#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include "Result.h"

#include <windows.h> 
#include <playsoundapi.h>
#include <mmsystem.h>
#include <array>
#pragma comment(lib, "winmm.lib")



struct AudioLoaderWav
{
//private:
    static constexpr char FORMAT[4] = { 'W','A','V','E' };
    static constexpr char ID_RIFF[4] = { 'R','I','F','F' };
    static constexpr char ID_FMT[4] = { 'f','m','t',' ' };
    static constexpr char ID_DATA[4] = { 'd','a','t','a' };

    static bool isFORMAT(uint8_t* id) { return memcmp(id, FORMAT, 4) == 0; }
    static bool isRIFF(uint8_t* id)   { return memcmp(id, ID_RIFF, 4) == 0; }
    static bool isFMT(uint8_t* id)    { return memcmp(id, ID_FMT, 4)  == 0; }
    static bool isDATA(uint8_t* id)   { return memcmp(id, ID_DATA, 4) == 0; }


    // A chunk of info 
    struct ChunkInfo {
        uint8_t chunkID[4];
        uint32_t chunkSize;
    };

    struct RIFF : public ChunkInfo {
        uint8_t  format[4];
    };

    // Format of the sound infomation
    struct Format : public ChunkInfo {
        uint16_t audioFormat;   // Audio format 1=PCM, 6=mulaw, 7=alaw,  257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
        uint16_t numChannels;   // Number of channels 1=Mono 2=Sterio
        uint32_t sampleRate;    // Sampling Frequency in Hz
        uint32_t byteRate;      // bytes per second
        uint16_t blockAlign;    // 2=16-bit mono, 4=16-bit stereo
        uint16_t bitsPerSample; // Number of bits per sample
    };

    // Contains the sound infomation and raw data
    // BUG: We assume 16-bit monochannel samples
    struct Data : public ChunkInfo {
        uint8_t* data;

        // Returns the number of elements in the data array
        size_t size() const {
            return chunkSize / sizeof(uint8_t);
        }
    };

    struct Wav {
        RIFF riff;
        Format fmt;
        Data data;

        Wav() :
            riff(), fmt(), data() {}

        Wav(RIFF riff_, Format fmt_, Data data_) :
            riff(riff_), fmt(fmt_), data(data_) {}


        void rawAll(uint8_t*& start, uint32_t& size) const
        {
            std::cout << "riff chunksize: " << riff.chunkSize + sizeof(ChunkInfo) << std::endl;
            std::cout << "attempt size: " << (sizeof(RIFF) + sizeof(Format) + sizeof(Data) - sizeof(uint8_t*) + data.size()) << std::endl;

            size = (riff.chunkSize + sizeof(ChunkInfo)) / sizeof(uint8_t);
            start = new uint8_t[size];
            uint8_t* ptr = start;

            //
            uint8_t* target = start + size;
            std::cout << "start: " << (void*)start << std::endl;
            std::cout << "target: " << (void*)target << std::endl;


            //memcpy_s(ptr, size, &riff, sizeof(RIFF));
            *(RIFF*)ptr = riff;
            ptr += sizeof(RIFF);

            //memcpy_s(ptr, size, &fmt, sizeof(Format));
            *(Format*)ptr = fmt;
            ptr += sizeof(Format);

            *(Data*)ptr = data;
            ptr += sizeof(Data) - sizeof(uint8_t*);
            
            
            size_t dataSize = data.chunkSize / sizeof(uint8_t);
            std::cout << "is same: " << (ptr + dataSize == target) << std::endl;

            uint8_t* firs = data.data;
            uint8_t* last = data.data + dataSize;
            //std::copy(firs, last, ptr);
            ptr += dataSize;

            std::cout << "is same: " << (ptr == target) << std::endl;

            std::cout << "arr:" << std::endl;
            for (int i = 0; i < size - data.size(); i++) {
                std::cout << (char)*(start + i);
            }
            std::cout << std::endl;
            std::cout << "done" << std::endl;

            //memcpy(rawTar, &data.data, data.chunkSize / sizeof(uint8_t));
        }

    };

    static Result loadRawFile(std::string filepath, Wav& wav)
    {
        // Open File
        std::ifstream ifs{ filepath, std::ios_base::binary };
        if (ifs.fail()) return CannotOpenFile;

        // Get file length
        //ifs.seekg(0, ifs.end);
        //int length = ifs.tellg(); // tellg returns pos
        //ifs.seekg(0, ifs.beg);

        // Read RIFF header
        RIFF riff;
        ifs.read((char*)&riff, sizeof(RIFF));
        if (!ifs || !isRIFF(riff.chunkID) || !isFORMAT(riff.format)) {
            ifs.close();
            return BadFormatting;
        }

        // Read chunk infos iteratively
        ChunkInfo ch;
        Format fmt;
        Data data;
        bool fmt_read = false;
        bool data_read = false;
        while (ifs.read((char*)&ch, sizeof(ChunkInfo)))
        {
            // Fmt chunk
            if (isFMT(ch.chunkID)) 
            {
                std::copy(std::begin(ch.chunkID), std::end(ch.chunkID), std::begin(fmt.chunkID));
                fmt.chunkSize = ch.chunkSize;

                ifs.read((char*)&fmt + sizeof(ChunkInfo), ch.chunkSize); // We've already read ChunkInfo

                if (fmt_read) std::cerr << "Multiple FMT chunks found" << std::endl;
                fmt_read = true;
            }

            // Data chunk
            else if (isDATA(ch.chunkID)) 
            {
                std::copy(std::begin(ch.chunkID), std::end(ch.chunkID), std::begin(data.chunkID));
                data.chunkSize = ch.chunkSize;

                data.data = new uint8_t[data.size()];

                ifs.read((char*)data.data + sizeof(ChunkInfo), ch.chunkSize); // We've already read ChunkInfo

                if (data_read) std::cerr << "Multiple Data chunks found" << std::endl;
                data_read = true;
            }

            // Otherwise, skip
            else ifs.seekg(ch.chunkSize, std::ios_base::cur);
        }

        ifs.close();

        if (!data_read || !fmt_read) return ProblemReadingData;

        wav = Wav(
            riff, fmt, data
        );
        
        return Success;
    }

    // TODO: Move to results?
    static bool checkResultForErrors(Result result) {
        switch (result) {
        case Success: return false;

        case CannotOpenFile:
            std::cerr << "Cannot open file" << std::endl;
            break;

        case BadFormatting:
            std::cerr << "Bad formatting" << std::endl;
            break;

        case ProblemReadingData:
            std::cerr << "Problem when reading data" << std::endl;
            break;
        }

        return true;
    }

public:

    static Wav load(std::string filepath)
    {
        Wav wavFile;
        Result res = loadRawFile(filepath, wavFile);
        if (checkResultForErrors(res)) throw "Error occurred";
        return wavFile;
    }


    static void debug_printInfo(const Wav& wav)
    {
        std::cout << "-- RIFF --" << std::endl;

        std::cout << "id: "; for (auto val : wav.riff.chunkID) std::cout << (char)val;
        std::cout << "  (should be: "; for (auto val : ID_RIFF) std::cout << (char)val;
        std::cout << ")" << std::endl;

        std::cout << "size: " << std::to_string(wav.riff.chunkSize) << std::endl;

        std::cout << "format: ";
        for (int i = 0; i < 4; i++) std::cout << wav.riff.format[i];
        std::cout << "  (should be: "; for (auto val : FORMAT) std::cout << (char)val;
        std::cout << ")" << std::endl;

        std::cout << std::endl;

        std::cout << "-- FMT --" << std::endl;

        std::cout << "id: "; for (auto val : wav.fmt.chunkID) std::cout << (char)val;
        std::cout << "  (should be: "; for (auto val : ID_FMT) std::cout << (char)val;
        std::cout << ")" << std::endl;

        std::cout << "chunkSize: " << std::to_string(wav.fmt.chunkSize) << std::endl;

        std::cout << "audioFormat: " << std::to_string(wav.fmt.audioFormat) << std::endl;
        std::cout << "numChannels: " << std::to_string(wav.fmt.numChannels) << std::endl;
        std::cout << "sampleRate: " << std::to_string(wav.fmt.sampleRate) << std::endl;
        std::cout << "byteRate: " << std::to_string(wav.fmt.byteRate) << std::endl;
        std::cout << "blockAlign: " << std::to_string(wav.fmt.blockAlign) << std::endl;
        std::cout << "bitsPerSample: " << std::to_string(wav.fmt.bitsPerSample) << std::endl;

        std::cout << std::endl;

        std::cout << "-- DATA --" << std::endl;

        std::cout << "id: "; for (auto val : wav.data.chunkID) std::cout << (char)val;
        std::cout << "  (should be: "; for (auto val : ID_DATA) std::cout << (char)val;
        std::cout << ")" << std::endl;

        std::cout << "chunkSize: " << std::to_string(wav.data.chunkSize) << std::endl;

        //std::cout << "nb of samples: " << std::to_string(wav.data.nb_of_samples) << std::endl;
    }


    static void debug_play(const Wav& wav)
    {
        // TODO

        // PlaySoundA((LPCSTR) "C:\\kenny g.WAV", NULL, SND_FILENAME | SND_ASYNC);

        //std::cout << "Playing sound" << std::endl;

        uint8_t* value = nullptr;
        uint32_t size;
        wav.rawAll(value, size);

        std::cout << (value == nullptr) << std::endl;

        //for (int i = 0; i < size; i++) {
        //    std::cout << (char)*(value + i);
        //}


        PlaySound(
             (LPCWSTR)(char*)(value),
            NULL,
            SND_MEMORY //| SND_SYNC
        );
    }
};
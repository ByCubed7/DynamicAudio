#pragma once
#include <cstdint>
#include <cmath>
#include <map>
#include <string>

namespace DynamicAudio {

    typedef uint16_t NoteValueType;
    typedef double NoteDurationType;

    struct Note {
        struct Value {

            // See https://inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies
            static const NoteValueType Gs9 = 127;
            static const NoteValueType G9 = 126;
            static const NoteValueType Fs9 = 125;
            static const NoteValueType F9 = 124;
            static const NoteValueType E9 = 123;
            static const NoteValueType Ds9 = 122;
            static const NoteValueType D9 = 121;
            static const NoteValueType Cs9 = 120;
            static const NoteValueType C9 = 119;
            static const NoteValueType B8 = 118;
            static const NoteValueType As8 = 117;
            static const NoteValueType A8 = 116;
            static const NoteValueType Gs8 = 115;
            static const NoteValueType G8 = 114;
            static const NoteValueType Fs8 = 113;
            static const NoteValueType F8 = 112;
            static const NoteValueType E8 = 111;
            static const NoteValueType Ds8 = 110;
            static const NoteValueType D8 = 109;
            static const NoteValueType Cs8 = 108;
            static const NoteValueType C8 = 107;
            static const NoteValueType B7 = 106;
            static const NoteValueType As7 = 105;
            static const NoteValueType A7 = 104;
            static const NoteValueType Gs7 = 103;
            static const NoteValueType G7 = 102;
            static const NoteValueType Fs7 = 101;
            static const NoteValueType F7 = 100;
            static const NoteValueType E7 = 99;
            static const NoteValueType Ds7 = 98;
            static const NoteValueType D7 = 97;
            static const NoteValueType Cs7 = 96;
            static const NoteValueType C7 = 95;
            static const NoteValueType B6 = 94;
            static const NoteValueType As6 = 93;
            static const NoteValueType A6 = 92;
            static const NoteValueType Gs6 = 91;
            static const NoteValueType G6 = 90;
            static const NoteValueType Fs6 = 89;
            static const NoteValueType F6 = 88;
            static const NoteValueType E6 = 87;
            static const NoteValueType Ds6 = 86;
            static const NoteValueType D6 = 85;
            static const NoteValueType Cs6 = 84;
            static const NoteValueType C6 = 83;
            static const NoteValueType B5 = 82;
            static const NoteValueType As5 = 81;
            static const NoteValueType A5 = 80;
            static const NoteValueType Gs5 = 79;
            static const NoteValueType G5 = 78;
            static const NoteValueType Fs5 = 77;
            static const NoteValueType F5 = 76;
            static const NoteValueType E5 = 75;
            static const NoteValueType Ds5 = 74;
            static const NoteValueType D5 = 73;
            static const NoteValueType Cs5 = 72;
            static const NoteValueType C5 = 71;
            static const NoteValueType B4 = 70;
            static const NoteValueType As4 = 69;
            static const NoteValueType A4 = 68;
            static const NoteValueType Gs4 = 67;
            static const NoteValueType G4 = 66;
            static const NoteValueType Fs4 = 65;
            static const NoteValueType F4 = 64;
            static const NoteValueType E4 = 63;
            static const NoteValueType Ds4 = 62;
            static const NoteValueType D4 = 61;
            static const NoteValueType Cs4 = 60;
            static const NoteValueType C4 = 59;
            static const NoteValueType B3 = 58;
            static const NoteValueType As3 = 57;
            static const NoteValueType A3 = 56;
            static const NoteValueType Gs3 = 55;
            static const NoteValueType G3 = 54;
            static const NoteValueType Fs3 = 53;
            static const NoteValueType F3 = 52;
            static const NoteValueType E3 = 51;
            static const NoteValueType Ds3 = 50;
            static const NoteValueType D3 = 49;
            static const NoteValueType Cs3 = 48;
            static const NoteValueType C3 = 47;
            static const NoteValueType B2 = 46;
            static const NoteValueType As2 = 45;
            static const NoteValueType A2 = 44;
            static const NoteValueType Gs2 = 43;
            static const NoteValueType G2 = 42;
            static const NoteValueType Fs2 = 41;
            static const NoteValueType F2 = 40;
            static const NoteValueType E2 = 39;
            static const NoteValueType Ds2 = 38;
            static const NoteValueType D2 = 37;
            static const NoteValueType Cs2 = 36;
            static const NoteValueType C2 = 35;
            static const NoteValueType B1 = 34;
            static const NoteValueType As1 = 33;
            static const NoteValueType A1 = 32;
            static const NoteValueType Gs1 = 31;
            static const NoteValueType G1 = 30;
            static const NoteValueType Fs1 = 29;
            static const NoteValueType F1 = 28;
            static const NoteValueType E1 = 27;
            static const NoteValueType Ds1 = 26;
            static const NoteValueType D1 = 25;
            static const NoteValueType Cs1 = 24;
            static const NoteValueType C1 = 23;
            static const NoteValueType B0 = 22;
            static const NoteValueType As0 = 21;
            static const NoteValueType A0 = 20;
            static const NoteValueType BNeg1 = 19;
            static const NoteValueType ANeg1 = 18;
            static const NoteValueType GsNeg1 = 17;
            static const NoteValueType GNeg1 = 16;
            static const NoteValueType FsNeg1 = 15;
            static const NoteValueType FNeg1 = 14;
            static const NoteValueType ENeg1 = 13;
            static const NoteValueType DsNeg1 = 12;
            static const NoteValueType DNeg1 = 11;
            static const NoteValueType CsNeg1 = 10;
            static const NoteValueType CNeg1 = 9;
            static const NoteValueType BNeg2 = 8;
            static const NoteValueType AsNeg2 = 7;
            static const NoteValueType ANeg2 = 6;
            static const NoteValueType GNeg2 = 5;
            static const NoteValueType GsNeg2 = 4;
            static const NoteValueType FNeg2 = 3;
            static const NoteValueType FsNeg2 = 2;
            static const NoteValueType ENeg2 = 1;
            static const NoteValueType DsNeg2 = 0;

            static const NoteValueType Middle_C = Cs4;
            static const NoteValueType MIDI_A440 = As4;

            static const NoteValueType null = 0;

            /// <summary> Is the note value null. </summary>
            /// <param name="value"> The value to check. </param>
            /// <returns> True if the value is null, false otherwise. </returns>
            static bool isNull(const NoteValueType& value) {
                return value == null;
            }

            /// <summary> Is the note value valid. </summary>
            /// <param name="value"> The value to check. </param>
            /// <returns> True if the value is valid, false otherwise. </returns>
            static bool isValid(const NoteValueType& value) {
                return !isNull(value);
            }

            /// <summary> Transpose a value by a certain number of semitones </summary>
            /// <param name="originalNote"> The initial value. </param>
            /// <param name="semitones"> The amount to transpose by. </param>
            /// <returns> The transposed note. </returns>
            static NoteValueType transpose(const NoteValueType& originalNote, const NoteValueType semitones) {
                return originalNote + semitones;
            }

            //

            /// <summary> 
            /// Calculate the frequency of the note based on its MIDI value. 
            /// MIDI note 69 (A or A440) is set to 440 Hz.
            /// </summary>
            /// <param name="value"> The Notes value to calculate. </param>
            /// <returns> The frequency in hertz. </returns>
            static double calculateFrequency(const NoteValueType& value) {
                if (isNull(value)) return 0;

                // MIDI note 69 (A440) is set to 440 Hz
                return 440.0 * pow(2.0, (value - 69) / 12.0);
            }

            // Define the noteMap
            static std::map<std::string, NoteValueType> mapStringToValue;

            // 

            /// <summary> Convert string to Note enum value. </summary>
            static NoteValueType fromString(const std::string& noteString) {
                auto it = mapStringToValue.find(noteString);

                // If found, return note
                if (it != mapStringToValue.end())
                    return it->second;

                // Else default to null
                return null;
            }
        };

        struct Duration {
            // Using the British naming convension
            static NoteDurationType Maxima;
            static NoteDurationType Long;
            static NoteDurationType Breve;
            static NoteDurationType Semibreve; // 1 whole note
            static NoteDurationType Minim;
            static NoteDurationType Crotchet;
            static NoteDurationType Quaver;
            static NoteDurationType Semiquaver;

            // A bit excessive:
            static NoteDurationType Demisemiquaver;  // 1/32
            static NoteDurationType Hemidemisemiquaver;  // 1/64
            static NoteDurationType Semihemidemisemiquaver;  // 1/128
            static NoteDurationType Demisemihemidemisemiquaver;
        };


        /// <summary> The value of the note. </summary>
        NoteValueType value;

        /// <summary> The duration of the note. </summary>
        NoteDurationType duration;

        Note(NoteValueType _value, NoteDurationType _duration) : value(_value), duration(_duration) {}
        Note(NoteValueType _value) : value(_value), duration(Duration::Semibreve) {}
        Note() : value(Value::null), duration(Duration::Semibreve) {}

        static Note fromString(const std::string& noteString) {
            NoteValueType value = DynamicAudio::Note::Value::fromString(noteString);
            return Note(value);
        }

        /// <summary> Transpose the Note. </summary>
        /// <param name="semitones">The amount of semitones to transpose by. </param>
        void transpose(NoteValueType semitones) {
            value = Value::transpose(value, semitones);
        }

        /// <summary> Calculates the notes frequency. </summary>
        double calculateFrequency() {
            return Value::calculateFrequency(value);
        }

        //implicit operator uint8_t () const { return value; }
        //explicit operator auto() const { return value; } 

        Note operator+(const NoteValueType& semitones) {
            auto result = Note(value, duration);
            result.transpose(semitones);
            return result;
        }

        /// <summary> Returns a Note with no value. </summary>
        static Note null(NoteDurationType duration = Duration::Semibreve) {
            return Note(Value::null, duration);
        }

        friend bool operator==(const Note& lhs, const Note& rhs) {
            if (lhs.value != rhs.value)
                return false;

            if (lhs.duration != rhs.duration)
                return false;

            return true;
        }

        friend bool operator!=(const Note& lhs, const Note& rhs) {
            return !operator==(lhs, rhs);
        }
    };
}


std::map<std::string, DynamicAudio::NoteValueType> DynamicAudio::Note::Value::mapStringToValue = {
    {"Gs9",  DynamicAudio::Note::Value::Gs9},
    {"G9",  DynamicAudio::Note::Value::G9},
    {"Fs9",  DynamicAudio::Note::Value::Fs9},
    {"F9",  DynamicAudio::Note::Value::F9},
    {"E9",  DynamicAudio::Note::Value::E9},
    {"Ds9",  DynamicAudio::Note::Value::Ds9},
    {"D9",  DynamicAudio::Note::Value::D9},
    {"Cs9",  DynamicAudio::Note::Value::Cs9},
    {"C9",  DynamicAudio::Note::Value::C9},
    {"B8",  DynamicAudio::Note::Value::B8},
    {"As8",  DynamicAudio::Note::Value::As8},
    {"A8",  DynamicAudio::Note::Value::A8},
    {"Gs8",  DynamicAudio::Note::Value::Gs8},
    {"G8",  DynamicAudio::Note::Value::G8},
    {"Fs8",  DynamicAudio::Note::Value::Fs8},
    {"F8",  DynamicAudio::Note::Value::F8},
    {"E8",  DynamicAudio::Note::Value::E8},
    {"Ds8",  DynamicAudio::Note::Value::Ds8},
    {"D8",  DynamicAudio::Note::Value::D8},
    {"Cs8",  DynamicAudio::Note::Value::Cs8},
    {"C8",  DynamicAudio::Note::Value::C8},
    {"B7",  DynamicAudio::Note::Value::B7},
    {"As7",  DynamicAudio::Note::Value::As7},
    {"A7",  DynamicAudio::Note::Value::A7},
    {"Gs7",  DynamicAudio::Note::Value::Gs7},
    {"G7",  DynamicAudio::Note::Value::G7},
    {"Fs7",  DynamicAudio::Note::Value::Fs7},
    {"F7",  DynamicAudio::Note::Value::F7},
    {"E7",  DynamicAudio::Note::Value::E7},
    {"Ds7",  DynamicAudio::Note::Value::Ds7},
    {"D7",  DynamicAudio::Note::Value::D7},
    {"Cs7",  DynamicAudio::Note::Value::Cs7},
    {"C7",  DynamicAudio::Note::Value::C7},
    {"B6",  DynamicAudio::Note::Value::B6},
    {"As6",  DynamicAudio::Note::Value::As6},
    {"A6",  DynamicAudio::Note::Value::A6},
    {"Gs6",  DynamicAudio::Note::Value::Gs6},
    {"G6",  DynamicAudio::Note::Value::G6},
    {"Fs6",  DynamicAudio::Note::Value::Fs6},
    {"F6",  DynamicAudio::Note::Value::F6},
    {"E6",  DynamicAudio::Note::Value::E6},
    {"Ds6",  DynamicAudio::Note::Value::Ds6},
    {"D6",  DynamicAudio::Note::Value::D6},
    {"Cs6",  DynamicAudio::Note::Value::Cs6},
    {"C6",  DynamicAudio::Note::Value::C6},
    {"B5",  DynamicAudio::Note::Value::B5},
    {"As5",  DynamicAudio::Note::Value::As5},
    {"A5",  DynamicAudio::Note::Value::A5},
    {"Gs5",  DynamicAudio::Note::Value::Gs5},
    {"G5",  DynamicAudio::Note::Value::G5},
    {"Fs5",  DynamicAudio::Note::Value::Fs5},
    {"F5",  DynamicAudio::Note::Value::F5},
    {"E5",  DynamicAudio::Note::Value::E5},
    {"Ds5",  DynamicAudio::Note::Value::Ds5},
    {"D5",  DynamicAudio::Note::Value::D5},
    {"Cs5",  DynamicAudio::Note::Value::Cs5},
    {"C5",  DynamicAudio::Note::Value::C5},
    {"B4",  DynamicAudio::Note::Value::B4},
    {"As4",  DynamicAudio::Note::Value::As4},
    {"A4",  DynamicAudio::Note::Value::A4},
    {"Gs4",  DynamicAudio::Note::Value::Gs4},
    {"G4",  DynamicAudio::Note::Value::G4},
    {"Fs4",  DynamicAudio::Note::Value::Fs4},
    {"F4",  DynamicAudio::Note::Value::F4},
    {"E4",  DynamicAudio::Note::Value::E4},
    {"Ds4",  DynamicAudio::Note::Value::Ds4},
    {"D4",  DynamicAudio::Note::Value::D4},
    {"Cs4",  DynamicAudio::Note::Value::Cs4},
    {"C4",  DynamicAudio::Note::Value::C4},
    {"B3",  DynamicAudio::Note::Value::B3},
    {"As3",  DynamicAudio::Note::Value::As3},
    {"A3",  DynamicAudio::Note::Value::A3},
    {"Gs3",  DynamicAudio::Note::Value::Gs3},
    {"G3",  DynamicAudio::Note::Value::G3},
    {"Fs3",  DynamicAudio::Note::Value::Fs3},
    {"F3",  DynamicAudio::Note::Value::F3},
    {"E3",  DynamicAudio::Note::Value::E3},
    {"Ds3",  DynamicAudio::Note::Value::Ds3},
    {"D3",  DynamicAudio::Note::Value::D3},
    {"Cs3",  DynamicAudio::Note::Value::Cs3},
    {"C3",  DynamicAudio::Note::Value::C3},
    {"B2",  DynamicAudio::Note::Value::B2},
    {"As2",  DynamicAudio::Note::Value::As2},
    {"A2",  DynamicAudio::Note::Value::A2},
    {"Gs2",  DynamicAudio::Note::Value::Gs2},
    {"G2",  DynamicAudio::Note::Value::G2},
    {"Fs2",  DynamicAudio::Note::Value::Fs2},
    {"F2",  DynamicAudio::Note::Value::F2},
    {"E2",  DynamicAudio::Note::Value::E2},
    {"Ds2",  DynamicAudio::Note::Value::Ds2},
    {"D2",  DynamicAudio::Note::Value::D2},
    {"Cs2",  DynamicAudio::Note::Value::Cs2},
    {"C2",  DynamicAudio::Note::Value::C2},
    {"B1",  DynamicAudio::Note::Value::B1},
    {"As1",  DynamicAudio::Note::Value::As1},
    {"A1",  DynamicAudio::Note::Value::A1},
    {"Gs1",  DynamicAudio::Note::Value::Gs1},
    {"G1",  DynamicAudio::Note::Value::G1},
    {"Fs1",  DynamicAudio::Note::Value::Fs1},
    {"F1",  DynamicAudio::Note::Value::F1},
    {"E1",  DynamicAudio::Note::Value::E1},
    {"Ds1",  DynamicAudio::Note::Value::Ds1},
    {"D1",  DynamicAudio::Note::Value::D1},
    {"Cs1",  DynamicAudio::Note::Value::Cs1},
    {"C1",  DynamicAudio::Note::Value::C1},
    {"B0",  DynamicAudio::Note::Value::B0},
    {"As0",  DynamicAudio::Note::Value::As0},
    {"A0",  DynamicAudio::Note::Value::A0},
    {"BNeg1",  DynamicAudio::Note::Value::BNeg1},
    {"ANeg1",  DynamicAudio::Note::Value::ANeg1},
    {"GsNeg1",  DynamicAudio::Note::Value::GsNeg1},
    {"GNeg1",  DynamicAudio::Note::Value::GNeg1},
    {"FsNeg1",  DynamicAudio::Note::Value::FsNeg1},
    {"FNeg1",  DynamicAudio::Note::Value::FNeg1},
    {"ENeg1",  DynamicAudio::Note::Value::ENeg1},
    {"DsNeg1",  DynamicAudio::Note::Value::DsNeg1},
    {"DNeg1",  DynamicAudio::Note::Value::DNeg1},
    {"CsNeg1",  DynamicAudio::Note::Value::CsNeg1},
    {"CNeg1",  DynamicAudio::Note::Value::CNeg1},
    {"BNeg2",  DynamicAudio::Note::Value::BNeg2},
    {"AsNeg2",  DynamicAudio::Note::Value::AsNeg2},
    {"ANeg2",  DynamicAudio::Note::Value::ANeg2},
    {"GNeg2",  DynamicAudio::Note::Value::GNeg2},
    {"GsNeg2",  DynamicAudio::Note::Value::GsNeg2},
    {"FNeg2",  DynamicAudio::Note::Value::FNeg2},
    {"FsNeg2",  DynamicAudio::Note::Value::FsNeg2},
    {"ENeg2",  DynamicAudio::Note::Value::ENeg2},
    {"DsNeg2",  DynamicAudio::Note::Value::DsNeg2},

    { "B",  DynamicAudio::Note::Value::B4 },
    { "As",  DynamicAudio::Note::Value::As4 },
    { "A",  DynamicAudio::Note::Value::A4 },
    { "Gs",  DynamicAudio::Note::Value::Gs4 },
    { "G",  DynamicAudio::Note::Value::G4 },
    { "Fs",  DynamicAudio::Note::Value::Fs4 },
    { "F",  DynamicAudio::Note::Value::F4 },
    { "E",  DynamicAudio::Note::Value::E4 },
    { "Ds",  DynamicAudio::Note::Value::Ds4 },
    { "D",  DynamicAudio::Note::Value::D4 },
    { "Cs",  DynamicAudio::Note::Value::Cs4 },
    { "C",  DynamicAudio::Note::Value::C4 }
};

DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Maxima = 1 * 8;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Long = 1 * 4;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Breve = 1 * 2;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Semibreve = 1; // 1 whole note
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Minim = 1 / 2;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Crotchet = 1 / 4;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Quaver = 1 / 8;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Semiquaver = 1 / 16;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Demisemiquaver = 1 / 32;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Hemidemisemiquaver = 1 / 64;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Semihemidemisemiquaver = 1 / 128;
DynamicAudio::NoteDurationType DynamicAudio::Note::Duration::Demisemihemidemisemiquaver = 1 / 256;
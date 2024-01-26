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
            static const NoteValueType Cf = 59; // MIDI value for C flat
            static const NoteValueType C  = 60; // MIDI value for C natural
            static const NoteValueType Cs = 61; // MIDI value for C sharp
            static const NoteValueType Df = 61; // MIDI value for D flat
            static const NoteValueType D  = 62; // MIDI value for D natural
            static const NoteValueType Ds = 63; // MIDI value for D sharp
            static const NoteValueType Ef = 63; // MIDI value for E flat
            static const NoteValueType E  = 64; // MIDI value for E natural
            static const NoteValueType F  = 65; // MIDI value for F natural
            static const NoteValueType Fs = 66; // MIDI value for F sharp
            static const NoteValueType Gf = 66; // MIDI value for G flat
            static const NoteValueType G  = 67; // MIDI value for G natural
            static const NoteValueType Gs = 68; // MIDI value for G sharp
            static const NoteValueType Af = 68; // MIDI value for A flat
            static const NoteValueType A  = 69; // MIDI value for A natural (A440 reference)
            static const NoteValueType As = 70; // MIDI value for A sharp
            static const NoteValueType Bf = 70; // MIDI value for B flat
            static const NoteValueType B  = 71; // MIDI value for B natural

            static const NoteValueType Middle_C = C;
            static const NoteValueType MIDI_A440 = A;

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
    {"C",  DynamicAudio::Note::Value::C},
    {"Cs", DynamicAudio::Note::Value::Cs},
    {"D",  DynamicAudio::Note::Value::D},
    {"Ds", DynamicAudio::Note::Value::Ds},
    {"E",  DynamicAudio::Note::Value::E},
    {"F",  DynamicAudio::Note::Value::F},
    {"Fs", DynamicAudio::Note::Value::Fs},
    {"G",  DynamicAudio::Note::Value::G},
    {"Gs", DynamicAudio::Note::Value::Gs},
    {"A",  DynamicAudio::Note::Value::A},
    {"As", DynamicAudio::Note::Value::As},
    {"B",  DynamicAudio::Note::Value::B}
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
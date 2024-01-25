#pragma once

#include <vector>
#include "Note.h"

namespace DynamicAudio {

    class Chord {
    private:
        std::vector<Note> notes;

    public:
        // Default Constructor
        Chord() : notes() {}

        // Constructor to create a Chord from a vector of Note
        Chord(const std::vector<Note>& notes) : notes(notes) {}

        /// <summary> Adds a Note to the Chord. </summary>
        /// <param name="note"> The note to add. </param>
        void addNote(const Note& note) {
            notes.push_back(note);
        }

        /// <summary> Adds an empty Note. </summary>
        /// <param name="duration"> The duration of the empty Note. </param>
        void addNull(double duration) {
            notes.push_back(
                Note::null(duration)
            );
        }

        /// <returns> A vector of the Note collection. </returns>
        const std::vector<Note>& allNotes() const {
            return notes;
        }

        /// <summary> Removes the given Note from the Chord. </summary>
        /// <param name="note"> The Note to remove. </param>
        void removeNote(const Note& note) {
            auto it = std::remove_if(notes.begin(), notes.end(), [&note](const Note& n) {
                return n == note;
                });
            notes.erase(it, notes.end());
        }

        /// <summary> Remove a Note by index. </summary>
        /// <param name="index">The index of the Note to remove. </param>
        void removeNote(int index) {
            notes.erase(notes.begin() + index);
        }

        /// <summary> Whether the Chord has the given Note. </summary>
        /// <param name="note"> The Note to check for. </param>
        /// <returns> Whether the Chord has the given Note. </returns>
        bool hasNote(const Note& note) const {
            return std::find(notes.begin(), notes.end(), note) != notes.end();
        }

        /// <summary> Transpose the entire Chord. </summary>
        /// <param name="semitones">The amount of semitones to transpose by. </param>
        void transpose(const NoteValueType& semitones) {
            for (auto& note : notes) {
                note.value = Note::Value::transpose(note.value, semitones);
            }
        }

        /// <summary> The first Note in the Chord. </summary>
        /// <returns> The first Note in the Chord. </returns>
        Note first() const {
            return notes[0];
        }

        // Get the total duration of the chord
        //int getTotalDuration() const {
        //    int duration = 0;

        //    for (Note note : notes)
        //        duration += note.duration;

        //    return duration;
        //}

        /// <summary>
        /// Gets the longest Note in the Chord.
        /// This is how long the Chord will play for.
        /// </summary>
        /// <returns> The length on the longest Note. </returns>
        double maxDuration() const {
            double longestTime = 0;
            for (const Note& note : notes)
                longestTime = std::max(longestTime, note.duration);
            return longestTime;
        }

        //Chord getScale() const {
        //    return getScale(first());
        //}

        //Chord getArpeggio() const {
        //    return getArpeggio(first());
        //}

        // 

        /// <summary>
        /// Calculates the Chord scale.
        /// For simplicity, we'll assume a major Chord.
        /// </summary>
        /// <param name="root"> The root Note to calculate. </param>
        /// <returns> The Chord of the scaled Note. </returns>
        static Chord getScale(Note root) {
            std::vector<Note> scale;

            // Add other notes based on the chord type (e.g., major, minor, etc.)
            // For simplicity, we'll assume a major chord here
            scale.push_back(root);
            scale.push_back(root + 2); // Major third
            scale.push_back(root + 4); // Perfect fifth
            scale.push_back(root + 5); // Major sixth
            scale.push_back(root + 7); // Minor seventh
            scale.push_back(root + 9); // Major ninth
            scale.push_back(root + 11); // Perfect eleventh

            return Chord(scale);
        }

        /// <summary>
        /// Calculates the Chord arpeggio.
        /// For simplicity, we'll assume a major Chord.
        /// </summary>
        /// <param name="root"> The root Note to calculate. </param>
        /// <returns> The Chord of the arpeggio-ed Note. </returns>
        static Chord getArpeggio(Note root) {
            std::vector<Note> arpeggio;

            // Add other notes based on the chord type (e.g., major, minor, etc.)
            // For simplicity, we'll assume a major arpeggio here
            arpeggio.push_back(root);
            arpeggio.push_back(root + 4);  // Major third
            arpeggio.push_back(root + 7);  // Perfect fifth
            arpeggio.push_back(root + 11); // Major ninth

            return Chord(arpeggio);
        }

        /// <summary>
        /// Creates a null Chord of a given duration.
        /// This just contains a null Note.
        /// </summary>
        /// <param name="length"> The duration of the nulled Chord. </param>
        /// <returns> A null Chord. </returns>
        static Chord null(NoteDurationType length) {
            std::vector<Note> empty;

            empty.push_back(Note::null(length));

            return Chord(empty);
        }

        /// <summary>
        /// Converts the given Note to a given Chord.
        /// </summary>
        /// <param name="note"> The Note to convert. </param>
        /// <returns> The converted Chord. </returns>
        static Chord fromNote(Note note) {
            Chord chord = {};
            chord.addNote(note);
            return chord;
        }

        /// <summary>
        /// An empty Chord.
        /// </summary>
        /// <returns> A Chord with nothing inside. </returns>
        static Chord empty() {
            return {};
        }
    };
}
#pragma once

#include <vector>
#include <tuple>

#include "Chord.h"

namespace DynamicAudio {

    struct Tune {
        std::vector<Chord> chords;

        Tune() : chords() {}

        /// <summary> Adds a chord to the tune. </summary>
        void addChord(Chord chord) {
            chords.push_back(chord);
        }

        /// <summary> Adds a single note as a chord to the tune. </summary>
        Chord& addSingle(Note note) {
            Chord chord = Chord::fromNote(note);
            chords.push_back(chord);
            return chords[chords.size()-1];
        }

        /// <summary> Adds an amount of silence to the tune. </summary>
        Chord& addSilence(double duration) {
            Chord chord = Chord::fromNote(Note::null(duration));
            chords.push_back(chord);
            return chords[chords.size() - 1];
        }

        /// <summary> Gets chord by index. </summary>
        Chord getChord(uint8_t index) {
            return chords[index];
        }

        /// <summary> The amount of chords in the tune. </summary>
        size_t size() {
            return chords.size();
        }

        /// <summary> Gets the most recent chord index to the given time. </summary>
        int getChordIndexAtTime(double time) {
            double timeTillTarget = time;
            int index = 0;

            for (const Chord& chord : chords)
            {
                // The next chord begins AFTER the longest notes ends
                timeTillTarget -= chord.maxDuration();

                // If past the target time
                if (timeTillTarget <= 0) return index;

                index++;
            }

            // No chord was found
            return -1;
        }

        /// <summary> Gets the most recent chord to the given time. </summary>
        Chord getChordAtTime(double time) {
            auto index = getChordIndexAtTime(time);
            if (index == -1) return Chord::empty();
            return chords[index];
        }

        /// <summary> Gets all of the notes being played at this time. </summary>
        Chord getNotesAtTime(double time) {
            std::vector<Note> current = {};
            double timeTillTarget = time + chords[0].maxDuration();

            for (const Chord& chord : chords)
            {
                // The next chord begins AFTER the longest notes ends
                timeTillTarget -= chord.maxDuration();

                // If past the target time
                if (timeTillTarget < 0) break;

                // If the note will be played at our designated time, add it
                for (const Note& note : chord.allNotes())
                    if (timeTillTarget <= note.duration)
                        current.push_back(note);
            }

            return current;
        }

        /// <summary> Gets the most recent note being played at this time. This is for times where you only want one note. </summary>
        Note getNoteAtTime(double time) {
            double timeTillTarget = time + chords[0].maxDuration();

            for (const Chord& chord : chords)
            {
                // The next chord begins AFTER the longest notes ends
                timeTillTarget -= chord.maxDuration();

                // If past the target time
                if (timeTillTarget <= 0) break;

                // If the note will be played at our designated time return it
                for (const Note& note : chord.allNotes())
                    if (timeTillTarget <= note.duration)
                        return note;
            }

            return Note::null();
        }
    };
}
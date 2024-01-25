#pragma once

#include <cstdint>
#include <cstdlib>
#include "AudioLoaderWav.h"
#include <chrono>
#include "AudioLoaderWav.h"

namespace Effect {

	// Unknown what the return type is
	// Maybe template it?
	#define value uint8_t

	/// <summary> The base class for an effect </summary>
	struct Abstract
	{
		/// <summary> Gets the calculated effects value. </summary>
		/// <param name="in"> The value passed in. </param>
		/// <returns> The value passed out. </returns>
		virtual value get(value in = 0) = 0;
	};

	/// <summary> Gets a constant value. </summary>
	struct Const : public Abstract
	{
		/// <summary> The value to represent. </summary>
		value constant;

		/// <summary> Constructor Definition. </summary>
		Const(value constant_) : constant(constant_) {}

		value get(value in) override {
			return constant;
		}

		/// <summary> Casting to a value should return the constant. </summary>
		operator value() { return constant; }
		/// <summary> Casting to a value should return the constant. </summary>
		operator const value() const { return constant; }
	};

	/// <summary> Gets a random value. </summary>
	struct Random : public Abstract
	{
		unsigned int seed;
		Abstract* minu;
		Abstract* maxi;

		/// <summary> Constructor Definition. </summary>
		Random(unsigned int seed_, Abstract* minu_, Abstract* maxi_)
			: seed(seed_), minu(minu_), maxi(maxi_) {
			std::srand(seed);
		}

		value get(value in) override {
			return minu->get(in) + std::rand() % (maxi->get(in) - minu->get(in));
		}
	};

	/// <summary> Returns the time stamp from start. </summary>
	struct TimeSince : public Abstract
	{
		std::chrono::steady_clock::time_point start;

		/// <summary> Constructor Definition. </summary>
		TimeSince()
			: start(std::chrono::high_resolution_clock::now()) {
		}

		value get(value in) override {
			std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start);
			return duration.count();
		}
	};


#ifdef max
#undef max
#undef min
#endif

	/// <summary> Gets the values of the WAV stream at the current time stamp. </summary>
	struct WavStream : public Abstract
	{
		Abstract* timestamp;
		AudioLoaderWav::Wav wav;

		/// <summary> Constructor Definition. </summary>
		WavStream(Abstract* timestamp_, AudioLoaderWav::Wav wav_)
			: timestamp(timestamp_), wav(wav_) {}

		value get(value in) override {
			// TODO: multiply timestamp by wav streams per second, ect..
			unsigned int stamp = std::max(timestamp->get(), (uint8_t)wav.data.chunkSize);
			return wav.data.data[stamp];
		}
	};

}
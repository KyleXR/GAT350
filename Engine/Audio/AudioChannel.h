#pragma once

namespace FMOD
{
	class Channel;
}

namespace neu
{
	class AudioChannel
	{
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* channel) : m_channel{channel} {}// !! set m_channel 

		bool IsPlaying();
		void Stop();

		void SetPitch(float pitch);
		void SetVolume(float volume);

		float GetPitch();
		float GetVolume();

	private:
		FMOD::Channel* m_channel = nullptr;
	};
}
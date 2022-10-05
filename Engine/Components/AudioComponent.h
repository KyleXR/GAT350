#pragma once
#include "Framework/Component.h"
#include "Audio/AudioChannel.h"

namespace neu
{
	class AudioComponent : public Component
	{
	public:
		~AudioComponent();
		AudioComponent() = default;

		CLASS_DECLARATION(AudioComponent)

		void Initialize() override;
		void Update() override;

		std::string m_SoundName;
		bool m_PlayOnAwake = false;
		float m_Volume = 1.0f;
		float m_Pitch = 1.0f;
		bool m_Loop = false;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Play();
		void Stop();

	public:
		AudioChannel m_channel;

		std::string sound_name;
		float volume = 1;
		float pitch = 1;
		bool play_on_start = false;
		bool loop = false;

	};

}
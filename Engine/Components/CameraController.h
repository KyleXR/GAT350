#pragma once 
#include "Framework/Component.h" 

namespace neu
{
	class CameraController : public Component
	{
	public:
		CLASS_DECLARATION(CameraController)

			void Initialize() override;
			void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:
		float sensitivity = 0.1f;
		float speed = 0;

	private:
		float m_yaw = 0; // Left/Right
		float m_pitch = 0; // Up/Down
	};
}
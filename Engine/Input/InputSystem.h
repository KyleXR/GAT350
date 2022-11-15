#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include "../Math/Vector2.h"

namespace neu
{
	class InputSystem
	{
	public:
		enum State
		{
			Idle,
			Pressed,
			Held,
			Released
		};

	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Initialized();
		void Shutdown();

		void Update();

		bool GetKeyDown(uint32_t key) { return m_keyboardState[key]; }
		State GetKeyState(uint32_t key);
		bool GetPreviousKeyDown(uint32_t key) { return m_prevKeyboardState[key]; }

	public:
		const Vector2& GetMousePosition() const { return m_mousePosition; }

		State GetButtonState(uint32_t button);
		bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetPreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }

	private:
		int m_numKeys;

		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;

	private:
		Vector2 m_mousePosition;

		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
	};

	extern const uint32_t key_space;
	extern const uint32_t key_up;
	extern const uint32_t key_down;
	extern const uint32_t key_left;
	extern const uint32_t key_right;
	extern const uint32_t key_escape;

	extern const uint32_t key_W;
	extern const uint32_t key_A;
	extern const uint32_t key_S;
	extern const uint32_t key_D;

	extern const uint32_t button_left;
	extern const uint32_t button_middle;
	extern const uint32_t button_right;
}
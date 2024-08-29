#pragma once

namespace StarEngine::Event
{
	enum KeyboardKey : U32
	{
		KEYBOARD_KEY_A = 65,
		KEYBOARD_KEY_B = 66,
		KEYBOARD_KEY_C = 67,
		KEYBOARD_KEY_D = 68,
		KEYBOARD_KEY_E = 69,
		KEYBOARD_KEY_F = 70,
		KEYBOARD_KEY_G = 71,
		KEYBOARD_KEY_H = 72,
		KEYBOARD_KEY_I = 73,
		KEYBOARD_KEY_J = 74,
		KEYBOARD_KEY_K = 75,
		KEYBOARD_KEY_L = 76,
		KEYBOARD_KEY_M = 77,
		KEYBOARD_KEY_N = 78,
		KEYBOARD_KEY_O = 79,
		KEYBOARD_KEY_P = 80,
		KEYBOARD_KEY_Q = 81,
		KEYBOARD_KEY_R = 82,
		KEYBOARD_KEY_S = 83,
		KEYBOARD_KEY_T = 84,
		KEYBOARD_KEY_U = 85,
		KEYBOARD_KEY_V = 86,
		KEYBOARD_KEY_W = 87,
		KEYBOARD_KEY_X = 88,
		KEYBOARD_KEY_Y = 89,
		KEYBOARD_KEY_Z = 90,

		KEYBOARD_KEY_LEFT_SHIFT = 340,
		KEYBOARD_KEY_LEFT_CTRL = 241,

		KEYBOARD_KEY_RIGHT_SHIFT = 344,
		KEYBOARD_KEY_RIGHT_CTRL = 245,
	};

	enum MouseKey : U32
	{
		MOUSE_KEY_1 = 0,
		MOUSE_KEY_2 = 1,
		MOUSE_KEY_3 = 2,
		MOUSE_KEY_4 = 3,
		MOUSE_KEY_5 = 4,
		MOUSE_KEY_6 = 5,
		MOUSE_KEY_7 = 6,
		MOUSE_KEY_8 = 7,
		MOUSE_KEY_LEFT = 0,
		MOUSE_KEY_RIGHT = 1,
		MOUSE_KEY_MIDDLE = 2,
	};

	VOID Update(GLFWwindow* Context);

	BOOL KeyDown(KeyboardKey Key);
	BOOL KeyHeld(KeyboardKey Key);
	BOOL KeyUp(KeyboardKey Key);

	BOOL MouseDown(MouseKey Key);
	BOOL MouseHeld(MouseKey Key);
	BOOL MouseUp(MouseKey Key);

	R32 GetMouseX();
	R32 GetMouseY();
	R32V2 GetMousePosition();

	VOID SetMouseX(R32 X);
	VOID SetMouseY(R32 Y);
}
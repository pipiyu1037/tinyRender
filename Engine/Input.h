#pragma once
#include "RenderBase.h"

#include <GLFW/glfw3.h>

class Input // static class
{
private:
	Input();

public:
	friend void RenderBase::Init();
	struct Key {
		friend class Input;
	private:
		Key(int code = 0) : code(code), lastPress(false), nowPress(false) {}
		int code;
		bool lastPress;
		bool nowPress;
	};

	static void Init(GLFWwindow* _window);
	static void Update();

	static bool GetKeyUp(Key& key) { return key.lastPress && !key.nowPress; }
	static bool GetKey(Key& key) { return key.nowPress; }
	static bool GetKeyDown(Key& key) { return !key.lastPress && key.nowPress; }

	static bool GetMouseUp() { return mouseLeftPressLast && !mouseLeftPressNow; }
	static bool GetMouse() { return mouseLeftPressNow; }
	static bool GetMouseDown() { return !mouseLeftPressLast && mouseLeftPressNow; }
	static bool GetMouseRightUp() { return mouseRightPressLast && !mouseRightPressNow; }
	static bool GetMouseRight() { return mouseRightPressNow; }
	static bool GetMouseRightDown() { return !mouseRightPressLast && mouseRightPressNow; }
	static float GetScroll() { return scrollOffsetY; }
	static float GetMouseX() { return mousePosX; }
	static float GetMouseY() { return mousePosY; }

private:
	constexpr static int keyNum = 120;
	static Key keys[keyNum];

	static bool mouseLeftPressLast;
	static bool mouseLeftPressNow;
	static bool mouseLeftPressCache;

	static bool mouseRightPressLast;
	static bool mouseRightPressNow;
	static bool mouseRightPressCache;

	static float scrollOffsetY;
	static float scrollOffsetYCache;

	static float mousePosX;
	static float mousePosY;
	static double mousePosXCache;
	static double mousePosYCache;

	// for RenderBase
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	static GLFWwindow* window;

public:
	static Key& Key_Space;
	static Key& Key_Apostrophe;
	static Key& Key_Comma;
	static Key& Key_Minus;
	static Key& Key_Period;
	static Key& Key_Slash;
	static Key& Key_0;
	static Key& Key_1;
	static Key& Key_2;
	static Key& Key_3;
	static Key& Key_4;
	static Key& Key_5;
	static Key& Key_6;
	static Key& Key_7;
	static Key& Key_8;
	static Key& Key_9;
	static Key& Key_Semicolon;
	static Key& Key_Equal;
	static Key& Key_A;
	static Key& Key_B;
	static Key& Key_C;
	static Key& Key_D;
	static Key& Key_E;
	static Key& Key_F;
	static Key& Key_G;
	static Key& Key_H;
	static Key& Key_I;
	static Key& Key_J;
	static Key& Key_K;
	static Key& Key_L;
	static Key& Key_M;
	static Key& Key_N;
	static Key& Key_O;
	static Key& Key_P;
	static Key& Key_Q;
	static Key& Key_R;
	static Key& Key_S;
	static Key& Key_T;
	static Key& Key_U;
	static Key& Key_V;
	static Key& Key_W;
	static Key& Key_X;
	static Key& Key_Y;
	static Key& Key_Z;
	static Key& Key_LeftBracket;
	static Key& Key_Backslash;
	static Key& Key_RightBracket;
	static Key& Key_GraveAccent;
	static Key& Key_World1;
	static Key& Key_World2;
	static Key& Key_Escape;
	static Key& Key_Enter;
	static Key& Key_Tab;
	static Key& Key_Backspace;
	static Key& Key_Insert;
	static Key& Key_Delete;
	static Key& Key_Right;
	static Key& Key_Left;
	static Key& Key_Down;
	static Key& Key_Up;
	static Key& Key_PageUp;
	static Key& Key_PageDown;
	static Key& Key_Home;
	static Key& Key_End;
	static Key& Key_CapsLock;
	static Key& Key_ScrollLock;
	static Key& Key_NumLock;
	static Key& Key_PrintScreen;
	static Key& Key_Pause;
	static Key& Key_F1;
	static Key& Key_F2;
	static Key& Key_F3;
	static Key& Key_F4;
	static Key& Key_F5;
	static Key& Key_F6;
	static Key& Key_F7;
	static Key& Key_F8;
	static Key& Key_F9;
	static Key& Key_F10;
	static Key& Key_F11;
	static Key& Key_F12;
	static Key& Key_F13;
	static Key& Key_F14;
	static Key& Key_F15;
	static Key& Key_F16;
	static Key& Key_F17;
	static Key& Key_F18;
	static Key& Key_F19;
	static Key& Key_F20;
	static Key& Key_F21;
	static Key& Key_F22;
	static Key& Key_F23;
	static Key& Key_F24;
	static Key& Key_F25;
	static Key& Key_Kp0;
	static Key& Key_Kp1;
	static Key& Key_Kp2;
	static Key& Key_Kp3;
	static Key& Key_Kp4;
	static Key& Key_Kp5;
	static Key& Key_Kp6;
	static Key& Key_Kp7;
	static Key& Key_Kp8;
	static Key& Key_Kp9;
	static Key& Key_KpDecimal;
	static Key& Key_KpDivide;
	static Key& Key_KpMultiply;
	static Key& Key_KpSubtract;
	static Key& Key_KpAdd;
	static Key& Key_KpEnter;
	static Key& Key_KpEqual;
	static Key& Key_LeftShift;
	static Key& Key_LeftControl;
	static Key& Key_LeftAlt;
	static Key& Key_LeftSuper;
	static Key& Key_RightShift;
	static Key& Key_RightControl;
	static Key& Key_RightAlt;
	static Key& Key_RightSuper;
	static Key& Key_Menu;
};


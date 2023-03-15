#include "Input.h"

Input::Key Input::keys[keyNum];
GLFWwindow* Input::window = nullptr;

bool Input::mouseLeftPressLast;
bool Input::mouseLeftPressNow;
bool Input::mouseLeftPressCache = false;

bool Input::mouseRightPressLast;
bool Input::mouseRightPressNow;
bool Input::mouseRightPressCache = false;

float Input::scrollOffsetY;
float Input::scrollOffsetYCache = false;

float Input::mousePosX;
float Input::mousePosY;
double Input::mousePosXCache;
double Input::mousePosYCache;



void Input::Update() {
	for (auto &key : keys) {
		key.lastPress = key.nowPress;
		if (glfwGetKey(window, key.code) == GLFW_PRESS) {
			key.nowPress = true;
		}
		else if (glfwGetKey(window, key.code) == GLFW_RELEASE) {
			key.nowPress = false;
		}
	}

	glfwGetCursorPos(RenderBase::window, &mousePosXCache, &mousePosYCache);

	mouseLeftPressLast = mouseLeftPressNow;
	mouseLeftPressNow = mouseLeftPressCache;
	mouseRightPressLast = mouseRightPressNow;
	mouseRightPressNow = mouseRightPressCache;
	scrollOffsetY = scrollOffsetYCache;
	mousePosX = static_cast<float>(mousePosXCache);
	mousePosY = static_cast<float>(mousePosYCache);

	mouseLeftPressCache = false;
	mouseRightPressCache = false;
	scrollOffsetYCache = 0;
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scrollOffsetYCache += static_cast<float>(yoffset);
	// camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			mouseLeftPressCache = true;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			mouseRightPressCache = true;
		}
	}
}

void Input::Init(GLFWwindow* _window) {
	window = _window;

	Key_Space = Key(GLFW_KEY_SPACE);
	Key_Apostrophe = Key(GLFW_KEY_APOSTROPHE);
	Key_Comma = Key(GLFW_KEY_COMMA);
	Key_Minus = Key(GLFW_KEY_MINUS);
	Key_Period = Key(GLFW_KEY_PERIOD);
	Key_Slash = Key(GLFW_KEY_SLASH);
	Key_0 = Key(GLFW_KEY_0);
	Key_1 = Key(GLFW_KEY_1);
	Key_2 = Key(GLFW_KEY_2);
	Key_3 = Key(GLFW_KEY_3);
	Key_4 = Key(GLFW_KEY_4);
	Key_5 = Key(GLFW_KEY_5);
	Key_6 = Key(GLFW_KEY_6);
	Key_7 = Key(GLFW_KEY_7);
	Key_8 = Key(GLFW_KEY_8);
	Key_9 = Key(GLFW_KEY_9);
	Key_Semicolon = Key(GLFW_KEY_SEMICOLON);
	Key_Equal = Key(GLFW_KEY_EQUAL);
	Key_A = Key(GLFW_KEY_A);
	Key_B = Key(GLFW_KEY_B);
	Key_C = Key(GLFW_KEY_C);
	Key_D = Key(GLFW_KEY_D);
	Key_E = Key(GLFW_KEY_E);
	Key_F = Key(GLFW_KEY_F);
	Key_G = Key(GLFW_KEY_G);
	Key_H = Key(GLFW_KEY_H);
	Key_I = Key(GLFW_KEY_I);
	Key_J = Key(GLFW_KEY_J);
	Key_K = Key(GLFW_KEY_K);
	Key_L = Key(GLFW_KEY_L);
	Key_M = Key(GLFW_KEY_M);
	Key_N = Key(GLFW_KEY_N);
	Key_O = Key(GLFW_KEY_O);
	Key_P = Key(GLFW_KEY_P);
	Key_Q = Key(GLFW_KEY_Q);
	Key_R = Key(GLFW_KEY_R);
	Key_S = Key(GLFW_KEY_S);
	Key_T = Key(GLFW_KEY_T);
	Key_U = Key(GLFW_KEY_U);
	Key_V = Key(GLFW_KEY_V);
	Key_W = Key(GLFW_KEY_W);
	Key_X = Key(GLFW_KEY_X);
	Key_Y = Key(GLFW_KEY_Y);
	Key_Z = Key(GLFW_KEY_Z);
	Key_LeftBracket = Key(GLFW_KEY_LEFT_BRACKET);
	Key_Backslash = Key(GLFW_KEY_BACKSLASH);
	Key_RightBracket = Key(GLFW_KEY_RIGHT_BRACKET);
	Key_GraveAccent = Key(GLFW_KEY_GRAVE_ACCENT);
	Key_World1 = Key(GLFW_KEY_WORLD_1);
	Key_World2 = Key(GLFW_KEY_WORLD_2);
	Key_Escape = Key(GLFW_KEY_ESCAPE);
	Key_Enter = Key(GLFW_KEY_ENTER);
	Key_Tab = Key(GLFW_KEY_TAB);
	Key_Backspace = Key(GLFW_KEY_BACKSPACE);
	Key_Insert = Key(GLFW_KEY_INSERT);
	Key_Delete = Key(GLFW_KEY_DELETE);
	Key_Right = Key(GLFW_KEY_RIGHT);
	Key_Left = Key(GLFW_KEY_LEFT);
	Key_Down = Key(GLFW_KEY_DOWN);
	Key_Up = Key(GLFW_KEY_UP);
	Key_PageUp = Key(GLFW_KEY_PAGE_UP);
	Key_PageDown = Key(GLFW_KEY_PAGE_DOWN);
	Key_Home = Key(GLFW_KEY_HOME);
	Key_End = Key(GLFW_KEY_END);
	Key_CapsLock = Key(GLFW_KEY_CAPS_LOCK);
	Key_ScrollLock = Key(GLFW_KEY_SCROLL_LOCK);
	Key_NumLock = Key(GLFW_KEY_NUM_LOCK);
	Key_PrintScreen = Key(GLFW_KEY_PRINT_SCREEN);
	Key_Pause = Key(GLFW_KEY_PAUSE);
	Key_F1 = Key(GLFW_KEY_F1);
	Key_F2 = Key(GLFW_KEY_F2);
	Key_F3 = Key(GLFW_KEY_F3);
	Key_F4 = Key(GLFW_KEY_F4);
	Key_F5 = Key(GLFW_KEY_F5);
	Key_F6 = Key(GLFW_KEY_F6);
	Key_F7 = Key(GLFW_KEY_F7);
	Key_F8 = Key(GLFW_KEY_F8);
	Key_F9 = Key(GLFW_KEY_F9);
	Key_F10 = Key(GLFW_KEY_F10);
	Key_F11 = Key(GLFW_KEY_F11);
	Key_F12 = Key(GLFW_KEY_F12);
	Key_F13 = Key(GLFW_KEY_F13);
	Key_F14 = Key(GLFW_KEY_F14);
	Key_F15 = Key(GLFW_KEY_F15);
	Key_F16 = Key(GLFW_KEY_F16);
	Key_F17 = Key(GLFW_KEY_F17);
	Key_F18 = Key(GLFW_KEY_F18);
	Key_F19 = Key(GLFW_KEY_F19);
	Key_F20 = Key(GLFW_KEY_F20);
	Key_F21 = Key(GLFW_KEY_F21);
	Key_F22 = Key(GLFW_KEY_F22);
	Key_F23 = Key(GLFW_KEY_F23);
	Key_F24 = Key(GLFW_KEY_F24);
	Key_F25 = Key(GLFW_KEY_F25);
	Key_Kp0 = Key(GLFW_KEY_KP_0);
	Key_Kp1 = Key(GLFW_KEY_KP_1);
	Key_Kp2 = Key(GLFW_KEY_KP_2);
	Key_Kp3 = Key(GLFW_KEY_KP_3);
	Key_Kp4 = Key(GLFW_KEY_KP_4);
	Key_Kp5 = Key(GLFW_KEY_KP_5);
	Key_Kp6 = Key(GLFW_KEY_KP_6);
	Key_Kp7 = Key(GLFW_KEY_KP_7);
	Key_Kp8 = Key(GLFW_KEY_KP_8);
	Key_Kp9 = Key(GLFW_KEY_KP_9);
	Key_KpDecimal = Key(GLFW_KEY_KP_DECIMAL);
	Key_KpDivide = Key(GLFW_KEY_KP_DIVIDE);
	Key_KpMultiply = Key(GLFW_KEY_KP_MULTIPLY);
	Key_KpSubtract = Key(GLFW_KEY_KP_SUBTRACT);
	Key_KpAdd = Key(GLFW_KEY_KP_ADD);
	Key_KpEnter = Key(GLFW_KEY_KP_ENTER);
	Key_KpEqual = Key(GLFW_KEY_KP_EQUAL);
	Key_LeftShift = Key(GLFW_KEY_LEFT_SHIFT);
	Key_LeftControl = Key(GLFW_KEY_LEFT_CONTROL);
	Key_LeftAlt = Key(GLFW_KEY_LEFT_ALT);
	Key_LeftSuper = Key(GLFW_KEY_LEFT_SUPER);
	Key_RightShift = Key(GLFW_KEY_RIGHT_SHIFT);
	Key_RightControl = Key(GLFW_KEY_RIGHT_CONTROL);
	Key_RightAlt = Key(GLFW_KEY_RIGHT_ALT);
	Key_RightSuper = Key(GLFW_KEY_RIGHT_SUPER);
	Key_Menu = Key(GLFW_KEY_MENU);
}

Input::Key& Input::Key_Space = Input::keys[0];
Input::Key& Input::Key_Apostrophe = Input::keys[1];
Input::Key& Input::Key_Comma = Input::keys[2];
Input::Key& Input::Key_Minus = Input::keys[3];
Input::Key& Input::Key_Period = Input::keys[4];
Input::Key& Input::Key_Slash = Input::keys[5];
Input::Key& Input::Key_0 = Input::keys[6];
Input::Key& Input::Key_1 = Input::keys[7];
Input::Key& Input::Key_2 = Input::keys[8];
Input::Key& Input::Key_3 = Input::keys[9];
Input::Key& Input::Key_4 = Input::keys[10];
Input::Key& Input::Key_5 = Input::keys[11];
Input::Key& Input::Key_6 = Input::keys[12];
Input::Key& Input::Key_7 = Input::keys[13];
Input::Key& Input::Key_8 = Input::keys[14];
Input::Key& Input::Key_9 = Input::keys[15];
Input::Key& Input::Key_Semicolon = Input::keys[16];
Input::Key& Input::Key_Equal = Input::keys[17];
Input::Key& Input::Key_A = Input::keys[18];
Input::Key& Input::Key_B = Input::keys[19];
Input::Key& Input::Key_C = Input::keys[20];
Input::Key& Input::Key_D = Input::keys[21];
Input::Key& Input::Key_E = Input::keys[22];
Input::Key& Input::Key_F = Input::keys[23];
Input::Key& Input::Key_G = Input::keys[24];
Input::Key& Input::Key_H = Input::keys[25];
Input::Key& Input::Key_I = Input::keys[26];
Input::Key& Input::Key_J = Input::keys[27];
Input::Key& Input::Key_K = Input::keys[28];
Input::Key& Input::Key_L = Input::keys[29];
Input::Key& Input::Key_M = Input::keys[30];
Input::Key& Input::Key_N = Input::keys[31];
Input::Key& Input::Key_O = Input::keys[32];
Input::Key& Input::Key_P = Input::keys[33];
Input::Key& Input::Key_Q = Input::keys[34];
Input::Key& Input::Key_R = Input::keys[35];
Input::Key& Input::Key_S = Input::keys[36];
Input::Key& Input::Key_T = Input::keys[37];
Input::Key& Input::Key_U = Input::keys[38];
Input::Key& Input::Key_V = Input::keys[39];
Input::Key& Input::Key_W = Input::keys[40];
Input::Key& Input::Key_X = Input::keys[41];
Input::Key& Input::Key_Y = Input::keys[42];
Input::Key& Input::Key_Z = Input::keys[43];
Input::Key& Input::Key_LeftBracket = Input::keys[44];
Input::Key& Input::Key_Backslash = Input::keys[45];
Input::Key& Input::Key_RightBracket = Input::keys[46];
Input::Key& Input::Key_GraveAccent = Input::keys[47];
Input::Key& Input::Key_World1 = Input::keys[48];
Input::Key& Input::Key_World2 = Input::keys[49];
Input::Key& Input::Key_Escape = Input::keys[50];
Input::Key& Input::Key_Enter = Input::keys[51];
Input::Key& Input::Key_Tab = Input::keys[52];
Input::Key& Input::Key_Backspace = Input::keys[53];
Input::Key& Input::Key_Insert = Input::keys[54];
Input::Key& Input::Key_Delete = Input::keys[55];
Input::Key& Input::Key_Right = Input::keys[56];
Input::Key& Input::Key_Left = Input::keys[57];
Input::Key& Input::Key_Down = Input::keys[58];
Input::Key& Input::Key_Up = Input::keys[59];
Input::Key& Input::Key_PageUp = Input::keys[60];
Input::Key& Input::Key_PageDown = Input::keys[61];
Input::Key& Input::Key_Home = Input::keys[62];
Input::Key& Input::Key_End = Input::keys[63];
Input::Key& Input::Key_CapsLock = Input::keys[64];
Input::Key& Input::Key_ScrollLock = Input::keys[65];
Input::Key& Input::Key_NumLock = Input::keys[66];
Input::Key& Input::Key_PrintScreen = Input::keys[67];
Input::Key& Input::Key_Pause = Input::keys[68];
Input::Key& Input::Key_F1 = Input::keys[69];
Input::Key& Input::Key_F2 = Input::keys[70];
Input::Key& Input::Key_F3 = Input::keys[71];
Input::Key& Input::Key_F4 = Input::keys[72];
Input::Key& Input::Key_F5 = Input::keys[73];
Input::Key& Input::Key_F6 = Input::keys[74];
Input::Key& Input::Key_F7 = Input::keys[75];
Input::Key& Input::Key_F8 = Input::keys[76];
Input::Key& Input::Key_F9 = Input::keys[77];
Input::Key& Input::Key_F10 = Input::keys[78];
Input::Key& Input::Key_F11 = Input::keys[79];
Input::Key& Input::Key_F12 = Input::keys[80];
Input::Key& Input::Key_F13 = Input::keys[81];
Input::Key& Input::Key_F14 = Input::keys[82];
Input::Key& Input::Key_F15 = Input::keys[83];
Input::Key& Input::Key_F16 = Input::keys[84];
Input::Key& Input::Key_F17 = Input::keys[85];
Input::Key& Input::Key_F18 = Input::keys[86];
Input::Key& Input::Key_F19 = Input::keys[87];
Input::Key& Input::Key_F20 = Input::keys[88];
Input::Key& Input::Key_F21 = Input::keys[89];
Input::Key& Input::Key_F22 = Input::keys[90];
Input::Key& Input::Key_F23 = Input::keys[91];
Input::Key& Input::Key_F24 = Input::keys[92];
Input::Key& Input::Key_F25 = Input::keys[93];
Input::Key& Input::Key_Kp0 = Input::keys[94];
Input::Key& Input::Key_Kp1 = Input::keys[95];
Input::Key& Input::Key_Kp2 = Input::keys[96];
Input::Key& Input::Key_Kp3 = Input::keys[97];
Input::Key& Input::Key_Kp4 = Input::keys[98];
Input::Key& Input::Key_Kp5 = Input::keys[99];
Input::Key& Input::Key_Kp6 = Input::keys[100];
Input::Key& Input::Key_Kp7 = Input::keys[101];
Input::Key& Input::Key_Kp8 = Input::keys[102];
Input::Key& Input::Key_Kp9 = Input::keys[103];
Input::Key& Input::Key_KpDecimal = Input::keys[104];
Input::Key& Input::Key_KpDivide = Input::keys[105];
Input::Key& Input::Key_KpMultiply = Input::keys[106];
Input::Key& Input::Key_KpSubtract = Input::keys[107];
Input::Key& Input::Key_KpAdd = Input::keys[108];
Input::Key& Input::Key_KpEnter = Input::keys[109];
Input::Key& Input::Key_KpEqual = Input::keys[110];
Input::Key& Input::Key_LeftShift = Input::keys[111];
Input::Key& Input::Key_LeftControl = Input::keys[112];
Input::Key& Input::Key_LeftAlt = Input::keys[113];
Input::Key& Input::Key_LeftSuper = Input::keys[114];
Input::Key& Input::Key_RightShift = Input::keys[115];
Input::Key& Input::Key_RightControl = Input::keys[116];
Input::Key& Input::Key_RightAlt = Input::keys[117];
Input::Key& Input::Key_RightSuper = Input::keys[118];
Input::Key& Input::Key_Menu = Input::keys[119];

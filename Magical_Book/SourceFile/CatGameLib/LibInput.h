
#ifndef __CAT_GAME_LIBRARY_INPUT_H__
#define __CAT_GAME_LIBRARY_INPUT_H__

#include "CatGameLib.h"
#include "ExternalLib.h"

#define PAD_NUM CatGameLib::LibInput::GamePadNumber
#define PAD_BUTTON_NUM CatGameLib::LibInput::GamePadButtonNumber

namespace CatGameLib
{

class LibInput
{
public:
	enum KeyBoardNumber
	{
		Key_0 = 48,
		Key_1,
		Key_2,
		Key_3,
		Key_4,
		Key_5,
		Key_6,
		Key_7,
		Key_8,
		Key_9,

		Key_A = 65,
		Key_B,
		Key_C,
		Key_D,
		Key_E,
		Key_F,
		Key_G,
		Key_H,
		Key_I,
		Key_J,
		Key_K,
		Key_L,
		Key_M,
		Key_N,
		Key_O,
		Key_P,
		Key_Q,
		Key_R,
		Key_S,
		Key_T,
		Key_U,
		Key_V,
		Key_W,
		Key_X,
		Key_Y,
		Key_Z,

		Key_Space		= GLFW_KEY_SPACE,
		Key_Esc			= GLFW_KEY_ESCAPE,
		Key_Up			= GLFW_KEY_UP,
		Key_Down		= GLFW_KEY_DOWN,
		Key_Left		= GLFW_KEY_LEFT,
		Key_Right		= GLFW_KEY_RIGHT,
		Key_LShift		= GLFW_KEY_LEFT_SHIFT,
		Key_RShift		= GLFW_KEY_RIGHT_SHIFT,
		Key_LCtrl		= GLFW_KEY_LEFT_CONTROL,
		Key_RCtrl		= GLFW_KEY_RIGHT_CONTROL,
		Key_LAlt		= GLFW_KEY_LEFT_ALT,
		Key_RAlt		= GLFW_KEY_RIGHT_ALT,
		Key_LSuper		= GLFW_KEY_LEFT_SUPER,	// windowsキー or commandキー
		Key_RSuper		= GLFW_KEY_RIGHT_SUPER,
		Key_Tab			= GLFW_KEY_TAB,
		Key_Enter		= GLFW_KEY_ENTER,
		Key_BackSpace	= GLFW_KEY_BACKSPACE,
	};

	enum MouseNumber
	{
		Mouse_Left			= 0,
		Mouse_Right,
		Mouse_Center,
		Mouse_4,
		Mouse_5,
		Mouse_6,
		Mouse_7,
		Mouse_8,
		Mouse_9,
		Mouse_Key_Num,
	};

	enum GamePadNumber
	{
		Pad_1 = 0,
		Pad_2,
		Pad_3,
		Pad_4,
		Pad_5,
		Pad_6,
		Pad_7,
		Pad_8,
		Pad_9,
		Pad_10,
		Pad_11,
		Pad_12,
		Pad_13,
		Pad_14,
		Pad_15,
		Pad_16,
	};

	enum GamePadButtonNumber
	{
		Button_1 = 0,
		Button_2,
		Button_3,
		Button_4,
		Button_5,
		Button_6,
		Button_7,
		Button_8,
		Button_9,
		Button_10,
		Button_11,
		Button_12,
		Button_13,
		Button_14,
		Button_15,
		Button_16,
	};

	static LibInput* getInstance( void)
	{
		static LibInput* instance = nullptr;
		if( !instance) { instance = new LibInput(); }
		return instance;
	}
	LibInput( const LibInput&) = delete;
	const LibInput& operator=( const LibInput&) = delete;

	static void MouseButtonPushCallback( GLFWwindow* window, int button, int action, int mods);
	static void MouseCursorMoveCallback( GLFWwindow* window, double xpos, double ypos);
	static void MouseCursorWindowInCallback( GLFWwindow* window, int flag);
	static void MouseWheelMoveCallback( GLFWwindow* window, double xpos, double ypos);

	void setWindow( GLFWwindow* window);
	void initSystem( void);
	void update( void);


	bool getKeyboardState( KeyBoardNumber number);
	bool getKeyboardUpState( KeyBoardNumber number);
	bool getKeyboardDownState( KeyBoardNumber number);

	bool getMouseState( MouseNumber number);
	bool getMouseUpState( MouseNumber number);
	bool getMouseDownState( MouseNumber number);
	LibVector2 getMousePosition( void);
	LibVector2 getMouseWheel( void);

	int getGamePadCount( void);
	int getGamePadStickCount( GamePadNumber padNumber);
	bool getGamePadState( GamePadNumber padNumber, GamePadButtonNumber number);
	bool getGamePadUpState( GamePadNumber padNumber, GamePadButtonNumber number);
	bool getGamePadDownState( GamePadNumber padNumber, GamePadButtonNumber number);
	LibVector2 getGamePadStickVector( GamePadNumber padNumber, int stickNumber);

private:
	class LibGamePad;
	
	const int specialKeyNum = 17;	// Spaceキー等の数
	const std::pair<bool,bool> initPair;

	bool isMouseWheelMove;
	int connectGamePadCount;

	GLFWwindow* window;				// 処理対象のウィンドウ

	LibVector2 mouseWheel;
	LibVector2 mousePosition;
	std::map<int, std::pair<bool,bool>> keyboardState;
	std::vector<std::pair<bool,bool>> mouseState;
	std::vector<LibGamePad*> gamePadState;
	LibInput();
	~LibInput();

	void initKeyboardState( void);
	void initMouseState( void);
	void initGamePadState( void);
};

}

#endif // __CAT_GAME_LIBRARY_INPUT_H__

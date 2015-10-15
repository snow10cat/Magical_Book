
#include "LibMain.h"

#ifdef DEBUG
#elif _DEBUG
#else

#pragma comment( linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

#endif	// _DEBUG

using namespace std;
using namespace CatGameLib;

class LibMain::Private
{
public:
	enum ClearColor
	{
		Red,
		Blue,
		Green,
		Alpha,
		ColorNum,
	};

	/**
	 * 	ライブラリ終了処理
	 *
	 * 	@author	minaka1412
	 */
	static void endLib( void);

	/**
	 * 	コンストラクタ
	 *
	 * 	@author	minaka1412
	 */
	Private();

	bool			isLibInit;
	bool			isScreenMonitorSize;

	int				screenWidth;
	int				screenHeight;

	unsigned int	shaderProgramNumber;
	unsigned int	nowShaderNumber;
	unsigned int	attr_uv;
	unsigned int	texture;

	string			windowTitle;
	ScreenMode		screenMode;
	GLFWwindow*		windowHandle;

	float			clearColor[ColorNum];
	vector<LibShader*> shaderProgram;

private:
	enum
	{
		DEFAULT_SCREEN_WIDTH	= 640,
		DEFAULT_SCREEN_HEIGHT	= 480,
	};
};

static LibMain* instance = LibMain::getInstance();

LibMain::LibMain() : p( new Private())
{
	// GLFW初期化
	if( glfwInit() == GL_FALSE)
	{
		LibDebug::errorMessageBox( "Can't initialize GLFW");
	}

	// OpenGLバージョンを設定 (OpenGL ES 2.0)
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

	// ALURE初期化
	if( !alureInitDevice( NULL, NULL)) 
	{
		LibDebug::errorMessageBox( "Can't initialize ALURE!");
	}
}

LibMain::~LibMain()
{
}

void LibMain::initLib( void)
{
	GLFWmonitor*	monitor	= nullptr;

	if( p -> screenMode == ScreenMode::FullScreen)
	{
		monitor	= glfwGetPrimaryMonitor();
	}

	if( p -> isScreenMonitorSize)
	{
		const GLFWvidmode* const mode = glfwGetVideoMode( glfwGetPrimaryMonitor());
		glfwWindowHint( GLFW_RED_BITS,		mode -> redBits);
		glfwWindowHint( GLFW_GREEN_BITS,	mode -> greenBits);
		glfwWindowHint( GLFW_BLUE_BITS,		mode -> blueBits);
		glfwWindowHint( GLFW_REFRESH_RATE,	mode -> refreshRate);
		p -> screenWidth = mode -> width;
		p -> screenHeight = mode -> height;
	}

	atexit( Private::endLib);

	p -> windowHandle = glfwCreateWindow( p -> screenWidth, p -> screenHeight, p -> windowTitle.c_str(), monitor, nullptr);

	if( p -> windowHandle == nullptr)
	{
		LibDebug::errorMessageBox( "Can't Create Window");
	}

	glfwMakeContextCurrent( p -> windowHandle);

	glClearColor( p -> clearColor[Private::ClearColor::Red],
				  p -> clearColor[Private::ClearColor::Blue],
				  p -> clearColor[Private::ClearColor::Green],
				  p -> clearColor[Private::ClearColor::Alpha]);

	glfwSwapInterval( 1);

	if( glewInit() != GLEW_OK)
	{
		LibDebug::errorMessageBox( "Can't initialize GLEW");
	}

	// デフォルトシェーダーの読み込みと設定
	startShaderProgram( loadShaderProgram( "Basic.vsh", "Basic.fsh"));
	getNowShader() -> setAttributePosition( "attr_pos");
	getNowShader() -> setAttributeUV( "attr_uv");
	getNowShader() -> setUniformTexture( "texture");
	getNowShader() -> setUniformHandle( "alpha");
}

void LibMain::setClearColor( float red, float blue, float green, float alpha)
{
	const float color[] = { red, blue, green, alpha };
	for( int i = 0; i < Private::ClearColor::ColorNum; i++)
	{
		assert( !(color[i] > 255 || color[i] < 0));
		p -> clearColor[i] = color[i] / 255.0f;
	}
}

void LibMain::setScreenSize( bool isMonitorSize)
{
	p -> isScreenMonitorSize = isMonitorSize;
}

void LibMain::setScreenSize( int width, int height)
{
	assert( !(width <= 0 || height <= 0));
	p -> screenWidth	 = width;
	p -> screenHeight	 = height;
}

void LibMain::setScreenMode( ScreenMode mode)
{
	p -> screenMode = mode;
}

void LibMain::setWindowTitle( const const char* title)
{
	p -> windowTitle = title;
}

bool LibMain::checkWindowState( void)
{
	return !glfwWindowShouldClose( p -> windowHandle);
}

void LibMain::clear( void)
{
	glClear( GL_COLOR_BUFFER_BIT);
}

void LibMain::draw( void)
{
	glfwSwapBuffers( p -> windowHandle);
	glfwPollEvents();
}

LibShader* LibMain::loadShaderProgram( const char* vertFileName, const char* flagFileName)
{
	LibShader* shader = new LibShader( vertFileName, flagFileName);
	assert( shader != nullptr);
	p -> shaderProgram.push_back( shader);
	p -> shaderProgramNumber++;
	return shader;
}

void LibMain::startShaderProgram( LibShader* shader)
{
	assert( shader != nullptr);
	for( int i = 0; i < p -> shaderProgram.size(); i++)
	{
		if( shader == p -> shaderProgram[i])
		{
			p -> nowShaderNumber = i;
		}
	}
	glUseProgram( shader -> getProgramHandle());
}

LibShader* LibMain::getNowShader( void)
{
	LibShader* shader = p -> shaderProgram[p -> nowShaderNumber];
	assert( shader != nullptr);
	return shader;
}

LibVector2 LibMain::getScreenSize( void) 
{ 
	return LibVector2( p -> screenWidth, p -> screenHeight);
}

LibVector2 LibMain::screenPosToWorldPos( const LibVector2& screenPos)
{
	LibVector2 worldPos;
	worldPos.x = ( screenPos.x / p -> screenWidth) * 2 - 1;
	worldPos.y = ( screenPos.y / p -> screenHeight) * 2 - 1;
	return worldPos;
}

LibMain::Private::Private() : isLibInit( false),
							  isScreenMonitorSize( false),
							  screenWidth( DEFAULT_SCREEN_WIDTH),
							  screenHeight( DEFAULT_SCREEN_HEIGHT),
							  shaderProgramNumber( 0),
							  windowHandle( nullptr),
							  screenMode( ScreenMode::Window),
							  windowTitle( "MyCatGameLibMainrary")
{
	for( int i = 0; i < Private::ClearColor::ColorNum; i++)
	{
		clearColor[i] = 1.0f;
	}
}

void LibMain::Private::endLib( void)
{
	// GLFWの終了処理
	glfwTerminate();
	
	// ALUREの終了処理
	alureShutdownDevice();
}

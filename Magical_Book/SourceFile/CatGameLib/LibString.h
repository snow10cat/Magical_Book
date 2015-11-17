
#ifndef __CAT_GAME_LIBRARY_STRING_H__
#define __CAT_GAME_LIBRARY_STRING_H__

#include <string>
#include "LibSprite.h"
#include "LibSprites.h"

namespace CatGameLib
{

class LibSprites;

class LibString : public LibSprite
{
public:
	static LibString* create(const char* message);
	static void loadTexture(void);

	void setString(const char* message);
	void draw(void);

private:
	static LibSprites* sprites;

	std::string message;

	LibString();
	~LibString();
};

}

#endif // __CAT_GAME_LIBRARY_STRING_H__


#include "Character.h"

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

LibVector2 Character::getPosition( void)
{
	return position;
}

void Character::rotation( Stage* stage)
{
	float angle = 0.0f;

	if( stage -> getRotateDegree() % 90 > 1)
	{
		angle = DEGREE_TO_RADIAN( 1);
	}
	else if( stage -> getRotateDegree() % 90 < -1)
	{
		angle = DEGREE_TO_RADIAN( -1);
	}

	const float sin_f = sinf( angle);
	const float cos_f = cosf( angle);

	const float posX = position.x;
	const float posY = position.y;
	const float cx = LibMain::getInstance() -> getScreenSize().x / 2;
	const float cy = LibMain::getInstance() -> getScreenSize().y / 2;

	position.x = (posX - cx) * cos_f - (posY - cy) * sin_f + cx;
	position.y = (posX - cx) * sin_f + (posY - cy) * cos_f + cy;
}
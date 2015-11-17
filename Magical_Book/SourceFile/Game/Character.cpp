
#include "Character.h"

using namespace std;
using namespace CatGameLib;
using namespace MagicalBook;

LibVector2 Character::getPosition(void)
{
	return position;
}

void Character::rotation(int angle)
{
	float anglef = DEGREE_TO_RADIAN(angle);
	
	const float sin_f = sinf(anglef);
	const float cos_f = cosf(anglef);

	const float posX = position.x;
	const float posY = position.y;
	const float cx = LibMain::getInstance() -> getScreenSize().x / 2;
	const float cy = LibMain::getInstance() -> getScreenSize().y / 2;

	position.x = ((posX - cx) * cos_f - (posY - cy) * sin_f + cx);
	position.y = ((posX - cx) * sin_f + (posY - cy) * cos_f + cy);
}
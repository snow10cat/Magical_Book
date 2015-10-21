
#ifndef __MAGICAL_BOOK_SCENE_H__
#define __MAGICAL_BOOK_SCENE_H__

namespace MagicalBook
{

class Scene
{
public:
	virtual void init(void) = 0;
	virtual void update(void) = 0;

private:

};

}

#endif // __MAGICAL_BOOK_SCENE_H__
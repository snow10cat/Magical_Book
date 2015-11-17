
#ifndef __CAT_GAME_LIBRARY_CIRCLE_H__
#define __CAT_GAME_LIBRARY_CIRCLE_H__

namespace CatGameLib
{

class LibCircle
{
public:
	LibCircle();
	LibCircle(int angle);
	LibCircle(float angle);
	LibCircle(const LibCircle& obj) = delete;
	~LibCircle();

	LibCircle& operator = (int angle);
	LibCircle& operator = (float angle);
	LibCircle& operator = (const LibCircle& c);

	int operator + (int angle);
	float operator + (float angle);
	LibCircle& operator += (int angle);
	LibCircle& operator += (float angle);
	LibCircle& operator += (const LibCircle& c);

	int operator - (int angle);
	float operator - (float angle);
	LibCircle& operator -= (int angle);
	LibCircle& operator -= (float angle);
	LibCircle& operator -= (const LibCircle& c);

	LibCircle& operator *= (int val);
	LibCircle& operator *= (float val);
	LibCircle& operator *= (const LibCircle& c);

	LibCircle& operator /= (int val);
	LibCircle& operator /= (float val);
	LibCircle& operator /= (const LibCircle& c);

	int getDegree(void);
	float getRadian(void);

private:
	class Private;	// Pimpl
	Private *p;
};

}

#endif // __CAT_GAME_LIBRARY_CIRCLE_H__


#include "CatGameLib.h"

#include <new>
#include <cassert>

using namespace std;
using namespace CatGameLib;

const int halfDegree = 180;
const float pi = 3.1415926f;

class LibCircle::Private
{
public:
	int Degree;
	float Radian;

	int radianToDegree( float angle)
	{
		angle = radianWrap( angle);
		return (int)( angle * halfDegree / pi + 0.9);
	}
	float degreeToRadian( int angle)
	{
		angle = degreeWrap( angle);
		return angle * pi / halfDegree;
	}
	int degreeWrap( int x)
	{
		return LibBaseFunc::wrap( x, -halfDegree + 1, halfDegree + 1);
	}
	float radianWrap( float x)
	{
		return LibBaseFunc::wrap( x, -pi + degreeToRadian( 1), pi + degreeToRadian( 1));
	}
};

LibCircle::LibCircle()
{
	p = new(nothrow) Private();
	assert( p != nullptr);
	*this = 0;
}

LibCircle::LibCircle( int angle)
{
	p = new(nothrow) Private();
	assert( p != nullptr);
	*this = angle;
}

LibCircle::LibCircle( float angle)
{
	p = new(nothrow) Private();
	assert( p != nullptr);
	*this = angle;
}

LibCircle::~LibCircle( void)
{
	delete p;
	p = nullptr;
}

LibCircle& LibCircle::operator=( int angle)
{
	assert( p != nullptr);
	p -> Degree = p -> degreeWrap( angle);
	p -> Radian = p -> degreeToRadian( p -> Degree);
	return *this;
}

LibCircle& LibCircle::operator=( float angle)
{
	assert( p != nullptr);
	p -> Radian = p -> radianWrap( angle);
	p -> Degree = p -> radianToDegree( p -> Radian);
	return *this;
}

LibCircle& LibCircle::operator=( const LibCircle& c)
{
	assert( p != nullptr && c.p != nullptr);
	if( this == &c) { return *this; }
	this -> p -> Degree = c.p -> Degree;
	this -> p -> Radian = c.p -> Radian;
	return *this;
}

LibCircle& LibCircle::operator+=( int angle)
{
	assert( p != nullptr);
	p -> Degree = p -> degreeWrap( p -> Degree + angle);
	p -> Radian = p -> degreeToRadian( p -> Degree);
	return *this;
}

LibCircle& LibCircle::operator+=( float angle)
{
	assert( p != nullptr);
	p -> Radian = p -> radianWrap( p -> Radian + angle);
	p -> Degree = p -> radianToDegree( p -> Radian);
	return *this;
}

LibCircle& LibCircle::operator+=( const LibCircle& c)
{
	assert( p != nullptr && c.p != nullptr);
	p -> Degree = p -> degreeWrap( p -> Degree + c.p -> Degree);
	p -> Radian = p -> radianWrap( p -> Radian + c.p -> Radian);
	return *this;
}

int LibCircle::operator+( int angle)
{
	assert( p != nullptr);
	return p -> degreeWrap( p -> Degree + angle);
}

float LibCircle::operator+( float angle)
{
	assert( p != nullptr);
	return p -> radianWrap( p -> Radian + angle);
}

LibCircle& LibCircle::operator-=( int angle)
{
	assert( p != nullptr);
	p -> Degree = p -> degreeWrap( p -> Degree - angle);
	p -> Radian = p -> degreeToRadian( p -> Degree);
	return *this;
}

LibCircle& LibCircle::operator-=( float angle)
{
	assert( p != nullptr);
	p -> Radian = p -> radianWrap( p -> Radian - angle);
	p -> Degree = p -> radianToDegree( p -> Radian);
	return *this;
}

LibCircle& LibCircle::operator-=( const LibCircle& c)
{
	assert( p != nullptr && c.p != nullptr);
	p -> Degree = p -> degreeWrap( p -> Degree - c.p -> Degree);
	p -> Radian = p -> radianWrap( p -> Radian - c.p -> Radian);
	return *this;
}

int LibCircle::operator-( int angle)
{
	assert( p != nullptr);
	return p -> degreeWrap( p -> Degree - angle);;
}

float LibCircle::operator-( float angle)
{
	assert( p != nullptr);
	return p -> radianWrap( p -> Radian - angle);
}

LibCircle& LibCircle::operator*=( int val)
{
	assert( p != nullptr);
	p -> Degree = p -> degreeWrap( p -> Degree * val);
	p -> Radian = p -> degreeToRadian( p -> Degree);
	return *this;
}

LibCircle& LibCircle::operator*=( float val)
{
	assert( p != nullptr);
	p -> Radian = p -> radianWrap( p -> Radian * val);
	p -> Degree = p -> radianToDegree( p -> Radian);
	return *this;
}


LibCircle& LibCircle::operator*=( const LibCircle& c)
{
	assert( p != nullptr);
	p -> Degree = p -> degreeWrap( p -> Degree * c.p -> Degree);
	p -> Radian = p -> radianWrap( p -> Radian * c.p -> Radian);
	return *this;
}

LibCircle& LibCircle::operator/=( int val)
{
	assert( p != nullptr);
	p -> Degree = p -> degreeWrap( p -> Degree / val);
	p -> Radian = p -> degreeToRadian( p -> Degree);
	return *this;
}

LibCircle& LibCircle::operator/=( float val)
{
	assert( p != nullptr);
	p -> Radian = p -> radianWrap( p -> Radian / val);
	p -> Degree = p -> radianToDegree( p -> Radian);
	return *this;
}

LibCircle& LibCircle::operator/=( const LibCircle& c)
{
	assert( p != nullptr);
	p -> Degree = p -> degreeWrap( p -> Degree / c.p -> Degree);
	p -> Radian = p -> radianWrap( p -> Radian / c.p -> Radian);
	return *this;
}

int LibCircle::getDegree( void)
{
	assert( p != nullptr);
	return p -> Degree;
}

float LibCircle::getRadian( void)
{
	assert( p != nullptr);
	return p -> Radian;
}

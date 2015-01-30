#ifndef POINT
#define POINT

#include "../NameSpace.h"

NS_QUICK_GEOM_BEGIN
class Point {
public:
	Point();
	~Point();
public:
	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);

	float getLength() const;
private:
	float _x, _y;
};
NS_QUICK_GEOM_END

#endif
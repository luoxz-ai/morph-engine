#include "IntVector2.hpp"
const IntVector2 IntVector2::zero = IntVector2(0, 0);

//-----------------------------------------------------------------------------------------------
IntVector2::IntVector2(const IntVector2& copy)
	: x(copy.x)
	, y(copy.y) {}


//-----------------------------------------------------------------------------------------------
IntVector2::IntVector2(int initialX, int initialY)
	: x(initialX)
	, y(initialY) {}


//-----------------------------------------------------------------------------------------------
const IntVector2 IntVector2::operator + (const IntVector2& vecToAdd) const {
	return IntVector2(this->x + vecToAdd.x, this->y + vecToAdd.y);
}


//-----------------------------------------------------------------------------------------------
const IntVector2 IntVector2::operator-(const IntVector2& vecToSubtract) const {
	return IntVector2(this->x - vecToSubtract.x, this->y - vecToSubtract.y);
}


//-----------------------------------------------------------------------------------------------
const IntVector2 IntVector2::operator*(int uniformScale) const {
	return IntVector2(this->x*uniformScale, this->y*uniformScale);
}


int IntVector2::operator*(const IntVector2& another) const {
	return x*another.x + y*another.y;
}

//-----------------------------------------------------------------------------------------------
const IntVector2 IntVector2::operator/(int inverseScale) const {
	return IntVector2(this->x / inverseScale, this->y / inverseScale);
}


//-----------------------------------------------------------------------------------------------
void IntVector2::operator+=(const IntVector2& vecToAdd) {
	x = x + vecToAdd.x;
	y = y + vecToAdd.y;
}


//-----------------------------------------------------------------------------------------------
void IntVector2::operator-=(const IntVector2& vecToSubtract) {
	x = x - vecToSubtract.x;
	y = y - vecToSubtract.y;
}


//-----------------------------------------------------------------------------------------------
void IntVector2::operator*=(const int uniformScale) {
	x = x * uniformScale;
	y = y * uniformScale;
}


//-----------------------------------------------------------------------------------------------
void IntVector2::operator/=(const int uniformDivisor) {
	x = x / uniformDivisor;
	y = y / uniformDivisor;
}


//-----------------------------------------------------------------------------------------------
void IntVector2::operator=(const IntVector2& copyFrom) {
	x = copyFrom.x;
	y = copyFrom.y;
}


//-----------------------------------------------------------------------------------------------
const IntVector2 operator*(int uniformScale, const IntVector2& vecToScale) {
	return IntVector2(vecToScale.x * uniformScale, vecToScale.y * uniformScale);
}

int dotProduct(const IntVector2 & a, const IntVector2 & b) {
	return a*b;
}


//-----------------------------------------------------------------------------------------------
bool IntVector2::operator==(const IntVector2& compare) const {
	return x == compare.x && y == compare.y;
}


//-----------------------------------------------------------------------------------------------
bool IntVector2::operator!=(const IntVector2& compare) const {
	return x != compare.x || y != compare.y;
}

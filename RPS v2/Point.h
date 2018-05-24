#pragma once

class Point {
	char y, x;
public:
	//constrctors
	Point() {};
	Point(int _x, int _y) { x = _x; y = _y; }
	//function declaration
	inline char getX() { return x; }
	inline char getY() { return y; }
	inline void setX(char _x) { x = _x; }
	inline void setY(char _y) { y = _y; }
};
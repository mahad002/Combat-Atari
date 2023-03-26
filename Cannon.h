#pragma once
#include "Point.h"
#include <iostream>

using namespace std;

class Cannon1 {
public:
	Point P;
	int direction;
	float* color;
	int can_check = 3;
	bool can;
	bool hit = false;

	bool downshot1(int[][1000], int, int);
	bool rightshot1(int[][1000], int, int);
	bool leftshot1(int[][1000], int, int);
	bool upshot1(int[][1000], int, int);

};
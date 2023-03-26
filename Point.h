#pragma once
#include <iostream>

using namespace std;

class Point {
public:
	int x;
	int y;
	Point() {
		x = 0;
		y = 0;
	}
	Point(int i, int j) {
		x = i;
		y = j;
	}
};

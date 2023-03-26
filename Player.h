#pragma once
#include <iostream>
//#include "Tank.h"
#include "Cannon.h"
#include "Point.h"

using namespace std;

class Player {
public:
	Point p;
	char* U = new char[255];
	int guest;
	int score;
	int lvl;
	int chances;
	//int player;
	int speed;
	int ammo_size;
	int direction;
	Cannon1 shot[3];
	//Tank vehicle;

	Player(int i, int j, int points, int level, int lives, int direction) {
		p.x = i;
		p.y = j;
		score = points;
		lvl = level;
		chances = lives;
		this->direction = direction;
	}

	void down1(int[][1000], int, int);
	void right1(int[][1000], int, int);
	void left1(int[][1000], int, int);
	void up1(int[][1000], int, int);
	void drawCar1(float x, float y, float* color);
	void life(int [][1000]);

};
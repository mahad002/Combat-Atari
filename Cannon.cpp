#include <iostream>
#include "Point.h"
#include "Cannon.h"
#include "util.h"

using namespace std;

bool Cannon1 :: downshot1(int points[][1000], int x_ene, int y_ene) {
	int flag = 0;
	for (int i = P.x; i < P.x + 10; i++) {
		if ((points[i][P.y - 1] == 1) || (P.y) <= 10) {	//checking hurdles
			flag = 1;
			direction = 4;			//if hit with hurdle change direction toward left
			can_check--;
			//cannon = 0;
			break;
		}
	}
	if (flag == 0) {					//if no hurdle it will move
		P.y -= 5;
	}

	for (int i = x_ene - 40; i < x_ene; i++) {
		for (int j = y_ene; j < y_ene + 20; j++) {//checking car hitting with opponent car
			if (P.x == 200 + i && P.y == j) {
				hit = true;
				//P1.score += 20;
				//life_ene();
			}
		}
	}

	glutPostRedisplay();
	return hit;
}

bool Cannon1 :: rightshot1(int points[][1000], int x_ene, int y_ene) {
	int flag = 0;
	for (int i =P.y; i < P.y + 10; i++) {
		if ((points[P.x + 10 + 1][i] == 1) || (400 + P.x) >= 850) {	//checking hurdles
			flag = 1;
			direction = 3;
			can_check--;
			break;
		}
	}
	if (flag == 0) {
		P.x += 5;						//move one point forward
	}
	for (int i = P.x; i < P.x + 20; i++) {
		for (int j = P.y - 20; j < P.y + 20; j++) {
			if (390 + i == 200 + x_ene && j == y_ene) {//checking car hitting with opponent car
				/*P1.score += 20;
				cannon = 0;
				life_ene();*/
				hit = true;
			}
		}
	}
	glutPostRedisplay();
	return hit;
}

bool Cannon1 :: leftshot1(int points[][1000], int x_ene, int y_ene) {
	int flag = 0;
	for (int i = P.y; i < P.y + 10; i++) {
		if ((points[P.x][i] == 1) || (P.x) <= 30) {	//checking hurdles
			flag = 1;
			direction = 2;
			can_check--;
			break;
		}
	}
	if (flag == 0) {
		P.x -= 5;							// if no hurdle move one point 
	}
	for (int i = x_ene; i < x_ene + 30; i++) {
		for (int j = y_ene; j < y_ene + 5; j++) {
			if (P.x == 200 + i && P.y == j) {//checking car hitting with opponent car
				/*P1.score += 20;
				cannon = 0;
				shot = 0;
				life_ene();*/
				hit = true;
			}
		}
	}

	glutPostRedisplay();
	return hit;
}

bool Cannon1 :: upshot1(int points[][1000], int x_ene, int y_ene) {
	int flag = 0;
	for (int i = P.x; i < P.x + 10; i++) {
		if ((points[i][P.y + 5 + 1] == 1) || (P.y) >= 820) {	//checking hurdles
			flag = 1;
			direction = 1;			//if hurdle is there then change direction toward right
			can_check--;
			//glutTimerFunc(10000, downshot, 0);
			break;
		}
	}
	if (flag == 0) {
		P.y += 5;						//if no hurdle is there then move on point
	}

	for (int i = P.x - 40; i < P.x + 120; i++) {
		for (int j = P.y; j < P.y + 20; j++) {
			if (i == 200 + x_ene && j == y_ene) {//checking car hitting with opponent car
				/*P1.score += 20;
				shot = 0;
				cannon = 0;
				life_ene();*/
				hit = true;
			}
		}
	}
	glutPostRedisplay();
	return hit;
}



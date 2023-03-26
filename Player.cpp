#include <iostream>
#include "Player.h"
#include "Point.h"
#include "util.h"
#include <fstream>
#include <Windows.h>


using namespace std;

//void lines() //simulating lines
//{
//	int y;
//	for (y = 0; y < 50; y++)
//	{
//		cout << "-";
//		Sleep(20);
//	}
//	cout << endl;
//}

void Player:: life(int points[][1000]) {
	srand(time(NULL));
	for (int i = 50; i < 400; i += 100) {//making new Map
		for (int j = 760; j > 0; j -= 100)
			points[i][j] = 2;
	}
	for (int i = 460; i < 800; i += 100) {
		for (int j = 60; j < 900; j += 100)
			points[i][j] = 2;
	}

	if (lvl == 1) { //score will also updated after hitting opponent
		score = 0;
	}
	else if (lvl == 2) {
		score = 50;
	}
	else if (lvl == 3) {
		score = 150;
	}
	else if (lvl == 4) {
		score = 400;
	}

	chances--;
	DrawCircle(90, 670, 10, colors[RED]);
	if (chances == 0) {
		if (guest == 1) {
			fstream Booking;
			Booking.open("Booking.txt", ios::app);
			system("PAUSE");
			system("CLS");
			Booking << U << endl;
			Booking << to_string(chances) << "\n";
			Booking << to_string(score) << "\n";
			Booking << to_string(p.x) << "\n";
			Booking << to_string(p.y) << "\n\n";
			string getcontent = "";
			Booking.open("Booking.txt", ios::in);
			system("PAUSE");
			system("CLS");
			//lines();
			cout << "            Rush Hour For Sir Naveed!\n";
			//lines();
			cout << "Your booking Details: \n\n";
			while (!Booking.eof())
			{
				//cout << "234567\n";
				getline(Booking, getcontent);
				//cout << "Hereeeee\n";
				if (U == getcontent)
				{
					cout << " hara\n";
					for (int i = 0; i < 5; i++)
					{
						//will print the details;
						if (i == 0)
							cout << "Username: ";
						else if (i == 1)
							cout << "Chances: ";
						else if (i == 2)
							cout << "Score: ";
						else if (i == 3)
							cout << "x: ";
						else if (i == 4)
							cout << "y: ";
						cout << getcontent << endl;
						getline(Booking, getcontent);
					}
					cout << endl;
					break;
				}
			}
			Booking.close();
		}
		exit(1);
	}
	p.x = rand() % 10, p.y = rand() % 8 /*,x_ene = 0, y_ene = 0*/;
	//enemy = 3;
	direction = 2;
}

void Player :: down1(int points[][1000], int x_ene, int y_ene) {
	int flag = 0;
	for (int i = p.x; i < p.x + 40; i++) {
		if (points[i ][p.y - 1] == 1) {	//checking hurdles
			flag = 1;
			direction = 3;			//if hit with hurdle change direction toward left
			break;
		}
	}
	if (flag == 0) {					//if no hurdle it will move
		p.y--;
	}
	for (int i = p.x; i < p.x + 40; i++) {
		if (points[i][p.y - 1] == 2) {	//checking points
			score++;
		}
	}
	for (int i = x_ene - 40; i < x_ene + 40; i++) {
		for (int j = y_ene; j < y_ene + 20; j++) {//checking car hitting with opponent car
			if (p.x == 200 + i && p.y == j) {
				life(points);
			}
		}
	}
	glutPostRedisplay();
}

void Player :: right1(int points[][1000], int x_ene, int y_ene) {
	int flag = 0;
	for (int i = p.y; i < p.y + 20; i++) {
		if (points[p.x + 30 + 1][i] == 1) {	//checking hurdles
			flag = 1;
			direction = 1;			//changing direction toward down
			break;
		}
	}
	if (flag == 0) {
		p.x++;						//move one point forward
	}
	for (int i = p.y; i < p.y + 20; i++) {
		if (points[p.x + 40 + 1][i] == 2) {	//check points
			score++;
		}
	}
	for (int i = p.x; i < p.x + 40; i++) {
		for (int j = p.y - 20; j < p.y + 20; j++) {
			if (i == 200 + x_ene && j == y_ene) {//checking car hitting with opponent car
				life(points);
			}
		}
	}
	glutPostRedisplay();
}

void Player :: left1(int points[][1000], int x_ene, int y_ene) {
	int flag = 0;
	for (int i = p.y; i < p.y + 20; i++) {
		if (points[p.x ][i] == 1) {	//checking hurdles
			flag = 1;
			direction = 4;				//change direction toward up
			break;
		}
	}
	if (flag == 0) {
		p.x--;							// if no hurdle move one point 
	}
	for (int i = p.y; i < p.y + 40; i++) {
		if (points[10+ p.x - 1][i] == 2) {	//checking points
			score++;
		}
	}
	for (int i = x_ene; i < x_ene + 40; i++) {
		for (int j = y_ene; j < y_ene + 20; j++) {
			if (p.x == 200 + i && p.y == j) {//checking car hitting with opponent car
				life(points);
			}
		}
	}
	glutPostRedisplay();
}

void Player :: up1(int points[][1000], int x_ene, int y_ene) {
	int flag = 0;
	for (int i = p.x; i < p.x + 40; i++) {
		if (points[i][p.y + 20 + 1] == 1) {	//checking hurdles
			flag = 1;
			direction = 2;			//if hurdle is there then change direction toward right
			break;
		}
	}
	if (flag == 0) {
		p.y++;						//if no hurdle is there then move on point
	}

	for (int i = p.x; i < p.x + 40; i++) {
		if (points[i][p.y + 20 + 1] == 2) {	//checking points
			score++;
		}
	}
	for (int i = p.x - 40; i < p.x + 40; i++) {
		for (int j = p.y; j < p.y + 20; j++) {
			if (i == 200 + x_ene && j == y_ene) {//checking car hitting with opponent car
				life(points);
			}
		}
	}
	glutPostRedisplay();
}

void Player :: drawCar1(float x, float y, float* color) //drawCar function given by instructor
{
	DrawSquare(x, y, 20, colors[WHITE]);
	DrawRoundRect(x - 10, y, 40, 10, color, 5);

	if (direction == 2) {
		DrawRoundRect(x + 15, y + 15, 20, 4, colors[RED], 2);
	}
	else if (direction == 3) {
		DrawRoundRect(x - 15, y + 15, 20, 4, colors[RED], 2);
	}

	glutPostRedisplay();
}


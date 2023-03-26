//============================================================================
// Name        : P_i211239_Project.cpp
// Author      : FAST CS Department
// Version     : Sir Naveed
// Copyright   : (c) Reserved
// Description : Basic 2D game...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
#include <time.h>
#include <MMsystem.h>
#include <stdio.h>
#include "util.h"
//#include "Tank.h"
//#include "Point.h"
//#include "Cannon.h"
#include "Player.h"

using namespace std;

//int option = 0;
char* Pass = new char[255];
char* U = new char[255];
int xI = 400, yI = 400;
int x_e = 290, y_e = 400;
int  points[1000][1000], chances_ene = 3, x_ene = 0, y_ene = 0, enemy = 1,
option = 0, rect = 4, rectOpp, gap, guest = 0, shot, shotene, cannon = 0, cannonene=0, k2 = 500, can_check = 3,can_check2=3;
bool can = false, p1 = false, e1 = false, can2 = false;
string song = "Mahad1.wav";
wstring temp = wstring(song.begin(), song.end());
LPCWSTR song1 = temp.c_str();
//bool play = PlaySound(song1, NULL, SND_SYNC);
//play = false;


/*lvl = 0, x_play = 0, y_play = 0, score = 0,*/
/* chances = 3,*/ /*player = 3,*/
/*x_shot = 0, y_shot = 0,*/

class point {
public:
	int x;
	int y;
};

class players {
public:
	point p;
	string username;
	int score;
	int lvl;
	int chances;
	int player;

	players(int i, int j, int points, int level, int lives, int direction) {
		p.x = i;
		p.y = j;
		score = points;
		lvl = level;
		chances = lives;
		player = direction;
	}
};

players P1(0, 0, 0, 1, 3, 3);

Player P2(390, 750, 0, 1, 3, 3);

Player E2(0, 0, 0, 0, 5, 3);

class CANNON {
public:
	int x;
	int y;
	CANNON(int i, int j)
	{
		x = i;
		y = j;
	}
	void RESETSHOT()
	{
		x = 390 + P1.p.x;
		y = 750 + P1.p.y;
	}
	void RESETSHOT1()
	{
		x = 200 + P1.p.x;
		y = 750 + P1.p.y;
	}
};

CANNON SHOT(/*390 + */P1.p.x, /*750 + */P1.p.y);

CANNON SHOTe(x_ene, y_ene);

void Rematch() {
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors

	P1.score = 0;//reseting values
	P1.lvl = 1;
	P1.chances = 3;
	x_ene = 0, y_ene = 0, P1.p.x = 0, P1.p.y = 0;
	enemy = 3;
	P1.player = 2;
	DrawString(290, 740, "---------------------------", colors[ORANGE]);
	DrawString(290, 710, "        RUSH HOUR", colors[ORANGE]);
	DrawString(290, 680, "---------------------------", colors[ORANGE]);
	DrawString(290, 650, "         YOU WON!!!", colors[GREEN]);
	DrawString(290, 620, "1.Rematch", colors[RED]);
	DrawString(290, 590, "2.High Score", colors[RED]);
	DrawString(290, 560, "3.Guest", colors[RED]);
	DrawString(290, 530, "4.Logout", colors[RED]);
	glutSwapBuffers();
}

void loading() // loading
{
	for (int i = 0; i <= 4; i++)
	{
		Sleep(200);
		cout << ".";
	}
	cout << "..";
	Sleep(300);
	cout << "..";
	Sleep(300);
	cout << ".....";
	Sleep(1000);
	cout << endl;
}

void lines() //simulating lines
{
	int y;
	for (y = 0; y < 50; y++)
	{
		cout << "-";
		Sleep(20);
	}
	cout << endl;
}

int highscore() {
	fstream Score;
	int h_score = 0,temp=0;
	string getcontent = "";
	Score.open("Score.txt", ios::in);

	while (!Score.eof()) {
		temp = stoi(getcontent);
		if (h_score < temp) {
			h_score = temp;
		}
	}

	return h_score;
}

//function to check whether username present or not;
bool checklogin(char* U)
{
	bool found = false;
	string x;
	fstream DataBase("DataBase.txt");
	found = false;
	while (!DataBase.eof())
	{
		getline(DataBase, x);
		if (U == x)
		{
			found = true;
			break;
		}
	}

	DataBase.close();
	return found;
}

//function to signup by entering it's username;
void Signup()
{
	string getcontent;
	bool check1;
	fstream DataBase("DataBase.txt", ios::app);
	cout << "Welcome New Member, \nPlease Enter a New Username and Password:\n";
	cout << "Username: ";
	cin >> U;
	check1 = checklogin(U);
	if (check1 == true)
	{
		cout << "Username already Taken! \nRenter! Username: ";
		cin >> U;
	}
	check1 = checklogin(U);
	if (check1 == false)
	{
		cout << "\nPassword: ";
		cin >> Pass;
		DataBase << U << "\n";
		DataBase << Pass << "\n\n";
		cout << "\nYou've Signed Up Successfully!\n";
	}
	else
	{
		cout << "\nSorry Signup Invalid! \nPlease Try Again!\n";
	}

	DataBase.close();
}

//function to enter the user's in the menu who already signed up;
void Login()
{
	bool found = false;
	bool check;
	string exit = "4";
	fstream DataBase("DataBase.txt");
	cout << "Welcome Member, \nPlease Enter Your Username and Password:\n";
	lines();
	cout << "Username: " << endl;
	cin >> U;


	while (!found)
	{
		if (U == exit)
		{
			cout << "You have pressed 4 to exit!\n";
			return;
		}
		check = checklogin(U);
		if (check == false)
		{
			cout << "Sorry Username not found!\n";
			cout << "Username: " << endl;
			cin >> U;
		}
		else
		{
			break;
		}
	}

	cout << "Password: " << endl;
	cin >> Pass;


	while (!found)
	{
		if (Pass == exit)
		{
			cout << "You have pressed 4 to exit!\n";
			return;
		}
		check = checklogin(Pass);
		if (check == false)
		{
			cout << "\nPassword Incorrect!" << endl;
			cout << "Password: " << endl;
			cin >> Pass;
		}
		else
		{
			cout << "\nPassword Correct!" << endl;
			break;
		}
	}
	DataBase.close();
}

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */

void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void life() {
	srand(time(NULL));
	for (int i = 50; i < 400; i += 100) {//making new Map
		for (int j = 760; j > 0; j -= 100)
			points[i][j] = 2;
	}
	for (int i = 460; i < 800; i += 100) {
		for (int j = 60; j < 900; j += 100)
			points[i][j] = 2;
	}

	if (P1.lvl == 1) { //score will also updated after hitting opponent
		P1.score += 0;
	}
	else if (P1.lvl == 2) {
		P1.score += 50;
	}
	else if (P1.lvl == 3) {
		P1.score += 100;
	}
	else if (P1.lvl == 4) {
		P1.score += 150;
	}

	P1.chances--;
	DrawCircle(90, 670, 10, colors[RED]);
	if (P1.chances == 0) {
		option = 10;
		if (guest == 1) {
			fstream Booking;
			Booking.open("Booking.txt", ios::app);
			system("PAUSE");
			system("CLS");
			Booking << U << endl;
			Booking << to_string(P1.chances) << "\n";
			Booking << to_string(P1.score) << "\n";
			Booking << to_string(P1.p.x) << "\n";
			Booking << to_string(P1.p.y) << "\n\n";
			string getcontent = "";
			Booking.open("Booking.txt", ios::in);
			system("PAUSE");
			system("CLS");
			lines();
			cout << "            Rush Hour For Sir Naveed!\n";
			lines();
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
		fstream Score;
		string getcontent = "";
		Score.open("Score.txt", ios::app);

		Score << to_string(P1.score) << endl;
		option = 7;
		//Rematch();
		//exit(1);
	}
	P1.p.x = rand() % 10, P1.p.y = rand() % 8 /*,x_ene = 0, y_ene = 0*/;
	enemy = 3;
	P1.player = 2;
}

void life_ene() {
	srand(time(NULL));
	for (int i = 50; i < 400; i += 100) {//making new Map
		for (int j = 760; j > 0; j -= 100)
			points[i][j] = 2;
	}
	for (int i = 460; i < 800; i += 100) {
		for (int j = 60; j < 900; j += 100)
			points[i][j] = 2;
	}

	chances_ene--;
	//DrawCircle(90, 670, 10, colors[RED]);
	if (chances_ene == 0) {
		option = 7;
		DrawString(295, 790, "You Won!", colors[BLACK]);
		//system("PAUSE");
		fstream Score;
		string getcontent = "";
		Score.open("Score.txt", ios::app);
		//system("PAUSE");
		Score << to_string(P1.score) << endl;
		//exit(1);
	}
	/*P1.p.x = 0, P1.p.y = 0,*/ x_ene = rand() % 100, y_ene = rand() % 8;
	enemy = 3;
	cannon = 0;
	//P1.player = 2;
	//Rematch();
}

void check(int i, int j) {
	if (points[i][j] == 0) {
		points[i][j] = 2;
	}
}

void drawCar(float x, float y, float* color)//drawCar function given by instructor
{
	DrawSquare(x, y, 20, colors[WHITE]);
	DrawRoundRect(x - 10, y, 40, 10, color, 5);

	if (p1 == true) {
		if (P1.player == 2) {
			DrawRoundRect(x + 15, y + 15, 20, 4, colors[RED], 2);
		}
		else if (P1.player == 3) {
			DrawRoundRect(x - 15, y + 15, 20, 4, colors[RED], 2);
		}
	}
	if (e1 == true) {
		if (enemy == 2) {
			DrawRoundRect(x + 15, y + 15, 20, 4, colors[RED], 2);
		}
		else if (enemy == 3) {
			DrawRoundRect(x - 15, y + 15, 20, 4, colors[RED], 2);
		}
	}

	glutPostRedisplay();
}
//===================================================================================================
void Map(int map_x, int l, float* color) {
	int map_y = map_x - 10, space = 150, swidth = l / 2 - space / 2, sheight = 10, k = l + 10, s = l + 10;
	float* scolor = color;

	DrawRectangle(map_x, map_y, swidth, sheight, scolor); // bottom left
	//changing the values of array to 1 where Map is made
	for (int i = map_y; i <= map_y + sheight; i++) {//on mazes the values in array is 1
		for (int j = map_x + 1; j <= map_x + swidth; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x + swidth + space, map_y/**/, swidth, sheight, scolor); // bottom right
	//changing the values of array to 1 where Map is made
	for (int i = map_y; i <= map_y + sheight; i++) {
		for (int j = map_x + 1 + swidth + space; j <= map_x + swidth + space + swidth; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x + swidth * 2 + space, map_y + sheight, sheight * 2, swidth, scolor); // right down
	//changing the values of array to 1 where Map is made
	for (int i = map_y + sheight; i <= map_y + sheight + swidth; i++) {
		for (int j = map_x + swidth * 2 + space; j <= map_x + swidth * 2 + space + sheight * 2; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x + swidth * 2 + space, map_y + sheight + swidth + space, sheight * 2, swidth, scolor); // right up
	//changing the values of array to 1 where Map is made
	for (int i = map_y + sheight + swidth + space; i <= map_y + sheight + swidth + space + swidth; i++) {
		for (int j = map_x + swidth * 2 + space; j <= map_x + swidth * 2 + space + sheight * 2; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x + swidth + space, map_y + k, swidth, sheight, scolor); // top left
	//changing the values of array to 1 where Map is made
	for (int i = map_y + k; i <= map_y + k + sheight; i++) {
		for (int j = map_x + swidth + space; j <= map_x + swidth + space + swidth; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x, map_y + s, swidth, sheight, scolor); // top right
	//changing the values of array to 1 where Map is made
	for (int i = map_y + s; i <= map_y + s + sheight; i++) {
		for (int j = map_x; j <= map_x + swidth; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x - sheight * 2, map_y + sheight + swidth + space, sheight * 2, swidth, scolor); // left up
	//changing the values of array to 1 where Map is made
	for (int i = map_y + sheight + swidth + space; i <= map_y + sheight + swidth + space + swidth; i++) {
		for (int j = map_x - sheight * 2; j <= map_x - sheight * 2 + sheight * 2; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x - sheight * 2, map_y + sheight, sheight * 2, swidth, scolor); // left down
	//changing the values of array to 1 where Map is made
	for (int i = map_y + sheight; i <= map_y + sheight + swidth; i++) {
		for (int j = map_x - sheight * 2; j <= map_x - sheight * 2 + sheight * 2; j++)
			points[j][i] = 1;
	}
}
//===================================================================================================
void Map2(int map_x, int l, float* color) {
	int map_y = map_x - 10, space = 150, swidth = l / 2 - space / 2, sheight = 10, k = l + 10, s = l + 10;
	float* scolor = color;

	DrawRectangle(map_x, map_y, swidth, sheight, scolor); // bottom left
	//changing the values of array to 1 where Map is made
	for (int i = map_y; i <= map_y + sheight; i++) {//on mazes the values in array is 1
		for (int j = map_x + 1; j <= map_x + swidth; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x + swidth + space, map_y/**/, swidth, sheight, scolor); // bottom right
	//changing the values of array to 1 where Map is made
	for (int i = map_y; i <= map_y + sheight; i++) {
		for (int j = map_x + 1 + swidth + space; j <= map_x + swidth + space + swidth; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x + swidth * 2 + space, map_y + sheight, sheight * 2, swidth, scolor); // right down
	//changing the values of array to 1 where Map is made
	for (int i = map_y + sheight; i <= map_y + sheight + swidth; i++) {
		for (int j = map_x + swidth * 2 + space; j <= map_x + swidth * 2 + space + sheight * 2; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x + swidth * 2 + space, map_y + sheight + swidth + space, sheight * 2, swidth, scolor); // right up
	//changing the values of array to 1 where Map is made
	for (int i = map_y + sheight + swidth + space; i <= map_y + sheight + swidth + space + swidth; i++) {
		for (int j = map_x + swidth * 2 + space; j <= map_x + swidth * 2 + space + sheight * 2; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x + swidth + space, map_y + k, swidth, sheight, scolor); // top left
	//changing the values of array to 1 where Map is made
	for (int i = map_y + k; i <= map_y + k + sheight; i++) {
		for (int j = map_x + swidth + space; j <= map_x + swidth + space + swidth; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x, map_y + s, swidth, sheight, scolor); // top right
	//changing the values of array to 1 where Map is made
	for (int i = map_y + s; i <= map_y + s + sheight; i++) {
		for (int j = map_x; j <= map_x + swidth; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x - sheight * 2, map_y + sheight + swidth + space, sheight * 2, swidth, scolor); // left up
	//changing the values of array to 1 where Map is made
	for (int i = map_y + sheight + swidth + space; i <= map_y + sheight + swidth + space + swidth; i++) {
		for (int j = map_x - sheight * 2; j <= map_x - sheight * 2 + sheight * 2; j++)
			points[j][i] = 1;
	}

	DrawRectangle(map_x - sheight * 2, map_y + sheight, sheight * 2, swidth, scolor); // left down
	//changing the values of array to 1 where Map is made
	for (int i = map_y + sheight; i <= map_y + sheight + swidth; i++) {
		for (int j = map_x - sheight * 2; j <= map_x - sheight * 2 + sheight * 2; j++)
			points[j][i] = 1;
	}
}
//===================================================================================================
void drawCannon(float x, float y)//drawCar function given by instructor
{
	DrawCircle(SHOT.x + 390, SHOT.y + 750, 5, colors[WHITE]);

	glutPostRedisplay();
}
//===================================================================================================
void downshot(/*int p*/) {
	int flag = 0;
	for (int i = SHOT.x; i < SHOT.x + 10; i++) {
		if ((points[390 + i][750 + SHOT.y - 1] == 1) || (750 + SHOT.y) <= 10) {	//checking hurdles
			flag = 1;
			shot = 4;			//if hit with hurdle change direction toward left
			can_check--;
			//cannon = 0;
			break;
		}
	}
	if (flag == 0) {					//if no hurdle it will move
		SHOT.y -= 5;
	}

	for (int i = x_ene - 40; i < x_ene+80; i++) {
		for (int j = y_ene; j < y_ene + 20; j++) {//checking car hitting with opponent car
			if (390 + SHOT.x == 200 + i && SHOT.y == j) {
				P1.score += 20;
				shot = 0;
				cannon = 0;
				life_ene();
			}
		}
	}

	glutPostRedisplay();
}
//upward motion
void upshot(/*int p*/) {
	int flag = 0;
	for (int i = SHOT.x; i < SHOT.x + 10; i++) {
		if ((points[390 + i][750 + SHOT.y + 5 + 1] == 1) || (750 + SHOT.y) >= 820) {	//checking hurdles
			flag = 1;
			shot = 1;			//if hurdle is there then change direction toward right
			can_check--;
			//glutTimerFunc(10000, downshot, 0);
			break;
		}
	}
	if (flag == 0) {
		SHOT.y += 5;						//if no hurdle is there then move on point
	}

	for (int i = SHOT.x - 40; i < SHOT.x + 120; i++) {
		for (int j = SHOT.y; j < SHOT.y + 20; j++) {
			if (390 + i == 200 + x_ene && j == y_ene) {//checking car hitting with opponent car
				P1.score += 20;
				shot = 0;
				cannon = 0;
				life_ene();
			}
		}
	}
	glutPostRedisplay();
}
//left motion
void leftshot(/*int p*/)
{
	int flag = 0;
	for (int i = SHOT.y; i < SHOT.y + 10; i++) {
		if ((points[390 + SHOT.x][750 + i] == 1) || (390 + SHOT.x) <= 30) {	//checking hurdles
			flag = 1;
			shot = 2;
			can_check--;
			break;
		}
	}
	if (flag == 0) {
		SHOT.x -= 5;							// if no hurdle move one point 
	}
	for (int i = x_ene; i < x_ene + 30; i++) {
		for (int j = y_ene; j < y_ene + 5; j++) {
			if (390 + SHOT.x == 200 + i && SHOT.y == j) {//checking car hitting with opponent car
				P1.score += 20;
				cannon = 0;
				shot = 0;
				life_ene();
			}
		}
	}
}
//right motion
void rightshot(/*int p*/) {
	int flag = 0;
	for (int i = SHOT.y; i < SHOT.y + 10; i++) {
		if ((points[390 + SHOT.x + 10 + 1][750 + i] == 1) || (400 + SHOT.x) >= 850) {	//checking hurdles
			flag = 1;
			shot = 3;
			can_check--;
			break;
		}
	}
	if (flag == 0) {
		SHOT.x += 5;						//move one point forward
	}
	for (int i = SHOT.x; i < SHOT.x + 40; i++) {
		for (int j = SHOT.y - 20; j < SHOT.y + 40; j++) {
			if (390 + i == 200 + x_ene && j == y_ene) {//checking car hitting with opponent car
				P1.score += 20;
				cannon = 0;
				life_ene();
			}
		}
	}
	glutPostRedisplay();
	/*if (k != l)
	{
		glutTimerFunc(10000, rightshot, 0);
		k++;
	}
	if (k == l) {
		k = 0;
	}*/
}
//===================================================================================================
void down() {
	int flag = 0;
	for (int i = P1.p.x; i < P1.p.x + 40; i++) {
		if (points[i+390][750+P1.p.y - 1] == 1) {	//checking hurdles
			flag = 1;
			P1.player = 3;			//if hit with hurdle change direction toward left
			break;
		}
	}
	if (flag == 0) {					//if no hurdle it will move
		P1.p.y--;
	}
	for (int i = P1.p.x; i < P1.p.x + 40; i++) {
		if (points[390 + i][750 + P1.p.y - 1] == 2) {		//check that there is food or not
			//points[390 + i][750 + P1.p.y - 1] = 3;		//removing of food
			P1.score++;
		}
	}
	for (int i = x_ene - 40; i < x_ene + 40; i++) {
		for (int j = y_ene; j < y_ene + 20; j++) {//checking car hitting with opponent car
			if (390 + P1.p.x == 200 + i && P1.p.y == j) {
				life();
			}
		}
	}
	glutPostRedisplay();
}
//upward motion
void up() {
	int flag = 0;
	for (int i = P1.p.x; i < P1.p.x + 40; i++) {
		if (points[390+i][750+P1.p.y + 20 + 1] == 1) {	//checking hurdles
			flag = 1;
			P1.player = 2;			//if hurdle is there then change direction toward right
			break;
		}
	}
	if (flag == 0) {
		P1.p.y++;						//if no hurdle is there then move on point
	}

	for (int i = P1.p.x; i < P1.p.x + 40; i++) {
		if (points[390 + i][750 + P1.p.y + 20 + 1] == 2) {	//checking food
			//points[390 + i][750 + P1.p.y + 50 + 1] = 3;	//removing food
			P1.score++;
		}
	}
	for (int i = P1.p.x - 40; i < P1.p.x + 40; i++) {
		for (int j = P1.p.y; j < P1.p.y + 20; j++) {
			if (390 + i == 200 + x_ene && j == y_ene) {//checking car hitting with opponent car
				life();
			}
		}
	}
	glutPostRedisplay();
}
//left motion
void left()
{
	int flag = 0;
	for (int i = P1.p.y; i < P1.p.y + 20; i++) {
		if (points[P1.p.x+390][750+i] == 1) {	//checking hurdles
			flag = 1;
			P1.player = 4;				//change direction toward up
			break;
		}
	}
	if (flag == 0) {
		P1.p.x--;							// if no hurdle move one point 
	}
	for (int i = P1.p.y; i < P1.p.y + 40; i++) {
		if (points[400 + P1.p.x - 1][750 + i] == 2) {	//checking food
			//points[390 + P1.p.x - 1][750 + i] = 3;		//removing food
			P1.score++;
		}
	}
	for (int i = x_ene; i < x_ene + 40; i++) {
		for (int j = y_ene; j < y_ene + 20; j++) {
			if (390 + P1.p.x == 200 + i && P1.p.y == j) {//checking car hitting with opponent car
				life();
			}
		}
	}
	glutPostRedisplay();
}
//right motion
void right() {
	int flag = 0;
	for (int i = P1.p.y; i < P1.p.y + 20; i++) {
		if (points[P1.p.x + 30 + 1+390][i+750] == 1) {	//checking hurdles
			flag = 1;
			P1.player = 1;			//changing direction toward down
			break;
		}
	}
	if (flag == 0) {
		P1.p.x++;						//move one point forward
	}
	for (int i = P1.p.y; i < P1.p.y + 20; i++) {
		if (points[390 + P1.p.x + 40 + 1][750 + i] == 2) {	//check food
			//points[390 + P1.p.x + 60 + 1][750 + i] = 3;	//removing food
			P1.score++;
		}
	}
	for (int i = P1.p.x; i < P1.p.x + 40; i++) {
		for (int j = P1.p.y - 20; j < P1.p.y + 20; j++) {
			if (390 + i == 200 + x_ene && j == y_ene) {//checking car hitting with opponent car
				life();
			}
		}
	}
	glutPostRedisplay();
}
//===================================================================================================
void downene() {
	int flag = 0;
	srand(time(NULL));
	for (int i = x_ene; i < x_ene + 40; i++) {
		if (points[200 + i][750 + y_ene - 1] == 1) {	//checking hurdles
			flag = 1;
			enemy = rand() % 5 + 1;			//if hit with hurdle change direction toward left
			if (enemy == 1) {
				enemy = 3;
			}
			break;
		}
	}
	if (flag == 0) {					//if no hurdle it will move
		y_ene--;
	}
	glutPostRedisplay();
}
//upward motion
void upene() {
	int flag = 0;
	srand(time(NULL));
	for (int i = x_ene; i < x_ene + 40; i++) {
		if (points[200 + i][750 + y_ene + 20 + 1] == 1) {	//checking hurdles
			flag = 1;
			enemy = rand() % 5 + 1;			//if hurdle is there then change direction toward right
			if (enemy == 4) {
				enemy = 2;
			}
			break;
		}
	}
	if (flag == 0) {
		y_ene++;						//if no hurdle is there then move on point
	}
	glutPostRedisplay();
}
//left motion
void leftene() {
	int flag = 0;
	srand(time(NULL));
	for (int i = y_ene; i < y_ene + 20; i++) {
		if (points[200 + x_ene - 1][750 + i] == 1) {	//checking hurdles
			flag = 1;
			enemy = rand() % 5 + 1;				//change direction toward up
			if (enemy == 3) {
				enemy = 4;
			}
			break;
		}
	}
	if (flag == 0) {
		x_ene--;							// if no hurdle move one point 
	}
	glutPostRedisplay();
}
//right motion
void rightene() {
	int flag = 0;
	srand(time(NULL));
	for (int i = y_ene; i < y_ene + 20; i++) {
		if ((points[200 + x_ene + 30 + 1][750 + i] == 1) || (200 + x_ene + 30 + 1) >= 850) {	//checking hurdles
			flag = 1;
			enemy = rand() % 5 + 1;			//changing direction toward down
			if (enemy == 2) {
				enemy = 1;
			}
			break;
		}
	}
	if (flag == 0) {
		x_ene++;						//move one point forward
	}
	glutPostRedisplay();
}
//===================================================================================================
void downeneshot() {
	int flag = 0;
	srand(time(NULL));
	for (int i = SHOTe.x; i < SHOTe.x + 40; i++) {
		if (points[200 + i][750 + SHOTe.y - 1] == 1) {	//checking hurdles
			flag = 1;
			can_check2--;
			enemy = 4;
			break;
		}
	}
	if (flag == 0) {					//if no hurdle it will move
		SHOTe.y--;
	}
	for (int i = P1.p.x - 40; i < P1.p.x + 80; i++) {
		for (int j = P1.p.y; j < P1.p.y + 20; j++) {//checking car hitting with opponent car
			if (200 + SHOTe.x == 390 + i && SHOTe.y == j) {
				P1.score -= 10;
				shotene = 0;
				cannonene = 0;
				life();
			}
		}
	}

	glutPostRedisplay();
}
//upward motion
void upeneshot() {
	int flag = 0;
	srand(time(NULL));
	for (int i = SHOTe.x; i < SHOTe.x + 40; i++) {
		if (points[200 + i][750 + SHOTe.y + 20 + 1] == 1) {	//checking hurdles
			flag = 1;
			shotene = 1;
			can_check2--;
			break;
		}
	}
	if (flag == 0) {
		y_ene++;						//if no hurdle is there then move on point
	}
	for (int i = SHOTe.x - 40; i < SHOTe.x + 120; i++) {
		for (int j = SHOTe.y; j < SHOTe.y + 20; j++) {
			if (200 + i == 390 + P1.p.x && j == P1.p.y) {//checking car hitting with opponent car
				P1.score -= 10;
				shotene = 0;
				cannonene = 0;
				life();
			}
		}
	}
	glutPostRedisplay();
}
//left motion
void lefteneshot() {
	int flag = 0;
	srand(time(NULL));
	for (int i = SHOTe.y; i < SHOTe.y + 20; i++) {
		if (points[200 + SHOTe.x - 1][750 + i] == 1) {	//checking hurdles
			flag = 1;
			shotene = 2;
			can_check2--;
			break;
		}
	}
	if (flag == 0) {
		SHOTe.x--;							// if no hurdle move one point 
	}
	for (int i = P1.p.x; i < P1.p.x + 30; i++) {
		for (int j = P1.p.y; j < P1.p.y + 5; j++) {
			if (200 + SHOTe.x == 390 + i && SHOTe.y == j) {//checking car hitting with opponent car
				P1.score -= 10;
				cannonene = 0;
				shotene = 0;
				life();
			}
		}
	}
	glutPostRedisplay();
}
//right motion
void righteneshot() {
	int flag = 0;
	srand(time(NULL));
	for (int i = SHOTe.y; i < SHOTe.y + 20; i++) {
		if ((points[200 + SHOTe.x + 30 + 1][750 + i] == 1) || (200 + SHOTe.x + 30 + 1) >= 850) {	//checking hurdles
			flag = 1;
			shotene = 3;
			can_check2--;
			break;
		}
	}
	if (flag == 0) {
		SHOTe.x++;						//move one point forward
	}
	for (int i = SHOTe.x; i < SHOT.x + 40; i++) {
		for (int j = SHOTe.y - 20; j < SHOTe.y + 40; j++) {
			if (200 + i == 390 + P1.p.x && j == P1.p.y) {//checking car hitting with opponent car
				P1.score -= 10;
				cannonene = 0;
				life();
			}
		}
	}
	glutPostRedisplay();
}
//===================================================================================================

void Menu() {
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
		200.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	DrawString(290, 740, "---------------------------", colors[ORANGE]);
	DrawString(290, 710, "        RUSH HOUR", colors[ORANGE]);
	DrawString(290, 680, "---------------------------", colors[ORANGE]);
	DrawString(290, 650, "1.Start a New Game", colors[RED]);
	DrawString(290, 620, "2.Login", colors[RED]);
	DrawString(290, 590, "3.Signup", colors[RED]);
	DrawString(290, 560, "4.Exit", colors[RED]);
	DrawString(290, 530, "---------------------------", colors[ORANGE]);
	//play = true;
	//bool play = PlaySound(song1, NULL, SND_SYNC);
	glutSwapBuffers();
}

void GameDisplay()/**/ {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	if (option == 1) {
		//left boundary
		for (int i = 30; i < 1000; ++i) {
			points[30][i] = 1;
		}
		//top boundary
		for (int i = 20; i < 1000; ++i) {
			points[i][820] = 1;
		}
		//right boundary
		for (int i = 20; i < 1000; ++i) {
			points[850][i] = 1;
		}
		//down boundary
		for (int i = 20; i < 1000; ++i) {
			points[i][10] = 1;
		}

		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			148.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT); //Update the colors
		//glutDisplayFunc(Menu);

		// calling some functions from util.cpp file to help students
		cout << P1.score << endl;

		//Square at 400,20 position
		//DrawSquare( 400 , 20 ,40,colors[RED]); 
		//Square at 250,250 position
		//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
		//Display P1.score

		DrawString(50, 790, "Score: " + to_string(P1.score), colors[MISTY_ROSE]);
		//Triangle at 300, 450 position
		//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
		// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
		//Circle at 50, 670 position
		//DrawCircle(670,810,10,colors[RED]);
		DrawCircle(670, 800, 10, colors[RED]);
		DrawCircle(650, 800, 10, colors[RED]);
		DrawCircle(630, 800, 10, colors[RED]);
		if (P1.chances == 2) {
			DrawCircle(670, 800, 10, colors[BLACK]);
		}
		else if (P1.chances == 1) {
			DrawCircle(670, 800, 10, colors[BLACK]);
			DrawCircle(650, 800, 10, colors[BLACK]);
		}
		else if (P1.chances == 0) {
			DrawCircle(630, 800, 10, colors[BLACK]);
			DrawCircle(650, 800, 10, colors[BLACK]);
			DrawCircle(630, 800, 10, colors[BLACK]);
		}

		//Line from 550,50 to 550,480 with width 10
		//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float* color);
		//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	

		DrawString(390, 790, "Stage=" + to_string(P1.lvl), colors[MISTY_ROSE]);

		DrawString(700, 790, "lives=" + to_string(P1.chances), colors[MISTY_ROSE]);


		// Drawing Player car
		p1 = true; e1 = false;
		drawCar(P1.p.x + 390, 750 + P1.p.y, colors[GREEN]);

		//P2.drawCar1(P2.p.x, P2.p.y, colors[ORANGE]);

		p1 = false; e1 = true;
		//drawing opponent car
		drawCar(200 + x_ene, 750 + y_ene, colors[RED]);

		//drawing Map
		Map(20, 800, colors[ORANGE]);
		Map(120, 600, colors[BLACK]);
		Map(220, 400, colors[ORANGE]);
		Map(320, 200, colors[RED]);

		//changing value 0 to 2 
		for (int i = 50; i < 400; i += 100) {
			for (int j = 760; j > 0; j -= 100)
				check(i, j);
		}

		//repeat the same procedure for 2nd half
		for (int i = 460; i < 800; i += 100) {
			for (int j = 60; j < 900; j += 100)
				check(i, j);
		}

		//draw square at centre of maze
		DrawSquare(390, 390, 60, colors[GREEN]);

		//validating square
		for (int i = 390; i < 390 + 60; ++i) {
			for (int j = 390; j < 390 + 60; ++j) {
				points[j][i] = 1;
			}
		}

		if (can_check > 0) {
			if (cannon == 1) {
				if (can == true) {
					shot = P1.player;
					can = false;
					SHOT.x = P1.p.x;
					SHOT.y = P1.p.y;
				}
				//drawCannon(SHOT.x + 390, SHOT.y + 750);
				if (shot == 4)
				{
					drawCannon(SHOT.x + 400, SHOT.y + 760);
					//glutTimerFunc(10000, upshot, 0);
					upshot();
				}
				else if (shot == 1)
				{
					drawCannon(SHOT.x + 400, SHOT.y + 760);
					//glutTimerFunc(10000, downshot, 0);
					downshot();
				}
				else if (shot == 2)
				{
					drawCannon(SHOT.x + 420, SHOT.y + 765);
					//glutTimerFunc(10000, rightshot, 0);
					rightshot();
				}
				else if (shot == 3)
				{
					drawCannon(SHOT.x + 380, SHOT.y + 800);
					//glutTimerFunc(10000, leftshot, 0);
					leftshot();
				}
			}
		}
		if (can_check2 > 0) {
			if (cannonene == 1) {
				if (can2 == true) {
					shotene = enemy;
					can2 = false;
					SHOTe.x = x_ene;
					SHOTe.y = y_ene;
				}
				//drawCannon(SHOT.x + 390, SHOT.y + 750);
				if (shotene == 4)
				{
					drawCannon(SHOTe.x + 210, SHOTe.y + 760);
					//glutTimerFunc(10000, upshot, 0);
					upeneshot();
				}
				else if (shotene == 1)
				{
					drawCannon(SHOTe.x + 210, SHOTe.y + 760);
					//glutTimerFunc(10000, downshot, 0);
					downeneshot();
				}
				else if (shotene == 2)
				{
					drawCannon(SHOTe.x + 220, SHOTe.y + 765);
					//glutTimerFunc(10000, rightshot, 0);
					righteneshot();
				}
				else if (shotene == 3)
				{
					drawCannon(SHOTe.x + 190, SHOTe.y + 800);
					//glutTimerFunc(10000, leftshot, 0);
					lefteneshot();
				}
			}
		}
		//k2--;

		if (P1.player == 1/*DOWN KEY*/) {
			down();
			P2.down1(points, x_ene, y_ene);
		}
		else if (P1.player == 2/*RIGHT KEY*/) {
			right();
			P2.right1(points, x_ene, y_ene);
		}
		else if (P1.player == 3/*LEFT KEY*/) {
			P2.left1(points, x_ene, y_ene);
			left();
		}
		else if (P1.player == 4/*UP KEY*/) {
			P2.up1(points, x_ene, y_ene);
			up();
		}

		if (P1.lvl <= 2 || P1.lvl == 4) {
			if (enemy == 1/*DOWN KEY*/) {
				downene();
				E2.down1(points, x_ene, y_ene);
			}
			else if (enemy == 2/*RIGHT KEY*/) {
				rightene();
				E2.right1(points, x_ene, y_ene);
			}
			else if (enemy == 3/*LEFT KEY*/) {
				leftene();
				E2.left1(points, x_ene, y_ene);
			}
			else if (enemy == 4/*UP KEY*/) {
				upene();
				E2.up1(points, x_ene, y_ene);
			}
		}
		//in level 3 car will move with double speed
		if (P1.lvl == 3) {
			if (enemy == 1/*DOWN KEY*/) {
				E2.down1(points, x_ene, y_ene); E2.down1(points, x_ene, y_ene); E2.down1(points, x_ene, y_ene); E2.down1(points, x_ene, y_ene);
				downene();
				downene();
				downene();
				downene();
			}
			else if (enemy == 2/*RIGHT KEY*/) {
				E2.right1(points, x_ene, y_ene); E2.right1(points, x_ene, y_ene); E2.right1(points, x_ene, y_ene); E2.right1(points, x_ene, y_ene);
				rightene();
				rightene();
				rightene();
				rightene();
			}
			else if (enemy == 3/*LEFT KEY*/) {
				E2.left1(points, x_ene, y_ene); E2.left1(points, x_ene, y_ene); E2.left1(points, x_ene, y_ene); E2.left1(points, x_ene, y_ene);
				leftene();
				leftene();
				leftene();
				leftene();
			}
			else if (enemy == 4/*UP KEY*/) {
				E2.up1(points, x_ene, y_ene); E2.up1(points, x_ene, y_ene); E2.up1(points, x_ene, y_ene); E2.up1(points, x_ene, y_ene);
				upene();
				upene();
				upene();
				upene();
			}
		}
		if (P1.score >= 450) {//if score is 556 player won 
			lines();
			cout << "Congratulations you WON!!!!\n";
			lines();
			Rematch();
			//exit(1);
		}
		//else if (P1.score == 250) {//when score is 392 level updated
		//	P1.lvl = 4;
		//	for (int i = 50; i < 400; i += 100) {//updating Map

		//		for (int j = 760; j > 0; j -= 100)
		//			points[i][j] = 2;
		//	}
		//	for (int i = 460; i < 800; i += 100) {
		//		for (int j = 60; j < 900; j += 100)
		//			points[i][j] = 2;
		//	}
		//	P1.score += 100;//bonus score
		//}
		//else if (P1.score == 100) {//when score is 228 level updated
		//	P1.lvl = 3;
		//	for (int i = 50; i < 400; i += 100) {//updating Map
		//		for (int j = 760; j > 0; j -= 100)
		//			points[i][j] = 2;
		//	}
		//	for (int i = 460; i < 800; i += 100) {
		//		for (int j = 60; j < 900; j += 100)
		//			points[i][j] = 2;
		//	}
		//	P1.score += 50;//bonus score
		//}
		//else if (P1.score >= 50) {//when score is 50 level updated
		//	P1.lvl = 2;
		//	for (int i = 50; i < 400; i += 100) {//updating Map
		//		for (int j = 760; j > 0; j -= 100)
		//			points[i][j] = 2;
		//	}
		//	for (int i = 460; i < 800; i += 100) {
		//		for (int j = 60; j < 900; j += 100)
		//			points[i][j] = 2;
		//	}
		//	P1.score += 25;//bonus score
		//}

		/*if (P1.chances == 0) {
			Won();
		}*/
		//readhighscore();//updating highscore

		glutSwapBuffers(); // do not modify this line.. or draw anything below this line

		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT); //Update the colors
		//Red Square
		//DrawSquare(400, 20, 40, colors[RED]);

		//DrawString(50, 800, "Score=0", colors[MISTY_ROSE]);

		//DrawCircle(50, 670, 10, colors[RED]);
		//DrawCircle(70, 670, 10, colors[RED]);
		//DrawCircle(90, 670, 10, colors[RED]);

		//drawCar();
		//glutSwapBuffers(); // do not modify this line..
	}
	else if (option == 7) {
		Rematch();
	}
}

bool flag = true;
bool flag_e = true;

void moveCar() {

	if (xI > 10 && flag) {
		xI -= 10;
		cout << "left ";
		if (xI < 100)

			flag = false;

	}
	else if (xI < 950 && !flag) {
		cout << "right ";
		xI += 10;
		if (xI > 840)
			flag = true;
	}

	if (x_e > 10 && flag) {
		x_e -= 15;
		cout << "\nleft e\n";
		if (x_e < 90)

			flag_e = false;

	}
	else if (x_e < 960 && !flag) {
		cout << "\nright e\n";
		x_e += 15;
		if (x_e > 840)
			flag_e = true;
	}
}

/*
 * Main Canvas drawing function.
 * */

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
  * is pressed from the keyboard
  *
  * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
  *
  * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
  * program coordinates of mouse pointer when key was pressed.
  *
  * */

void NonPrintableKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		x -= 15;
		cout << endl << "Left key pressed!\n";
		P2.direction = 3;
		P1.player = 3;

	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		x += 15;
		cout << endl << "Right key pressed!\n";
		P2.direction = 2;
		P1.player = 2;
	}
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		y += 15;
		cout << endl << "Up key pressed!\n";
		P2.direction = 4;
		P1.player = 4;
	}
	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		y -= 15;
		cout << endl << "Down key pressed!\n";
		P2.direction = 1;
		P1.player = 1;
	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */

void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(1); // exit the program when escape key is pressed.
	}
	else if (key == 'b' || key == 'B') 
	{
		//if b is pressed
		cout << "b pressed" << endl;

	}
	else if (key == 'A' || key == 'a') {
		// what to do when left key is pressed...
		enemy = 3;
		cout << endl << "Left key a pressed!\n";

	}
	else if (key == 'D' || key == 'd') {
		enemy = 2;
		cout << endl << "Right key d pressed!\n";
	}
	else if (key == 'W' || key == 'w') {
		enemy = 4;
		cout << endl << "Up key w pressed!\n";
	}
	else if (key == 'S' || key == 's') {
		enemy = 1;
		cout << endl << "Down key s pressed!\n";
	}
	else if (key == 49) {//used in menu
		// glutDisplayFunc(GameDisplay);
		option = 1;
	}
	else if (key == 50) {//used in menu
		option = 2;
		//highscores();
	}
	else if (key == 51) {//used in menu
		option = 3;
		//help();
	}
	else if (key == 52) {//used in menu & stop
		if (guest == 0) {
			fstream Booking;
			Booking.open("Booking.txt", ios::app);
			system("PAUSE");
			system("CLS");
			Booking << U << endl;
			Booking << to_string(P1.chances) << "\n";
			Booking << to_string(P1.score) << "\n";
			Booking << to_string(x_ene) << "\n";
			Booking << to_string(y_ene) << "\n\n";
			//fstream Booking;
			string getcontent = "";
			Booking.open("Booking.txt", ios::in);
			system("PAUSE");
			system("CLS");
			lines();
			cout << "            Rush Hour For Sir Naveed!\n";
			lines();
			cout << "Your booking Details: \n\n";
			while (!Booking.eof())
			{
				getline(Booking, getcontent);
				if (U == getcontent)
				{
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
					//break;
				}
			}
			Booking.close();
		}
		exit(1);
	}
	else if (key == 53) {//used in stop
		option = 4;
		//restart();
	}
	else if (key == 'p' || key == 'P') {//game pause when p is pressed
		option = 6;
		//stop();
	}
	else if (key == 32) {       // speed up player
		if (P1.player == 2) {
			P1.p.x += 10;
		}
		else if (P1.player == 1) {
			P1.p.y -= 10;
		}
		else if (P1.player == 3) {
			P1.p.x -= 10;
		}
		else if (P1.player == 4) {
			P1.p.y += 10;
		}
	}
	else if (key == 'r' || key == 'R') {        //speed up enemy
		if (enemy == 2) {
			x_ene += 10;
		}
		else if (enemy == 1) {
			y_ene -= 10;
		}
		else if (enemy == 3) {
			x_ene -= 10;
		}
		else if (enemy == 4) {
			y_ene += 10;
		}
	}
	else if (key == 'M' || key == 'm') {
		can = true;
		//k2 = 500;
		cannon = 1;
		can_check = 3;
		SHOT.RESETSHOT();
	}
	else if (key == 'T' || key == 't') {
		can2 = true;
		//k2 = 500;
		cannonene = 1;
		can_check2 = 3;
		SHOTe.RESETSHOT1();
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

	// implement your functionality here
	moveCar();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */

void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}

void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */

void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		cout << "Right Button Pressed" << endl;

	}
	glutPostRedisplay();
}

/*
 * our gateway main function
 * */

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int x_check = 0, y_check = 0;
	//bool play = PlaySound(song1, NULL, SND_SYNC);
	string exit = "4";

	lines();
	cout << "            Rush Hour For Sir Naveed!\n";
	lines();
	//prints the main menu;
	cout << "1.Login\n";
	cout << "2.Sign-Up\n";
	cout << "3.Customize Map\n";
	cout << "4.As Guest\n";
	cout << "5.Exit\n\n";
	lines();
	x_check = 0;
	cout << "Option: ";
	cin >> x_check;
	lines();
	do
	{
		switch (x_check)
		{
		case 1:
		{
			Login();
			fstream Booking;
			string getcontent = "";
			Booking.open("Booking.txt", ios::in);
			system("PAUSE");
			system("CLS");
			lines();
			cout << "            Rush Hour For Sir Naveed!\n";
			lines();
			cout << "Your booking Details: \n\n";
			while (!Booking.eof())
			{
				getline(Booking, getcontent);
				if (U == getcontent)
				{
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
					//break;
				}
			}
			lines();
			system("PAUSE");
			system("CLS");
			//prints a menu after we're logged in;
			//check for if user enters the main menu option;
			y_check = 0;
			x_check = 0;
			break;
		}
		break;
		case 2:
		{
			x_check = 0;
			Signup();
			break;
		}
		case 3: {
			//print colors menu
			cout << "1.Red\n";
			cout << "2.Orange\n";
			cout << "3.Brown\n";
			cout << "4.Green\n";
			cout << "5.Blue\n\n";
			break;
		}
		case 4:
		{
			guest = 1;
			break;
		}
		case 5:
		{
			x_check = 0;
			return 0;
			//break;
		}
		//break;
		default:
		{
			cout << "Not An Option!\n"; x_check = 0;
			cin.clear();
			cin.ignore();
			break;
		}
		}
		lines();
		system("PAUSE");
		system("CLS");
	} while (isdigit(x_check));

	if (U == exit || Pass == exit)
	{
		return 0;
	}


	int width = 840, height = 840; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour for Naveed Ahmad"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	//Menu();//menu will display before game display
	//glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	Menu();

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse


	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();

	if (guest == 0) {
		fstream Booking;
		Booking.open("Booking.txt", ios::app);
		system("PAUSE");
		system("CLS");
		Booking << U << endl;
		Booking << to_string(P1.chances) << "\n";
		Booking << to_string(P1.score) << "\n";
		Booking << to_string(x_ene) << "\n";
		Booking << to_string(y_ene) << "\n\n";
	}


	//Booking.close();

	string getcontent = "";
	fstream Booking;
	Booking.open("Booking.txt", ios::in);
	system("PAUSE");
	system("CLS");
	lines();
	cout << "                RUSH HOUR!\n";
	lines();
	cout << "Old Games Details: \n\n";
	while (!Booking.eof())
	{
		getline(Booking, getcontent);
		if (U == getcontent)
		{
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
			//break;
		}
	}
	Booking.close();

	delete[] U;
	delete[] Pass;

	return 0;
}

#endif /* RushHour_CPP_ */

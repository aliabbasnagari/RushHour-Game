//============================================================================
// Ali Abbas - 21I-2503 - "H" , Semester - 1 Final Project
// Name        : game.cpp
// Author      : FAST CS Department
// Version     : 1.0.0
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// Signatures / prototypes of all Functions
void SetCanvasSize(int, int);
void drawPlayerCar();
void drawOpponentCar(int, int);
void drawPass(int, int);
void drawTree(int, int);
void drawBoxes(int, int);
void dropPoint();
void dispItems();
void calculateDistances();
void moveOcar(int&, int&, char, bool&);
void setDrop();
void randGenerator(int arr[][2], int);
void GameDisplay();
void initiateValues();
void NonPrintableKeys(int, int, int);
void Timer(int);
void moveTimer(int);
void PrintableKeys(unsigned char, int, int);
void MousePressedAndMoved(int, int);
void MouseMoved(int, int);
void MouseClicked(int, int, int , int );
void carCollision();
void leaderBoard();
void saveScore(int*, string);
void resetData();



/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Ali Abbas"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}

int xI = 0, yI = 760, noBul = 0, noPass = 0, noTree = 0, noBox = 0, noOcar = 0, carType = 1, dPass = 0, remPass = 0,
seconds = 0, minutes = 0, score = 0, mX = 0, mY = 0;
string playerName = "";
bool onBoard = false, gameOver = false, isCollided = false, dispMenu = true;
int menuChoice = 0;

// Data of Passengers
int passCD[5][2] = { 0 };
int passD[5] = { 0 };
// Data of Trees
int treeCD[5][2] = { 0 };
int treeD[5] = { 0 };
// Data of Boxes
int boxCD[5][2] = { 0 };
int boxD[5] = { 0 };
// Data of Buildings
int bulCD[140][2] = { 0 };
int bulD[140] = { 0 };
// Data of opponent cars
int ocarCD[5][2] = { 0 };
int ocarD[5] = { 0 };
int ocarSpeed = 5;
bool ocarDir[5] = { 1 };
// Data of Drop Point
int dropX = 0, dropY = 0, dropD = 0;

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

// This function draws CAR
void drawPlayerCar() {
	if (carType == 1) {
		// DrawRectangle(xI + 2, yI + 10, 36, 15, colors[ORANGE]);
		DrawRoundRect(xI + 2, yI + 10, 36, 15, colors[ORANGE], 3);
		DrawRectangle(xI + 10, yI + 35, 20, 5, colors[ORANGE]);
	} else {
		// DrawRectangle(xI + 2, yI + 10, 36, 15, colors[RED]);
		DrawRoundRect(xI + 2, yI + 10, 36, 15, colors[RED], 3);
		DrawRectangle(xI + 10, yI + 35, 20, 5, colors[RED]);
	}

	DrawRectangle(xI + 5, yI, 8, 10, colors[SLATE_GRAY]);
	DrawRectangle(xI + 27, yI, 8, 10, colors[SLATE_GRAY]);
	DrawRectangle(xI + 10, yI + 25, 20, 12, colors[AQUA_MARINE]);
	DrawTriangle(xI + 5, yI + 25, xI + 10, yI + 25, xI + 10, yI + 37, colors[AQUA_MARINE]);
	DrawTriangle(xI + 29, yI + 25, xI + 29, yI + 37, xI + 35, yI + 25, colors[AQUA_MARINE]);
	DrawCircle(xI + 9, yI + 17, 3, colors[AQUA_MARINE]);
	DrawCircle(xI + 31, yI + 17, 3, colors[AQUA_MARINE]);
	glutPostRedisplay();
}

// This Function Draws obstacle/opponent CAR
void drawOpponentCar(int xc, int yc) {
	if (carType == 1) {
		// DrawRectangle(xc + 2, yc + 10, 36, 15, colors[MAGENTA]);
		DrawRoundRect(xc + 2, yc + 10, 36, 15, colors[MAGENTA], 3);
		DrawRectangle(xc + 10, yc + 35, 20, 5, colors[MAGENTA]);
	} else {
		// DrawRectangle(xc + 2, yc + 10, 36, 15, colors[YELLOW]);
		DrawRoundRect(xc + 2, yc + 10, 36, 15, colors[YELLOW], 3);
		DrawRectangle(xc + 10, yc + 35, 20, 5, colors[YELLOW]);
	}

	DrawRectangle(xc + 5, yc, 8, 10, colors[SLATE_GRAY]);
	DrawRectangle(xc + 27, yc, 8, 10, colors[SLATE_GRAY]);
	DrawRectangle(xc + 10, yc + 25, 20, 12, colors[AQUA_MARINE]);
	DrawTriangle(xc + 5, yc + 25, xc + 10, yc + 25, xc + 10, yc + 37, colors[AQUA_MARINE]);
	DrawTriangle(xc + 29, yc + 25, xc + 29, yc + 37, xc + 35, yc + 25, colors[AQUA_MARINE]);
	DrawCircle(xc + 9, yc + 17, 3, colors[AQUA_MARINE]);
	DrawCircle(xc + 31, yc + 17, 3, colors[AQUA_MARINE]);
	glutPostRedisplay();
}

// This function draws PASSENGERS
void drawPass(int xc, int yc) {
	DrawCircle(xc + 20, yc + 35, 5, colors[BLACK]); // Head
	DrawLine(xc + 20, yc + 10, xc + 20, yc + 30, 3, colors[BLACK]); // Body
	DrawLine(xc + 10, yc, xc + 20, yc + 10, 4, colors[BLACK]); // Left Leg
	DrawLine(xc + 30, yc, xc + 20, yc + 10, 4, colors[BLACK]); // Right Leg
	DrawLine(xc + 10, yc + 20, xc + 20, yc + 30, 4, colors[BLACK]); // Left Arm
	DrawLine(xc + 30, yc + 20, xc + 20, yc + 30, 4, colors[BLACK]); // Right Arm
	glutPostRedisplay();
}

// This function draws TREES
void drawTree(int xc, int yc) {
	DrawTriangle(xc, yc + 10, xc + 20, yc + 40, xc + 40, yc + 10, colors[GREEN]);
	DrawSquare(xc + 15, yc, 10, colors[BROWN]);
	glutPostRedisplay();
}

// This function draws BOXES (Obstacle)
void drawBoxes(int xc, int yc) {
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawSquare(xc, yc, 40, colors[SANDY_BROWN]);
	DrawRectangle(xc + 10, yc, 5, 40, colors[DARK_GRAY]);
	DrawRectangle(xc + 25, yc, 5, 40, colors[DARK_GRAY]);
	glutPostRedisplay();
}

// This function draws DROP POINT
void dropPoint() {
	if (!(dropX == 0 && dropY == 0)) {
		DrawCircle(dropX + 20, dropY + 25, 15, colors[BLUE]);
		DrawCircle(dropX + 20, dropY + 25, 5, colors[WHITE]);
		DrawTriangle(dropX + 20, dropY, dropX + 6, dropY + 20, dropX + 34, dropY + 20, colors[BLUE]);
	}
	glutPostRedisplay();
}

// This function displays TIME ,SCORE and other text on screen
void dispItems() {
	string escFun = (menuChoice == 0) ? "Exit" : "Main Menu";
	if (!dispMenu && !gameOver) {
		string carStatus = onBoard ? " On board" : " Empty";
		DrawString(50, 810, "Player Name:  " + playerName, colors[MISTY_ROSE]);
		DrawString(810, 720, "Car status: " + carStatus, colors[MISTY_ROSE]);
		DrawString(810, 690, to_string(minutes) + " : " + to_string(seconds), colors[MISTY_ROSE]);
		DrawString(810, 660, "Score: " + to_string(score), colors[MISTY_ROSE]);
	}
	// If Game Over This functions displays message
	if (gameOver && !dispMenu) {
		DrawString(450, 450, "GAME OVER", colors[MISTY_ROSE]);
		DrawString(450, 400, "Score: " + to_string(score), colors[MISTY_ROSE]);
		if (score > 100) {
			DrawString(450, 350, "You Win!", colors[MISTY_ROSE]);
		}
	}
	DrawString(810, 100, "Ali Abbas Nagari", colors[MISTY_ROSE]);
	DrawString(810, 80, "      Games", colors[MISTY_ROSE]);
	DrawString(810, 10, "ESC -> " + escFun, colors[MISTY_ROSE]);
	glutPostRedisplay();
}

// This function keeps track of all objects
void calculateDistances() {
	// For Building
	for (int i = 0; i < noBul; i++) {
		bulD[i] = sqrt(pow((bulCD[i][0]) - xI, 2) + pow((bulCD[i][1]) - yI, 2));
	}
	// For Passanger
	for (int i = 0; i < noPass; i++) {
		passD[i] = sqrt(pow(passCD[i][0] - xI, 2) + pow((passCD[i][1]) - yI, 2));
	}
	// For tree
	for (int i = 0; i < noTree; i++) {
		treeD[i] = sqrt(pow(treeCD[i][0] - xI, 2) + pow((treeCD[i][1]) - yI, 2));
	}
	// For Box
	for (int i = 0; i < noBox; i++) {
		boxD[i] = sqrt(pow(boxCD[i][0] - xI, 2) + pow((boxCD[i][1]) - yI, 2));
	}
	// For Opponent Car
	for (int i = 0; i < noOcar; i++) {
		ocarD[i] = sqrt(pow(ocarCD[i][0] - xI, 2) + pow((ocarCD[i][1]) - yI, 2));
	}
	carCollision(); // Check if car collides with another car (player car) or car is overtaking
	// For Drop Point
	if (!(dropX == 0 && dropY == 0)) {
		dropD = sqrt(pow(dropX - xI, 2) + pow(dropY - yI, 2));
	}
}

// This function moves obstacle cars randomly
void moveOcar(int& xc, int& yc, char axis, bool &dir) {	
	if (axis == 'x') {
		if (xc > 10 && dir) {
			xc -= ocarSpeed;
			// cout << "going left, ";
			if (xc < 80) {
				if (isCollided) {
					isCollided =  false;
				}
				dir = false;
			}
		} else if (xc < 800 && !dir) {
			xc += ocarSpeed;
			//cout << "going right, ";
			if (xc > 700) {
				if (isCollided) {
					isCollided = false;
				}
				dir = true;
			}
		}
	} else {
		if (yc > 10 && dir) {
			yc -= ocarSpeed;
			// cout << "going left, ";
			if (yc < 80) {
				if (isCollided) {
					isCollided = false;
				}
				dir = false;
			}
		} else if (yc < 800 && !dir) {
			yc += ocarSpeed;
			//cout << "going right, ";
			if (yc > 700) {
				if (isCollided) {
					isCollided = false;
				}
				dir = true;
			}
		}
	}
}

/* This function Sets Random coordinates for drop point which is not
 in a occupied place or too near pick up point */
void setDrop() {
	int xCord = (((rand() % 18) + 1) * 40), yCord = (((rand() % 18) + 1) * 40), j = 0;
	while (j < noBul) {
		int distance = sqrt(pow((xCord - xI), 2) + pow((yCord - yI), 2));
		if ((xCord == bulCD[j][0] && yCord == bulCD[j][1]) || (j < noPass && xCord == passCD[j][0] && yCord == passCD[j][1]) ||
			(j < noTree && xCord == treeCD[j][0] && yCord == treeCD[j][1]) || (j < noBox && xCord == boxCD[j][0] && yCord == boxCD[j][1]) || distance < 112) {
			xCord = (((rand() % 18) + 1) * 40);
			yCord = (((rand() % 18) + 1) * 40);
			j = -1;
		}
		j++;
	}
	dropX = xCord;
	dropY = yCord;
}

/*
 * Main Canvas drawing function.
 * */
void GameDisplay()/**/ {
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0.2/*Red Component*/, 0.2,	//148.0/255/*Green Component*/,
		0.2/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour

	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	// Condition to display menu options on canvas
	if (dispMenu && !(menuChoice == 2 || menuChoice == 3)) {
		// Display menu options based on inputs taken from printable keys
		DrawString(60, 760, " __________Main Menu__________", colors[WHITE]);
		// Sub menu choices
		if (menuChoice == 0) {
			int btn_color[4] = { 0 }, color[2] = {DARK_RED, RED};
			btn_color[0] = (mX >= 20 && mX <= 370) && (mY >= 160 && mY <= 200) ? color[0] : color[1];
			btn_color[1] = (mX >= 20 && mX <= 370) && (mY >= 210 && mY <= 250) ? color[0] : color[1];
			btn_color[2] = (mX >= 20 && mX <= 370) && (mY >= 260 && mY <= 300) ? color[0] : color[1];
			btn_color[3] = (mX >= 20 && mX <= 370) && (mY >= 310 && mY <= 350) ? color[0] : color[1];
			
			DrawString(60, 700, "Press: ", colors[WHITE]);
			DrawRoundRect(50, 640, 350, 40, colors[btn_color[0]], 10);
			DrawString(60, 650, "1 - Continue to play game.", colors[WHITE]);
			DrawRoundRect(50, 590, 350, 40, colors[btn_color[1]], 10);
			DrawString(60, 600, "2 - Display leader board.", colors[WHITE]);
			DrawRoundRect(50, 540, 350, 40, colors[btn_color[2]], 10);
			DrawString(60, 550, "3 - Instructions.", colors[WHITE]);
			DrawRoundRect(50, 490, 350, 40, colors[btn_color[3]], 10);
			DrawString(60, 500, "4 - Exit.", colors[WHITE]);
		}
		// Sub menu choices
		if (menuChoice == 1) {
			DrawString(30, 700, ">>  Enter your name: " + playerName + " |", colors[WHITE]);
			DrawString(30, 650, "info: name format, firstname_lastname." , colors[RED]);
			DrawString(30, 600, "info: Press Enter after entering name." , colors[RED]);
		}
		// Sub menu choices
		if (menuChoice == 5) {
			DrawString(30, 700, "Press: ", colors[WHITE]);
			DrawString(30, 650, "1 - Random Taxi.", colors[WHITE]);
			DrawString(30, 600, "2 - Select Taxi.", colors[WHITE]);
		}
		// Sub menu choices
		if (menuChoice == 6) {
			DrawString(30, 700, "Press: ", colors[WHITE]);
			DrawString(30, 650, "1 - Yellow Taxi.", colors[WHITE]);
			DrawString(30, 600, "2 - Red Taxi.", colors[WHITE]);
		}
		DrawString(30, 450, "__________________________________", colors[WHITE]);
	} else if (dispMenu && menuChoice == 2) {
		leaderBoard();
	} else if (dispMenu && menuChoice == 3) {
			DrawString(30, 700, ">> Use Arrow keys to control the Taxi. ", colors[WHITE]);
			DrawString(30, 650, ">> Avoid collision with Object (Other Taxi's, Boxes, Trees) they will reduce score.", colors[WHITE]);
			DrawString(30, 600, ">> Go near persons waiting around and press Spacebar to pick them.", colors[WHITE]);
			DrawString(30, 550, ">> Now take the passanger to the destination marked and receive money.", colors[WHITE]);
			DrawString(30, 500, ">> Over take a car and get 1 extra point.", colors[WHITE]);
	}
	// Game Starts form here
	if (!gameOver && !dispMenu) { // Condition to start game
		// Background Layer
		calculateDistances();
		for (unsigned int i = 0; i < 20; i++) {
			DrawRectangle(i * 40, 0, 40, 800, colors[WHITE]);
		}

		for (int i = 0; i < noBul; i++) {
			///DrawSquare(bulCD[i][0], bulCD[i][1], 40, colors[BLACK]);
			
			DrawRectangle(bulCD[i][0], bulCD[i][1], 20, 10 , colors[BROWN]);
			DrawRectangle(bulCD[i][0]+20, bulCD[i][1], 20, 10 , colors[BROWN]);
			
			DrawRectangle(bulCD[i][0], bulCD[i][1]+10, 10, 10 , colors[BROWN]);
			DrawRectangle(bulCD[i][0]+10, bulCD[i][1]+10, 20, 10 , colors[BROWN]);
			DrawRectangle(bulCD[i][0]+30, bulCD[i][1]+10, 10, 10 , colors[BROWN]);
			
			DrawRectangle(bulCD[i][0], bulCD[i][1] + 20, 20, 10 , colors[BROWN]);
			DrawRectangle(bulCD[i][0]+20, bulCD[i][1] + 20, 20, 10 , colors[BROWN]);
			
			DrawRectangle(bulCD[i][0], bulCD[i][1]+30, 10, 10 , colors[BROWN]);
			DrawRectangle(bulCD[i][0]+10, bulCD[i][1]+30, 20, 10 , colors[BROWN]);
			DrawRectangle(bulCD[i][0]+30, bulCD[i][1]+30, 10, 10 , colors[BROWN]);
			//DrawSquare(bulCD[i][0]+10, bulCD[i][1]+10, 20, colors[BROWN]);
		}
		
		for (int i = 0; i < noTree; i++) {
			if (!(treeCD[i][0] == 0 && treeCD[i][1] == 0)) {
				drawTree(treeCD[i][0], treeCD[i][1]);
			}
		}

		for (unsigned int i = 0; i < noOcar; i++) {
			if (!(ocarCD[i][0] == 0 && ocarCD[i][1] == 0)) {
				drawOpponentCar(ocarCD[i][0], ocarCD[i][1]);
			}
		}

		for (int i = 0; i < noPass; i++) {
			if (!(passCD[i][0] == 0 && passCD[i][1] == 0)) {
				drawPass(passCD[i][0], passCD[i][1]);
			}
		}
		
		for (int i = 0; i < noBox; i++) {
			if (!(boxCD[i][0] == 0 && boxCD[i][1] == 0)) {
				drawBoxes(boxCD[i][0], boxCD[i][1]);
			}
		}
		
		dropPoint();
		// Foreground
		drawPlayerCar();
	}
	dispItems();
	glutSwapBuffers(); // do not modify this line..
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).

 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	seconds++;
	if (seconds == 60) {
		minutes++;
		seconds = 0;
	}
	if (minutes == 1 && seconds == 1 && !gameOver) {
		gameOver = true;
		saveScore(&score, playerName);
	}

	if (!gameOver && !dispMenu) {
		glutTimerFunc(1000, Timer, 0);
	}

	// implement your functionality here
	// moveCar();
	// once again we tell the library to call our Timer function after next 1000/FPS
}


void moveTimer(int x) {
	for (int i = 0; i < noOcar; i++) {
		char axis = ' ';
		if (i == 0 || i == 2 || i == 4) {
			axis = 'x';
		} else {
			axis = 'y';
		}
		moveOcar(ocarCD[i][0], ocarCD[i][1], axis, ocarDir[i]);
	}
	// once again we tell the library to call our Timer function after next 1000/FPS
	if (!gameOver && !dispMenu) {
		glutTimerFunc(50, moveTimer, 0);
	}
}


void randGenerator(int arr[][2], int no) {
	for (int i = 0; i < no; i++) {
		int xCord = (((rand() % 18) + 1) * 40), yCord = (((rand() % 18) + 1) * 40), j = 0;
		while (j < noBul) {
			if ((xCord == bulCD[j][0] && yCord == bulCD[j][1]) || (j < noPass && xCord == passCD[j][0] && yCord == passCD[j][1]) ||
			   (j < noTree && xCord == treeCD[j][0] && yCord == treeCD[j][1]) || (j < noBox && xCord == boxCD[j][0] && yCord == boxCD[j][1]) || 
			   (j < noOcar && xCord == ocarCD[j][0] && yCord == ocarCD[j][1])) {
				xCord = (((rand() % 18) + 1) * 40);
				yCord = (((rand() % 18) + 1) * 40);
				j = -1;
			}
			j++;
		}
		arr[i][0] = xCord;
		arr[i][1] = yCord;
	}
}

// Function for initiating initial values
void initiateValues() {
	noBul = (rand() % 61) + 50;
	noPass = (rand() % 3) + 3;
	noTree = (rand() % 3) + 3;
	noBox = (rand() % 3) + 3;
	noOcar = (rand() % 3) + 1;
	remPass = noPass;

	// Generate random coordinates for BUILDINGS
	randGenerator(bulCD, noBul);

	// Generate random coordinates for PASSENGERS
	randGenerator(passCD, noPass);

	// Generate random coordinates for TREES
	randGenerator(treeCD, noTree);

	// Generate random coordinates for BOXES
	randGenerator(boxCD, noBox);

	// Generate random coordinates for opponent cars
	randGenerator(ocarCD, 5);

	// Starts timer functions
	glutTimerFunc(1000.0, Timer, 0);
	glutTimerFunc(50.0, moveTimer, 0);
}

void resetData() {
	menuChoice = 0; // Menu choice back to main menu
	score = 0; // Reset score in each run
	minutes = 0; // Reset minutes in each run
	seconds = 0; // Reset seconds in each run
	dropX = 0, dropY = 0; // Reset drop position in each run
	xI = 0, yI = 760; // Reset player car coordinates in each run
	playerName = "";  // Reset player name in each run
	onBoard = false, gameOver = false, isCollided = false, dispMenu = true;; // Reset other parameters
}

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
	bool trigRight = true, trigLeft = true, trigUp = true, trigDown = true;
	int speed = 10;
	char cO = ' ';
	if (carType == 1) {
		speed = 20;
	} else {
		speed = 10;
	}

	for (int i = 0; i < noBul; i++) {

		if (bulCD[i][0] - xI == 40 && bulD[i] < 56) { trigRight = false; }
		if (i < noPass && passCD[i][0] - xI == 40 && passD[i] < 56) { cO = 'a'; trigRight = false; }
		if (i < noTree && treeCD[i][0] - xI == 40 && treeD[i] < 56) { cO  = 'b'; trigRight = false; }
		if (i < noBox && boxCD[i][0] - xI == 40 && boxD[i] < 56) { cO  = 'b'; trigRight = false; }

		if (bulCD[i][0] - xI == -40 && bulD[i] < 56) { trigLeft = false; }
		if (i < noPass && passCD[i][0] - xI == -40 && passD[i] < 56) { cO  = 'c'; trigLeft = false; }
		if (i < noTree && treeCD[i][0] - xI == -40 && treeD[i] < 56) { cO  = 'd'; trigLeft = false; }
		if (i < noBox && boxCD[i][0] - xI == -40 && boxD[i] < 56) { cO  = 'd'; trigLeft = false; }

		if (bulCD[i][1] - yI == 40 && bulD[i] < 56) { trigUp = false; }
		if (i < noPass && passCD[i][1] - yI == 40 && passD[i] < 56) { cO  = 'e'; trigUp = false; }
		if (i < noTree && treeCD[i][1] - yI == 40 && treeD[i] < 56) { cO  = 'f'; trigUp = false; }
		if (i < noBox && boxCD[i][1] - yI == 40 && boxD[i] < 56) { cO  = 'f'; trigUp = false; }

		if (bulCD[i][1] - yI == -40 && bulD[i] < 56) { trigDown = false; }
		if (i < noPass && passCD[i][1] - yI == -40 && passD[i] < 56) { cO = 'g'; trigDown = false; }
		if (i < noTree && treeCD[i][1] - yI == -40 && treeD[i] < 56) { cO = 'h'; trigDown = false; }
		if (i < noBox && boxCD[i][1] - yI == -40 && boxD[i] < 56) { cO = 'h'; trigDown = false; }

	}

	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		if (xI > 0 && trigLeft) {
			xI -= speed;
			if (isCollided)
				isCollided = false;
		} else {
			if (cO == 'c' && !isCollided) {
				score -= 5;
				isCollided = true;
			}
			if (cO == 'd' && !isCollided) {
				if(carType == 1)
					score -= 4;
				if (carType == 2)
					score -= 2;
				isCollided = true;
			}
		}
	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		if (xI < 760 && trigRight) {
			xI += speed;
			if (isCollided)
				isCollided = false;
		} else {
			if (cO == 'a' && !isCollided) {
				score -= 5;
				isCollided = true;
			}
			if (cO == 'b' && !isCollided) {
				if(carType == 1)
					score -= 4;
				if (carType == 2)
					score -= 2;
				isCollided = true;
			}
		}
	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		if (yI < 760 && trigUp) {
			yI += speed;
			if (isCollided)
				isCollided = false;
		} else {
			if (cO == 'e' && !isCollided) {
				score -= 5;
				isCollided = true;
			}
			if (cO == 'f' && !isCollided) {
				if(carType == 1)
					score -= 4;
				if (carType == 2)
					score -= 2;
				isCollided = true;
			}
		}
	} else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		if (yI > 0 && trigDown) {
			yI -= speed;
			if (isCollided)
				isCollided = false;
		} else {
			if (cO == 'g' && !isCollided) {
				score -= 5;
				isCollided = true;
			}
			if (cO == 'h' && !isCollided) {
				if(carType == 1)
					score -= 4;
				if (carType == 2)
					score -= 2;
				isCollided = true;
			}
		}
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
	if (key == 27/* Escape key ASCII*/) {
		if (menuChoice == 0) {
			exit(1); // exit the program when escape key is pressed.
		} else {
			// Goes to main menu
			resetData();
		}
	}

	if (key == ' ' && !dispMenu) {
		if (!onBoard) {
			for (unsigned int i = 0; i < noPass; i++) {
				if (passD[i] < 56) {
					passCD[i][0] = -40;
					passCD[i][1] = -40;
					onBoard = true;
					setDrop();
					break;
				}
			}
		} else if (onBoard && dropD < 56) {
			score += 10;
			dropX = 0;
			dropY = 0;
			onBoard = false;
			dPass++;
			remPass--;
			if (remPass == 0) {
				noPass = (rand() % 3) + 3;
				randGenerator(passCD, noPass);
				remPass = noPass;
			}
		}
		if (dPass == 2) {	
			if (ocarSpeed < 15) {
				ocarSpeed += 2;	
			} else if (ocarSpeed > 15) {
				ocarSpeed = 15;
			}
			if (noOcar < 5) {
				noOcar++;
			}
			dPass = 0;
		}
	}

	if (dispMenu) {
		if (menuChoice == 0) {
			if (key == '1') {
				menuChoice = 1;
			} else if (key == '2') {
				menuChoice = 2;
			} else if (key == '3') {
				menuChoice = 3;
			}
		} else if (menuChoice == 1) {
			if (key == 13) {
				if (playerName != "") {
					menuChoice = 5;
				}
			} else if (key == 8) {
				if (playerName != "") {
					playerName.replace(playerName.length() - 1, 1, "");
				}
			} else if (key == 32) {
				playerName += "_";
			} else {
				playerName += key;
			}
		} else if (menuChoice == 5) {
			if (key == '1') {
				initiateValues();
				carType = (rand() % 2) + 1;
				gameOver = false;
				dispMenu = false;
			} else if (key == '2') {
				menuChoice = 6;
			}
		} else if (menuChoice == 6) {
			initiateValues();
			carType = (key == 49) ? 1 : 2;
			gameOver = false;
			dispMenu = false;
		}
	}
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	mX = x;
	mY = y;
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

	int btn = 0;
	btn = (mX >= 20 && mX <= 370) && (mY >= 160 && mY <= 200) ? 1 : btn;
	btn = (mX >= 20 && mX <= 370) && (mY >= 210 && mY <= 250) ? 2 : btn;
	btn = (mX >= 20 && mX <= 370) && (mY >= 260 && mY <= 300) ? 3 : btn;
	btn = (mX >= 20 && mX <= 370) && (mY >= 310 && mY <= 350) ? 4 : btn;

	if (button == GLUT_LEFT_BUTTON) { // dealing only with left button
		if (dispMenu) {
			if (menuChoice == 0) {
				if (btn == 1) {
					menuChoice = 1;
				} else if (btn == 2) {
					menuChoice = 2;
				} else if (btn == 3) {
					menuChoice = 3;
				} else if (btn == 4) {
					exit(1);
				}
			}
		}
		// cout << GLUT_DOWN << " " << GLUT_UP << endl;
	} else if (button == GLUT_RIGHT_BUTTON) { // dealing with right button
		//cout << "Right Button Pressed" << endl;
	}
	glutPostRedisplay();
}

// Prints Leaderboard (High Scores)
void leaderBoard() {
	DrawString(30, 800, "********** Highscores **********", colors[MISTY_ROSE]);
	string p_names[10];
	int scores[10] = { 0 }, serial = 0;
	fstream lBoard;
	lBoard.open("highscores.txt");
	int i = 0;
	while (!lBoard.eof()) {
		lBoard >> serial >> p_names[i] >> scores[i];
		i++;
	}

	DrawRectangle(20, 730, 980, 50, colors[BLACK]);
	DrawString(30, 750, "S#", colors[MISTY_ROSE]);
	DrawString(100, 750, "Player Names", colors[MISTY_ROSE]);
	DrawString(500, 750, "Scores", colors[MISTY_ROSE]);
	for (unsigned int i = 0; i < 10; i++) {
		if (scores[i] != 0) {
			DrawString(30, 700 - (i * 50), to_string(i + 1), colors[MISTY_ROSE]);
			DrawString(100, 700 - (i * 50), p_names[i], colors[MISTY_ROSE]);
			DrawString(500, 700 - (i * 50), to_string(scores[i]), colors[MISTY_ROSE]);
		}
	}
}

// Prints Leaderboard (High Scores)
void saveScore(int *score, string name) {
	string p_names[10], swapn;
	int scores[10] = { 0 }, serial = 0, i = 0, swaps = 0;
	fstream lBoard;
	lBoard.open("highscores.txt");
	while (!lBoard.eof() && i < 10) {
		lBoard >> serial >> p_names[i] >> scores[i];
		i++;
	}
	lBoard.close();
	for (unsigned int i = 0; i < 10; i++) {
		if (*score > scores[i]) {
			swaps = scores[i];
			swapn = p_names[i];
			for (unsigned int j = 9; j > i; j--) {
				scores[j] = scores[j-1];
				p_names[j] = p_names[j-1];
			}
			scores[i] = *score;
			p_names[i] = name;
			break;
		}
	}
	lBoard.open("highscores.txt");
	for (unsigned int i = 0; i < 10; i++) {
		if (scores[i] != 0) {
			lBoard << i+1 << "     " << p_names[i] << "     " << scores[i] << endl;
		}
	}
	lBoard.close();
}

void carCollision() {
	for (unsigned int i = 0; i < noOcar; i++) {
		if (ocarD[i]!=0 && ocarD[i] < 40 && !isCollided) {
			if(carType == 1)
				score -= 2;
			if (carType == 2)
				score -= 3;
			isCollided = true;
		} else if (ocarD[i]!=0 && ocarD[i] < 80 && !isCollided && (ocarCD[i][0] == xI || ocarCD[i][1] == yI)) {
			score += 1;
			isCollided = true;
		}
	}
}
#endif /* RushHour_CPP_  */
//============================================================================
// Name        : Triangle-Solver.cpp
// Author      : Plain & Simple
// Version     : 0.1
// License     : GPL v3
// Description : Solver for triangle sides and angles
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

// Function prototypes
void setup();
void input(double &sideA, double &sideB, double &sideC, double &angleA, double &angleB, double &angleC);
bool errCheck(double sideA, double sideB, double sideC, double angleA, double angleB, double angleC);
void SolveASA(double triangle[], int offset);
void SolveSSS(double triangle[]);

int main() {
	// Variable declaration
	double sideA, sideB, sideC, angleA, angleB, angleC;
	bool error;

	// Function calls
	setup();
	do {
		input(sideA, sideB, sideC, angleA, angleB, angleC);
		error = errCheck(sideA, sideB, sideC, angleA, angleB, angleC);
	} while (error);
	return 0;
}

void setup() {
	// Logo
	cout
	<< "8888888b.   888            d8b                     .d8888b.   d8b                           888           \n"
	<< "888   Y88b  888            Y8P                    d88P  Y88b  Y8P                           888           \n"
	<< "888    888  888                                   Y88b.                                     888           \n"
	<< "888   d88P  888   8888b.   888  88888b.     88     \"Y888b.    888  88888b.d88b.   88888b.   888   .d88b.  \n"
	<< "8888888P\"   888      \"88b  888  888 \"88b  888888      \"Y88b.  888  888 \"888 \"88b  888 \"88b  888  d8P  Y8b \n"
	<< "888         888  .d888888  888  888  888    88          \"888  888  888  888  888  888  888  888  88888888 \n"
	<< "888         888  888  888  888  888  888          Y88b  d88P  888  888  888  888  888 d88P  888  Y8b.     \n"
	<< "888         888  \"Y888888  888  888  888           \"Y8888P\"   888  888  888  888  88888P\"   888   \"Y8888  \n"
	<< "                                                                                  888                       \n"
	<< "                                                                                  888                       \n"
	<< "                                                                                  888                       ";

	// Triangle diagram
	cout
	<< "                       A \n"
	<< "                       .\n"
	<< "                      /|\n"
	<< "                     / |\n"
	<< "                    /  |\n"
	<< "                   /   |\n"
	<< "                  /    |\n"
	<< "                 /     |\n"
	<< "              B /      | C\n"
	<< "               /       |\n"
	<< "              /        |\n"
	<< "             /         |\n"
	<< "            /          |\n"
	<< "           /           |\n"
	<< "          /____________|\n"
	<< "        C       A       B\n";
}

void input(double &sideA, double &sideB, double &sideC, double &angleA, double &angleB, double &angleC) {
	cout << "\nEnter side lengths (A, B, and C) or 0 if unknown: ";
	cin >> sideA >> sideB >> sideC;
	cout << "Enter angle degree measures opposite sides (A, B, and C) or 0 if unknown: ";
	cin >> angleA >> angleB >> angleC;
}

bool errCheck(double sideA, double sideB, double sideC, double angleA, double angleB, double angleC) {
	bool error = false;

	// Side and angle errors
	if(sideA && sideB && sideC && angleA && angleB && angleC) {
		cout << "All sides and angles have been defined. There is nothing to solve.\n";
		return true;
	}

	// Side errors
	if(sideA < 0 || sideB < 0 || sideC < 0) {
		cout << "One or more of the sides has negative length.\n";
		error = true;
	}
	if(!(sideA && sideB && sideC)) {
		cout << "One or more of the sides has length 0.\n";
		error = true;
	}
	if((sideA - sideB - sideC) > 0 || (sideB - sideA - sideC) > 0 || (sideC - sideA - sideB) > 0) {
		cout << "One of the sides is longer than the other two combined.\n";
		error = true;
	}
	if(!((sideA - sideB - sideC) && (sideB - sideA - sideC) && (sideC - sideA - sideB))) {
		cout << "One of the sides is the same length as the other two combined.\n";
		error = true;
	}

	// Angle errors
	if(angleA + angleB + angleC > 180) {
		cout << "The sum of the angle measures is greater than 180°.\n";
		error = true;
	}
	if(angleA + angleB + angleC < 180 && (angleA && angleB && angleC)) { // Checks if all angles are provided and sum to < 180
		cout << "The sum of the angle measures is less than 180°.\n";
		error = true;
	}

	return error;
}


void SolveASA(double triangle[], int offset) {
  triangle[offset] = 180 - (triangle[(offset + 2) % 6] +
                            triangle[(offset - 2) % 6]);
  double sine_angle_ratio = sin(triangle[(offset + 3) % 6]) / triangle[offset];
  triangle[(offset + 1) % 6] =
  asin(triangle[(offset - 2) % 6] * sine_angle_ratio);
  triangle[(offset - 1) % 6] =
  asin(triangle[(offset + 2) % 6] * sine_angle_ratio);
}
void SolveSSS (double triangle[]) {
  triangle[0] = acos((pow(triangle[1], 2) + pow(triangle[5], 2) -
                     pow(triangle[3], 2)) / 2 * triangle[1] * triangle[5]);
  triangle[2] = acos((pow(triangle[3], 2) + pow(triangle[1], 2) -
                     pow(triangle[5], 2)) / 2 * triangle[3] * triangle[1]);
  triangle[4] = 180 - (triangle[2] + triangle[0]);
}

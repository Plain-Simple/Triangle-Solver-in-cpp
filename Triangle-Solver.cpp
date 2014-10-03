/*******************************************************************************
* Triangle-Solver.cpp
*
* Description: This is the main file for the C++ triangle solver, which solves
* missing sides and angles on a triangle using trigonometry.
*
* By Derik Kauffman, Matthew McMillan, Stefan Kussmaul
*******************************************************************************/

/* everybody please fix your name, sorry I can't spell*/

#include <iostream>
#include <cmath>
using namespace std;

void PrintGraphics();
void Input(double triangle[6]);
bool IsInvalid(double triangle [6]);
void SolveASA(double triangle [6], int offset);
void SolveSSS(double triangle [6]);

int main() {
  cout << "Please maximize your window and press enter\n\n";
  /* This is necessary so the logo doesn't get wrapped */
  cin.get();

  double triangle[6] = {0,0,0,0,0,0}; // find a better way to do this
  /* 0, 2, and 4 are angles ABC. The sides are the odd numbers between the
     angles (going clockwise on the triangle) */
  PrintGraphics();
  do {
    Input(triangle);
  } while(IsInvalid(triangle));
  return 0;
}

void PrintGraphics() {
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

void Input(double triangle [6]) {
  for (int i = 0; i < 3; i++) {
    cout << "Please enter side " << i << " (0 if unknown):\n";
    cin >> triangle[i * 2 + 1];
  }
  for (int i = 0; i < 3; i++) {
    cout << "Please enter angle " << i << " (0 if unknown):\n";
    cin >> triangle[2*i];
  }
}

bool IsInvalid(double triangle[6]) { /// I think you could make all of this
                                    /// a loop rather than an if tree
  // Side and angle errors
  if(triangle[0] && triangle[1] && triangle[2] &&
     triangle[3] && triangle[4] && triangle[5]) {
    cout << "All sides and angles have been defined. "
            "There is nothing to solve.\n";
    return true;
  } else if(triangle[3] < 0 || triangle[5] < 0 || triangle[1] < 0) { // Side errors
    cout << "One or more of the sides has negative length.\n";
    return true;
  } else if(!(triangle[3] && triangle[5] && triangle[1])) {
    cout << "One or more of the sides has length 0.\n";
    return true;
  } else if((triangle[3] - triangle[5] - triangle[1]) > 0 || (triangle[5] - triangle[3] - triangle[1]) > 0
      || (triangle[1] - triangle[3] - triangle[5]) > 0) {
    cout << "One of the sides is longer than the other two combined.\n";
    return true;
  } else if(!((triangle[3] - triangle[5] - triangle[1]) && (triangle[5] - triangle[3] - triangle[1])
       && (triangle[1] - triangle[3] - triangle[5]))) {
    cout << "One of the sides is the same length as the other two combined.\n";
    return true;
  } else if(triangle[0] + triangle[2] + triangle[4] > 180) {
    cout << "The sum of the angle measures is greater than 180°.\n";
    return true;
  } else if(triangle[0] + triangle[2] + triangle[4] < 180 && (triangle[0] && triangle[2]
                                        && triangle[4])) { // Checks if all angles are provided and sum to < 180
    cout << "The sum of the angle measures is less than 180°.\n";
    return true;
  } else {
    return false;
  }
}


void SolveASA(double triangle [6], int offset) {
  triangle[offset] = 180 - (triangle[(offset + 2) % 6] +
                            triangle[(offset - 2) % 6]);
  double sine_angle_ratio = sin(triangle[(offset + 3) % 6]) / triangle[offset];
  triangle[(offset + 1) % 6] =
    asin(triangle[(offset - 2) % 6] * sine_angle_ratio);
  triangle[(offset - 1) % 6] =
    asin(triangle[(offset + 2) % 6] * sine_angle_ratio);
}
void SolveSSS(double triangle [6]) {
  triangle[0] = acos((pow(triangle[1], 2) + pow(triangle[5], 2) -
                      pow(triangle[3], 2)) / 2 * triangle[1] * triangle[5]);
  triangle[2] = acos((pow(triangle[3], 2) + pow(triangle[1], 2) -
                      pow(triangle[5], 2)) / 2 * triangle[3] * triangle[1]);
  triangle[4] = 180 - (triangle[2] + triangle[0]);
}

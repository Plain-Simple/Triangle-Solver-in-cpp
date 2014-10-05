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
//bool IsInvalid(double triangle [6]);
string IdentifyTriangle(double triangle [6]);
void SolveASA(double triangle [6], int offset); /// what is int offset?
void SolveSSS(double triangle [6]);
void SolveSAS(double triangle [6]);

int main() {
	cout << "Please maximize your window and press enter\n\n";
  /* This is necessary so the logo doesn't get wrapped */
  cin.get();

  double triangle[6] = {0,0,0,0,0,0}; // find a better way to do this
  /* 0, 2, and 4 are angles ABC. The sides are the odd numbers between the
     angles (going clockwise on the triangle) */
  PrintGraphics();
//  do {
    Input(triangle);
    string triangleType = IdentifyTriangle(triangle);
    cout << "Triangle is " << triangleType << endl;
// } while(IsInvalid(triangle));
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
      << "                                                                                  888                       \n";
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
      << "         Side B /      | Side C\n"
      << "               /       |\n"
      << "              /        |\n"
      << "             /         |\n"
      << "            /          |\n"
      << "           /           |\n"
      << "          /____________|\n"
      << "        C     Side A       B\n\n";
}

void Input(double triangle [6]) {
  for (int i = 65; i < 68; i++) { /* set i to 65 for ascii value "A" */
	char side = i;
    cout << "Please enter side " << side << " (0 if unknown): ";
    cin >> triangle[2 * i - 129];
    cout << endl; /// what looks better; with endl or without?
  }
  for (int i = 97; i < 100; i++) { /* set i to 97 for ascii value "a" */
	char angle = i;
    cout << "Please enter angle " << angle << " (0 if unknown):";
    cin >> triangle[2 * i - 194];
    cout << endl;
  }
}

/*bool IsInvalid(double triangle[6]) { /// This function simply does not work the way we need it to
                                    /// Make into a loop
  // Side and angle errors
  if(triangle[0] && triangle[1] && triangle[2] &&
     triangle[3] && triangle[4] && triangle[5]) {
    cout << endl << "All sides and angles have been defined. "
            "There is nothing to solve.\n";
    return true;
  } else if(triangle[3] < 0 || triangle[5] < 0 || triangle[1] < 0) { // Side errors
    cout << endl << "One or more of the sides has negative length.\n";
    return true;
  //} //else if(!(triangle[3] && triangle[5] && triangle[1])) {
    //cout << endl << "One or more of the sides has length 0.\n"; /// This is a little confusing because the sides can be 0
    //return true;
  } else if((triangle[3] - triangle[5] - triangle[1]) > 0 || (triangle[5] - triangle[3] - triangle[1]) > 0
      || (triangle[1] - triangle[3] - triangle[5]) > 0) {
    cout << endl << "One of the sides is longer than the other two combined.\n";
    return true;
  } else if(!((triangle[3] - triangle[5] - triangle[1]) && (triangle[5] - triangle[3] - triangle[1])
       && (triangle[1] - triangle[3] - triangle[5]))) {
    cout << endl << "One of the sides is the same length as the other two combined.\n";
    return true;
  } else if(triangle[0] + triangle[2] + triangle[4] > 180) {
    cout << endl << "The sum of the angle measures is greater than 180°.\n";
    return true;
  } else if(triangle[0] + triangle[2] + triangle[4] < 180 && (triangle[0] && triangle[2]
                                        && triangle[4])) { // Checks if all angles are provided and sum to < 180
    cout << endl << "The sum of the angle measures is less than 180°.\n";
    return true;
  } else {
    return false;
  }
}*/

string IdentifyTriangle(double triangle [6]) { /// not quite there yet; help would be appreciated
	string type = "undefined";
	int i;
	for(i = 1; i < 6; i = i + 2)
	{
		if(triangle[i % 6] != 0 && triangle[(i + 2) % 6] != 0 && triangle[(i + 1) % 6] != 0)
			type = "SAS";
		else if(triangle[i % 6] != 0 && triangle[(i + 2) % 6] != 0 && triangle[(i + 4) % 6] != 0)
			type = "SSS";
		else if(triangle[(i - 1) % 6] != 0 && triangle[(i + 1) % 6 != 0] && triangle[(i + 2) % 6] != 0) 
			type = "ASA";
		else if(triangle[i % 6] != 0 && triangle[(i + 1) % 6] != 0 && triangle[(i - 1) % 6] != 0)
			type = "AAS";
		else if(triangle[i % 6] != 0 && triangle[(i + 3) % 6] != 0 && triangle[(i - 1) % 6] != 0)
			type = "AAS";
	}
	return type;
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
void SolveSAS(double triange [6]) {

}


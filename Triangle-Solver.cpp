/*******************************************************************************
* Triangle-Solver.cpp
*
* Description: This is the main file for the C++ triangle solver, which solves
* missing sides and angles on a triangle using trigonometry.
*
* By Derik Kauffman, Matthew McMillan, Stefan Kussmaul
*******************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

void Process(double triangle [6]);
/* executes functions in order */
bool IsInvalid(double triangle [6]);
/* checks to see if final triangle is valid */
void Input(double triangle[6]);
/* take user input of known angles and sides */

void SolveMissingSideLOS(double triangle[6], int missing_side);
/* solve missing side using law of sines */
void SolveMissingAngleLOS(double triangle[6], int missing_angle);
/* solve missing angle using law of sines */

string GetTriangleType(double triangle[6]);
/* returns the type of triangle (ie. "equilateral") */
string GetAngleType(double triangle[6]);
/* returns the type of triangle angle (ie. obtuse) */
void SolveLastAngle(double &angle1, double &angle2, double &angle3);
/* takes in 3 angles, and solves the missing one */


double GetAngleToSideRatio(double triangle[6]);
/* figures out sinx/x ratio for law of sines */
double GetSideToAngleRatio(double triangle[6]);
/* figures out x/sinx ratio for law of sines */
void SolveLastAngle(double &angle1, double &angle2, double &angle3);
/* solves last angle based on the fact that all angles add up to 180 */

int main() {
    double triangle[6];
    Process(triangle);
  return 0;
}

void Process(double triangle [6]) {
	char go_again = 'n', invalid;
	cout
	  	  << "Plain+Simple Triangle Solver C++ edition\n"
	  	  << "\tPress enter to continue";
	  	  cin.get();
	  do {
	  cout
	  	  << "                       B \n"
	      << "                       .\n"
	      << "                      /|\n"
	      << "                     / |\n"
	      << "                    /  |\n"
	      << "                   /   |\n"
	      << "                  /    |\n"
	      << "                 /     |\n"
	      << "         Side C /      | Side A\n"
	      << "               /       |\n"
	      << "              /        |\n"
	      << "             /         |\n"
	      << "            /          |\n"
	      << "           /           |\n"
	      << "          /____________|\n"
	      << "        A     Side B       C\n\n";
	  Input(triangle);
	  /// Solve function could go here
	  invalid = IsInvalid(triangle);
	  if(invalid == 0)
	  {
		  cout << "Solved Triangle----------------------\n"
			   << "Side A\t" << triangle[3] << endl
			   << "Side B\t" << triangle[5] << endl
			   << "Side C\t" << triangle[1] << endl << endl
			   << "angle a\t\t" << triangle[0] << endl
			   << "angle b\t\t" << triangle[2] << endl
			   << "angle c\t\t" << triangle[4] << endl << endl;
		  string t_type = GetTriangleType(triangle);
		  string t_angle = GetAngleType(triangle);
		  cout << "Triangle is " << t_type << " and " << t_angle;
	  }
	  cout << "\n\nRun again? (y/n) ";
	  cin >> go_again;
	  } while(go_again == 'y');

}

void Input(double triangle [6]) {
	/* 0, 2, and 4 are angles. The sides are the odd numbers between the
	       angles (going clockwise on the triangle) */
  for (int i = 0; i < 3; i++) { /* set i to 65 for ascii value "A" */
    cout << "Enter side " << char(i + 65) << " (0 if unknown): ";
    cin >> triangle[(2 * i + 3) % 6];
    cout << endl;
  }
  for (int i = 0; i < 3; i++) {
    cout << "Enter angle " << char(i + 97) << " (0 if unknown):";
    cin >> triangle[2 * i]; /* the angle input is shifted by one angle (so 2)
                                  due to the "angles opposite sides" diagram */
  }
}

bool IsInvalid(double triangle[6]) {
                                    /// Make into a loop
  if(triangle[3] < 0 || triangle[5] < 0 || triangle[1] < 0) { // Side errors
    cout << endl << "Error: One or more of the sides has negative length.\n";
    return true;
  } else if((triangle[3] - triangle[5] - triangle[1]) > 0 || (triangle[5] - triangle[3] - triangle[1]) > 0
      || (triangle[1] - triangle[3] - triangle[5]) > 0) {
    cout << endl << "Error: One of the sides is longer than the other two combined.\n";
    return true;
  } else if(!((triangle[3] - triangle[5] - triangle[1]) && (triangle[5] - triangle[3] - triangle[1])
       && (triangle[1] - triangle[3] - triangle[5]))) {
    cout << endl << "Error: One of the sides is the same length as the other two combined.\n";
    return true;
  } else if(triangle[0] + triangle[2] + triangle[4] > 180) {
    cout << endl << "Error: The sum of the angle measures is greater than 180°.\n";
    return true;
  } else if(triangle[0] + triangle[2] + triangle[4] < 180 && (triangle[0] && triangle[2]
                                        && triangle[4])) { // Checks if all angles are provided and sum to < 180
    cout << endl << "Error: The sum of the angle measures is less than 180°.\n";
    return true;
  } else {
    return false;
  }
}

string GetTriangleType(double triangle[6]) {
  if ((triangle[0] == triangle [2]) == triangle[4]) {
    return "equilateral";
  }
  for (int i = 0; i < 3; i++) {
    if (triangle[2 * i] == ((2 * i + 2) % 6)) {
      return "isosceles";
    }
  }
  return "scalene";
}

string GetAngleType(double triangle[6]) {
  for (int i = 0; i < 3; i++) {
    if (triangle[2 * i] == 90) {
      return "right";
    } else if (triangle[2 * i] > 90) {
      return "obtuse";
    }
  }
  return "acute";
  /* if no right or obtuse angles were found, it must be an acute triangle */
}

void SolveLastAngle(double &angle1, double &angle2, double &angle3) {
  if (angle1 && angle2) {
    angle3 = 180 - (angle1 + angle2);
  } else if (angle1 && angle3) {
    angle2 = 180 - (angle1 + angle3);
  } else if (angle2 && angle3) {
    angle1 = 180 - (angle2 + angle3);
  }
}

double GetSideToAngleRatio(double triangle[6]) {
  for (int i = 0; i < 6; i += 2) {
    if (triangle[i] && triangle[(i + 3) % 6]) {
      return triangle[(i + 3) % 6] / sin(triangle[i]);
    }
  }
  return 0;
}

double GetAngleToSideRatio(double triangle[6]) {
  for (int i = 0; i < 6; i += 2) {
    if (triangle[i] && triangle[(i + 3) % 6]) {
      return sin(triangle[i]) / triangle[(i + 3) % 6];
    }
  }
  return 0;
}

void SolveMissingSideLOS(double triangle[6], int missing_side) {
  triangle[missing_side] =
  GetSideToAngleRatio(triangle) * sin(triangle[(missing_side + 3) % 6]);
}

void SolveMissingAngleLOS(double triangle[6], int missing_angle) {
  triangle[missing_angle] =
  asin(GetAngleToSideRatio(triangle) * triangle[(missing_angle + 3) % 6]);
}


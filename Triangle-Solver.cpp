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
/* prints out Plain + Simple logo and triangle diagram */
void PrintGraphics();
/* take user input of known angles and sides */
//bool IsInvalid(double triangle [6]);
void Input(double triangle[6]);

/* The following four functions are depreciated and should be removed as soon as
   there is a replacement */

string IdentifyTriangle(double triangle [6]);
/* Next three solve functions solve the type of triangle in their name, filling
   in any unknown sides or angles. offset is the number of the element that is
   the first A or S in the triangle ID. */
void SolveASA(double triangle [6], int offset);
void SolveSSS(double triangle [6]);
void SolveSAS(double triangle [6]);

/* solve missing side using law of sines */
void SolveMissingSideLOS(double triangle[6], int missing_side);
/* solve missing angle using law of sines */
void SolveMissingAngleLOS(double triangle[6], int missing_angle);

/* returns the type of triangle followed by a space (ie. "equilateral ") */
string GetTriangleType(double triangle[6]);
/* returns the type of triangle angle (ie. obtuse) */
string GetAngleType(double triangle[6]);
/* takes in 3 angles, and solves the missing one */
void SolveLastAngle(double &angle1, double &angle2, double &angle3);

/* figures out sinx/x ratio for law of sines */
double GetAngleToSideRatio(double triangle[6]);
/* figures out x/sinx ratio for law of sines */
double GetSideToAngleRatio(double triangle[6]);

/* solves last angle based on the fact that all angles add up to 180 */
void SolveLastAngle(double &angle1, double &angle2, double &angle3);

int main() {
  cout << "Welcome to the triangle solver. Please press enter to continue.";
  cin.get();
  char go_again = 'n';
  do {
    /* 0, 2, and 4 are angles. The sides are the odd numbers between the
       angles (going clockwise on the triangle) */
    double triangle[6] = {0,0,0,0,0,0}; /// find a better way to do the this
    PrintGraphics();
    //  do {
        Input(triangle);
        string triangleType = IdentifyTriangle(triangle);
        cout << "Triangle is " << triangleType << endl;
    // } while(IsInvalid(triangle));
    cout << "\n\nWould you like to run the program again?\n";
  } while (go_again == 'y');
  return 0;
}

void PrintGraphics() {
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
}

void Input(double triangle [6]) {
  for (int i = 0; i < 3; i++) { /* set i to 65 for ascii value "A" */
    cout << "Please enter side " << char(i + 65) << " (0 if unknown): ";
    cin >> triangle[(2 * i + 3) % 6];
    cout << endl;
  }
  for (int i = 0; i < 3; i++) { /* set i to 97 for ascii value "a" */
    cout << "Please enter angle " << char(i + 97) << " (0 if unknown):";
    cin >> triangle[2 * i]; /* the angle input is shifted by one angle (so 2)
                                  due to the "angles opposite sides" diagram */
    cout << endl;
  }
  /* the following loop is for debugging only:
  for (int i = 0; i < 6; i++) {
    cout << endl << triangle[i];
  } */
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

string IdentifyTriangle(double triangle [6]) { /// should be done now
	for(int i = 0; i < 6; i += 2) { /* instead of saying "=0", you can just say
      if (triangle[x]) and it will be treated like a boolean */
		if (triangle[i + 1] && triangle[(i + 2) % 6] && triangle[(i + 3) % 6]) {
			return "SAS";
		} else if (triangle[1] && triangle[3] && triangle[5]) {
			return "SSS";
		} else if (triangle[i] && triangle[i + 1] && triangle[(i + 2) % 6]) {
			return "ASA";
		} else if ((triangle[i] && triangle[(i + 2) % 6] && triangle[(i + 3) % 6])
      || (triangle[i + 1] && triangle[(i + 2) % 6] && triangle [(i + 4) % 6])) {
        /* checks for AAS then SAA */
			return "AAS";
	  }
	}
	return "undefined";
	/* rather than using a variable like "type", we can just return the value as
	soon as we get it, thus saving processing time and reducing variable use */
}
void SolveASA(double triangle [6], int offset) { /// Matt: you need a side-sine ratio
  triangle[offset] = 180 - (triangle[(offset + 2) % 6] +
                            triangle[(offset - 2) % 6]);
  double sine_angle_ratio = sin(triangle[(offset + 3) % 6]) / triangle[offset];
  triangle[(offset + 1) % 6] =
    asin(triangle[(offset - 2) % 6] * sine_angle_ratio);
  triangle[(offset - 1) % 6] =
    asin(triangle[(offset + 2) % 6] * sine_angle_ratio);
}

void SolveSSS(double triangle [6]) { /* pretty sure this is completely wrong */
  triangle[0] = acos((pow(triangle[1], 2) + pow(triangle[5], 2) -
                      pow(triangle[3], 2)) / 2 * triangle[1] * triangle[5]);
  triangle[2] = acos((pow(triangle[3], 2) + pow(triangle[1], 2) -
                      pow(triangle[5], 2)) / 2 * triangle[3] * triangle[1]);
  triangle[4] = 180 - (triangle[2] + triangle[0]);
}
void SolveSAS(double triange [6]) {

}

string GetTriangleType(double triangle[6]) {
  if ((triangle[0] == triangle [2]) == triangle[4]) {
    return "equilateral ";
  }
  for (int i = 0; i < 3; i++) {
    if (triangle[2 * i] == ((2 * i + 2) % 6)) {
      return "isosceles ";
    }
  }
  return "scalene ";
}

string GetAngleType(double triangle[6]) {
  for (int i = 0; i < 3; i++) {
    if (triangle[2 * i] == 90) {
      return "right triangle";
    } else if (triangle[2 * i] > 90) {
      return "obtuse triangle";
    }
  }
  return "acute triangle";
  /* if no right or obtuse angles were found, it must be an acute triangle */
}

void SolveAAS(double triangle[6], int offset) {
  for (int i = 0; i < 6; i += 2) {
    if (!triangle[i]) { /* find missing angle, then solve for it */
      triangle [i] = 180 - (((i + 2) % 6) + ((i + 4) % 6));
    }
  }
  double sine_ratio;
  for (int i = 0; i < 6; i += 2) {
    if (triangle[i] && triangle[i + 3]) {
      sine_ratio = triangle[i + 3] / sin(triangle[i]);
    }
  }
  for (int i = 1; i < 6; i += 2) {
    if (!triangle[i]) { /* find unsolved side */
      triangle[i] = sine_ratio * sin(triangle[(i + 3) % 6]);
    }
  }
}

/* solves last angle based on the fact that all angles add up to 180 */
void SolveLastAngle(double &angle1, double &angle2, double &angle3) {
  if (angle1 && angle2) {
    angle3 = 180 - (angle1 + angle2);
  } else if (angle1 && angle3) {
    angle2 = 180 - (angle1 + angle3);
  } else if (angle2 && angle3) {
    angle1 = 180 - (angle2 + angle3);
  }
}

/* figures out x/sinx ratio for law of sines */
double GetSideToAngleRatio(double triangle[6]) {
  for (int i = 0; i < 6; i += 2) {
    if (triangle[i] && triangle[(i + 3) % 6]) {
      return triangle[(i + 3) % 6] / sin(triangle[i]);
    }
  }
  return 0;
}
/* figures out sinx/x ratio for law of sines */
double GetAngleToSideRatio(double triangle[6]) {
  for (int i = 0; i < 6; i += 2) {
    if (triangle[i] && triangle[(i + 3) % 6]) {
      return sin(triangle[i]) / triangle[(i + 3) % 6];
    }
  }
  return 0;
}

/* figure out missing side using an opposite angle and a sine ratio */
void SolveMissingSideLOS(double triangle[6], int missing_side) {
  triangle[missing_side] =
  GetSideToAngleRatio(triangle) * sin(triangle[(missing_side + 3) % 6]);
}
/* figure out missing angle using an opposite side and a sine ratio */
void SolveMissingAngleLOS(double triangle[6], int missing_angle) {
  triangle[missing_angle] =
  asin(GetAngleToSideRatio(triangle) * triangle[(missing_angle + 3) % 6]);
}

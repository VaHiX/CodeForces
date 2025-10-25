// Problem: CF 1563 A - Charmed by the Game
// https://codeforces.com/contest/1563/problem/A

/*
Problem: A. Charmed by the Game
Purpose: Given the number of games won by Alice (a) and Borys (b), determine all possible numbers of breaks that could occur in the match.
Algorithms:
  - For a match with a + b total games, breaks depend on who serves first and how the games are distributed.
  - If the total is even, then breaks can be any value from 0 to a+b. 
  - If the total is odd, then breaks must be even values from 0 to a+b.
Time Complexity: O(1) per test case (constant time operations)
Space Complexity: O(1) (no extra space used except for variables)
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

int main(void) {
  int t;
  cin >> t;
  while (t--) {
    int a;
    int b;
    cin >> a >> b;
    int d = abs(a - b) / 2;   // Difference in wins divided by 2
    int k = 0;
    if (0 == (a + b) % 2) {   // If total games is even
      int c = 0;
      for (int i = 0; k < a + b - d; i += 2) {   // Increment by 2 to ensure even breaks
        k = d + i;
        c++;
      }
      cout << c << endl;
      k = 0;
      for (int i = 0; k < a + b - d; i += 2) {   // Print valid breaks
        k = d + i;
        cout << k << " ";
      }
      cout << endl;
    } else {   // If total games is odd
      int c = 0;
      for (int i = 0; k < a + b - d; i += 1) {   // Increment by 1 to allow all values
        k = d + i;
        c++;
      }
      cout << c << endl;
      k = 0;
      for (int i = 0; k < a + b - d; i += 1) {   // Print valid breaks
        k = d + i;
        cout << k << " ";
      }
      cout << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
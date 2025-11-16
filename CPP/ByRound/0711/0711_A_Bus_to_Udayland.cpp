// Problem: CF 711 A - Bus to Udayland
// https://codeforces.com/contest/711/problem/A

/*
Purpose: 
This code determines if two friends, ZS and Chris, can sit together in neighbouring empty seats on a bus.
The bus has n rows, each with 4 seats arranged in two pairs separated by a walkway ('|').
The input describes the current seating configuration using 'O' for empty and 'X' for occupied.
The task is to find a pair of adjacent empty seats in the same row and mark them with '+'.
If such a pair exists, output "YES" and the updated bus configuration; otherwise, output "NO".

Algorithms/Techniques:
- Brute-force search through rows and pairs of seats to find two consecutive empty seats ('O' followed by 'O')
- Once found, mark both seats with '+' and stop searching
- Output result based on whether a valid pair was found

Time Complexity: O(n), where n is the number of rows. In the worst case, we may scan all rows once.
Space Complexity: O(n), for storing the bus configuration in a 2D array of size n x 6.

*/
#include <cstdio>
#include <iostream>

using namespace std;
int main() {
  int i, j, k;
  int n;
  int flag = 0;
  scanf("%d", &n);
  char a[n][6];
  for (i = 0; i < n; i++) {
    scanf("%s", &a[i]); // Read each row of the bus seating
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < 4; j++) { // j < 4 because we only check pairs within the row (0,1 and 2,3)
      if (a[i][j] == 'O' && a[i][j + 1] == 'O') { // Check if two adjacent seats in same row are empty
        a[i][j] = '+'; // Mark first seat in pair
        a[i][j + 1] = '+'; // Mark second seat in pair
        flag = 1; // Set flag to indicate solution found
        break;
      }
    }
    if (flag == 1) {
      break; // Break outer loop once solution is found
    }
  }
  if (flag == 0)
    cout << "NO"; // No pair of neighbouring empty seats found
  else {
    cout << "YES" << endl; // A valid pair was found
    for (i = 0; i < n; i++) {
      for (j = 0; j < 5; j++) {
        printf("%c", a[i][j]); // Print updated configuration
      }
      printf("\n");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
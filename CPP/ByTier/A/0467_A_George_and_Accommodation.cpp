// Problem: CF 467 A - George and Accommodation
// https://codeforces.com/contest/467/problem/A

/*
 * Code Purpose:
 * This program determines how many rooms in a dormitory can accommodate both George and Alex,
 * given that each room has a certain number of occupants and a total capacity.
 * A room is suitable if it has at least 2 free spaces (i.e., q - p >= 2).
 *
 * Algorithms/Techniques:
 * - Simple iteration through all rooms
 * - Basic arithmetic comparison
 *
 * Time Complexity: O(n), where n is the number of rooms
 * Space Complexity: O(1), only using a constant amount of extra space
 */

#include <cstdio>
int main() {
  int n;
  scanf("%d\n", &n);  // Read number of rooms
  int output(0);      // Initialize counter for suitable rooms
  while (n--) {       // Loop through each room
    int p, q;
    scanf("%d %d\n", &p, &q);  // Read current occupancy and capacity
    if (q - p >= 2) {         // Check if room has at least 2 free spaces
      ++output;               // Increment counter if condition is met
    }
  }
  printf("%d\n", output);   // Print the number of suitable rooms
  return 0;
}


// https://github.com/VaHiX/CodeForces/
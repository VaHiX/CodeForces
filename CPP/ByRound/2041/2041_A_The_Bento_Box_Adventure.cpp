// Problem: CF 2041 A - The Bento Box Adventure
// https://codeforces.com/contest/2041/problem/A

#include <cstdio>
// ======================================================================
// Problem: Find the missing restaurant number from 1 to 5
// Algorithm: Use a boolean array to track visited restaurants, then find
//            the first unvisited one (guaranteed to exist due to input constraints)
// Time Complexity: O(1) - fixed number of operations (4 + 5 = 9 iterations max)
// Space Complexity: O(1) - fixed size boolean array of 6 elements (0 to 5)
// ======================================================================
int main() {
  bool v[6] = {0}; // Array to track visited restaurants (index 1-5)
  for (int p = 0; p < 4; p++) { // Loop through 4 input values
    int x;
    scanf("%d", &x); // Read restaurant number
    v[x] = 1; // Mark restaurant as visited
  }
  for (int p = 1; p <= 5; p++) { // Loop through all possible restaurants
    if (!v[p]) { // If restaurant hasn't been visited
      printf("%d\n", p); // Print the missing restaurant number
      break; // Exit loop after finding it
    }
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/
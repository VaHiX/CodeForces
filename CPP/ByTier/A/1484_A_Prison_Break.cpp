// Problem: CF 1484 A - Prison Break
// https://codeforces.com/contest/1484/problem/A

#include <cstdio>
int main() {
  long t; // Number of test cases
  scanf("%ld", &t);
  while (t--) {
    long a, b; // Dimensions of the prison rectangle
    scanf("%ld %ld", &a, &b);
    printf("%ld\n", a * b); // Output the area (number of cells)
  }
}
/*
Flowerbox:
Problem: A. Prison Break
Purpose: Determine minimum number of walls to break so that every cell in a rectangular prison can reach the outside.
Algorithms/Techniques: Graph theory, connectivity analysis
Time Complexity: O(t) where t is number of test cases
Space Complexity: O(1)
*/


// https://github.com/VaHiX/codeForces/
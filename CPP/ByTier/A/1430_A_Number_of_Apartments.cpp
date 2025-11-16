// Problem: CF 1430 A - Number of Apartments
// https://codeforces.com/contest/1430/problem/A

/*
Code purpose:
This program determines the number of three-room, five-room, and seven-room apartments
in a building given the total number of windows. It uses a greedy approach by
first assigning as many seven-room apartments as possible, then adjusting for
remainder values to satisfy the constraint that the sum of windows equals n.

Algorithms/Techniques:
- Greedy algorithm with modular arithmetic to distribute windows among apartment types
- Precomputed cases for remainders when dividing by 7 to find valid combinations

Time Complexity: O(1) - Fixed number of operations per test case
Space Complexity: O(1) - Only a constant amount of extra space used
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // If n is 1, 2, or 4, it's impossible to form with given apartment sizes (3,5,7)
    if (n == 1 || n == 2 || n == 4) {
      puts("-1");
      continue;
    }
    // Start by using as many 7-room apartments as possible
    long a(0), b(0), c(n / 7);
    // Handle different remainders when dividing by 7 to adjust the counts
    if (n % 7 == 1) {
      --c;  // Reduce the count of 7-room apartments
      a = b = 1;  // Use one 3-room and one 5-room apartment to make up for the 1 window deficit
    } else if (n % 7 == 2) {
      --c;  // Reduce the count of 7-room apartments
      a = 3;  // Use three 3-room apartments to make up for the 2 window deficit
    } else if (n % 7 == 3) {
      a = 1;  // Use one 3-room apartment to make up for the 3 window deficit
    } else if (n % 7 == 4) {
      --c;  // Reduce the count of 7-room apartments
      a = 2;  // Use two 3-room apartments to make up for the 4 window deficit
      b = 1;  // Use one 5-room apartment
    } else if (n % 7 == 5) {
      b = 1;  // Use one 5-room apartment to make up for the 5 window deficit
    } else if (n % 7 == 6) {
      a = 2;  // Use two 3-room apartments to make up for the 6 window deficit
    }
    printf("%ld %ld %ld\n", a, b, c);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
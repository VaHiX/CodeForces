// Problem: CF 1472 B - Fair Division
// https://codeforces.com/contest/1472/problem/B

/*
B. Fair Division
Algorithm: Count the number of 1-gram and 2-gram candies.
          For a fair division to be possible:
            - Total weight must be even (so each person gets equal weight)
            - If there are an odd number of 1-gram candies, it's impossible unless we can balance with 2-gram candies
            - If there are no 1-gram candies and an odd number of 2-gram candies, it's impossible

Time Complexity: O(n) for each test case, where n is the number of candies.
Space Complexity: O(1), constant extra space.

Input:
  t - number of test cases
  For each test case:
    n - number of candies
    Array of n integers (each 1 or 2)

Output:
  "YES" if candies can be divided fairly, otherwise "NO"
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long ones(0), twos(0);
    while (n--) {
      long x;
      scanf("%ld", &x);
      ones += (x == 1);   // Count number of 1-gram candies
      twos += (x == 2);   // Count number of 2-gram candies
    }
    bool possible(true);
    if (ones % 2) {          // If odd number of 1-gram candies
      possible = false;      // It's impossible to split evenly unless we can balance with 2s
    } else if ((ones == 0) && (twos % 2)) { // If no 1-grams but odd number of 2-grams
      possible = false;      // Impossible to split evenly
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/
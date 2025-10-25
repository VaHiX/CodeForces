// Problem: CF 1662 A - Organizing SWERC
// https://codeforces.com/contest/1662/problem/A

/*
Problem: A. Organizing SWERC
Purpose: Given a set of problems with beauty scores and difficulties, select one problem per difficulty (1-10) such that the total beauty score is maximized. If any difficulty is missing, output "MOREPROBLEMS".

Algorithms/Techniques:
- Greedy approach: For each difficulty level, keep the maximum beauty score among all problems of that difficulty.
- Linear scan and comparison.

Time Complexity: O(n) per test case, where n is the number of problems.
Space Complexity: O(1), since we use a fixed-size array of size 10.
*/

#include <algorithm>
#include <cstdio>
using namespace std;
int a[20]; // Array to store the maximum beauty score for each difficulty level (1-10)
int main() {
  int T = 0;
  scanf("%d", &T); // Read number of test cases
  while (T--) {
    int n = 0;
    scanf("%d", &n); // Read number of problems
    for (int i = 1; i <= 10; i++)
      a[i] = 0; // Initialize all difficulty levels to 0
    for (int i = 1, b = 0, d = 0; i <= n; i++) {
      scanf("%d%d", &b, &d); // Read beauty and difficulty of current problem
      a[d] = max(a[d], b); // Keep track of maximum beauty for each difficulty
    }
    int sum = 0;
    bool fl = 1; // Flag to check if all difficulties are covered
    for (int i = 1; i <= 10; i++) {
      if (!a[i]) { // If any difficulty is missing
        fl = 0;
        break;
      }
      sum += a[i]; // Add max beauty score for this difficulty to total
    }
    if (fl)
      printf("%d\n", sum); // Print total beauty if all difficulties are present
    else
      puts("MOREPROBLEMS"); // Otherwise, print message requesting more problems
  }
}


// https://github.com/VaHiX/codeForces/
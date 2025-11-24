// Problem: CF 1914 B - Preparing for the Contest
// https://codeforces.com/contest/1914/problem/B

/*
Code Purpose:
This program solves the problem of arranging n problems with increasing difficulty levels (1 to n) such that Monocarp gets excited exactly k times. 
Excitement occurs when a problem with higher difficulty is solved after a problem with lower difficulty, excluding the first problem.

Algorithm/Techniques:
- Greedy approach:
  1. First, place the first k problems in ascending order (1, 2, ..., k). This ensures no excitement yet.
  2. Then, place the remaining problems (from n down to k+1) in descending order.
     This guarantees exactly k excitations, because each of the last (n - k) problems is harder than all previous ones.

Time Complexity: O(n)
Space Complexity: O(1)

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    // Print first k numbers in ascending order
    for (long p = 1; p <= k; p++) {
      printf("%ld ", p);
    }
    // Print remaining numbers in descending order
    for (long p = n; p > k; p--) {
      printf("%ld ", p);
    }
    puts(""); // Newline after each test case
  }
}


// https://github.com/VaHiX/CodeForces/
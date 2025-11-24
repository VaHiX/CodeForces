// Problem: CF 1644 B - Anti-Fibonacci Permutation
// https://codeforces.com/contest/1644/problem/B

/*
Code Purpose:
This program generates n distinct anti-Fibonacci permutations of length n for each test case.
An anti-Fibonacci permutation ensures that for any three consecutive elements p[i-2], p[i-1], p[i], 
the condition p[i-2] + p[i-1] != p[i] holds.
The algorithm uses a clever construction where for each permutation, we fix one position to 1 and 
decrease the rest in reverse order, rotating this pattern for n permutations.

Algorithms/Techniques:
- Construction technique: For each of the n permutations, we place 1 at position p and fill remaining positions 
  in decreasing order starting from n down to 2.
- Time Complexity: O(n^2) per test case — nested loops iterate over n elements n times.
- Space Complexity: O(1) — only using a few variables, no extra space proportional to input size.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      long x(n);
      for (long u = 0; u < n; u++) {
        // Place 1 at position p, otherwise decrease x from n down to 2
        printf("%ld ", (u == p) ? 1 : x--);
      }
      puts(""); // Print new line after each permutation
    }
  }
}


// https://github.com/VaHiX/CodeForces/
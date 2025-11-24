// Problem: CF 1388 B - Captain Flint and a Long Voyage
// https://codeforces.com/contest/1388/problem/B

/*
Problem: Captain Flint and a Long Voyage
Purpose: Given a number of digits n, find the smallest number x of length n such that when we concatenate binary representations of its digits,
         and then remove the last n digits from this concatenation, the resulting number r is maximized.

Algorithms/Techniques:
- Greedy approach to construct the optimal number
- For each digit position, decide how to assign value to maximize final result

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding output space

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Calculate number of '8's to place at the beginning
    long g = (n + 3) / 4;
    // Print '9's for all positions except the first g ones
    for (long p = g; p < n; p++) {
      printf("9");
    }
    // Print '8's for the first g positions
    for (long p = 0; p < g; p++) {
      printf("8");
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 1753 B - Factorial Divisibility
// https://codeforces.com/contest/1753/problem/B

/*
 * Problem: Factorial Divisibility
 *
 * Given an integer x and an array of integers a_1, a_2, ..., a_n,
 * determine if the sum of factorials a_1! + a_2! + ... + a_n! is divisible by
 * x!.
 *
 * Approach:
 * - Precompute the count of each value in the array.
 * - For each value i from 1 to x-1, check if the count of i is divisible by
 * (i+1). If not, return "No".
 * - Accumulate the count of (i+1) by dividing count of i by (i+1), which
 * simulates how the factorials would combine.
 * - If all checks pass, return "Yes".
 *
 * Time Complexity: O(x + n)
 * Space Complexity: O(x)
 *
 * Algorithms/Techniques:
 * - Counting sort approach
 * - Modular arithmetic
 * - Simulation of factorial decomposition
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 5e5;
int n, x, a[N + 1], w;
int main() {
  scanf("%d %d", &n, &x);
  while (n--)
    scanf("%d", &w), ++a[w]; // Count occurrences of each number in the array
  for (int i = 1; i < x; ++i) {
    if (a[i] % (i + 1) !=
        0) { // If count of i is not divisible by (i+1), it's not divisible
      puts("No");
      return 0;
    }
    a[i + 1] +=
        a[i] / (i + 1); // Accumulate the count to the next factorial level
  }
  puts("Yes");
}

// https://github.com/VaHiX/CodeForces/
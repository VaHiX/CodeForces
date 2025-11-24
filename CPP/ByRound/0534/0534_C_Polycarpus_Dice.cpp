// Problem: CF 534 C - Polycarpus' Dice
// https://codeforces.com/contest/534/problem/C

/*
C. Polycarpus' Dice
Algorithm: For each die, determine how many values it could not have shown given the total sum A and the maximum value each die can show.
Techniques: Greedy approach with range constraints.
Time Complexity: O(n)
Space Complexity: O(n)

This problem involves determining for each die the number of values it could not possibly have shown,
given that all dice together sum to A, and each die has a maximum value.
We compute the minimum and maximum possible values each die can show based on:
- The total sum A
- The sum of all dice S
- The individual die maximums d[i]
Then we calculate how many values are excluded from each die's range.
*/

#include <cstdio>
#include <vector>
int main() {
  long long n, A;
  scanf("%lld %lld\n", &n, &A);
  std::vector<long long> d(n);
  long long S(0); // Sum of all dice max values
  for (int p = 0; p < n; p++) {
    scanf("%lld", &d[p]);
    S += d[p];
  }
  for (int p = 0; p < n; p++) {
    // Minimum value that this die could have shown
    long long m = A - S + d[p]; 
    if (m < 1) {
      m = 1;
    }
    // Maximum value that this die could have shown
    long long M = A - n + 1; 
    if (M > d[p]) {
      M = d[p];
    }
    // Number of values this die couldn't show = total possible - possible values
    long long possible = d[p] - (M - m + 1);
    printf("%lld ", possible);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 2048 B - Kevin and Permutation
// https://codeforces.com/contest/2048/problem/B

/*
Purpose: This code solves the problem of constructing a permutation of length n such that the sum of minimum values over all subarrays of length k is minimized.

Approach:
- The idea is to place the smallest numbers at positions where they contribute to the minimums of as few subarrays as possible.
- We first place numbers in a pattern where we start from the k-th element and step by k, assigning the smallest available numbers.
- Then, we fill the remaining positions with the rest of the numbers in increasing order.

Key Observation:
- To minimize the sum, we want to avoid placing small values in overlapping subarray windows.
- By placing numbers in a gap pattern (step size k), we ensure minimal overlap in the contribution to subarray minima.

Time Complexity: O(n)
Space Complexity: O(n)

Algorithms/Techniques:
- Greedy placement with stride k
- Simulation of permutation construction
*/

#include <iostream>

#define LL long long
using namespace std;
int a[1000000];
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
      a[i] = 0;  // Initialize array to 0
    int las = k, rp = 1;
    while (las <= n) {
      a[las] = rp++;  // Place smallest numbers at positions with stride k
      las += k;
    }
    for (int i = 1; i <= n; i++) {
      if (a[i] == 0)
        a[i] = rp++;  // Fill remaining positions with next available numbers
      cout << a[i] << ' ';
    }
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
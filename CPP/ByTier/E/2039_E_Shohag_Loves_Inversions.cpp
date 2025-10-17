// Problem: CF 2039 E - Shohag Loves Inversions
// https://codeforces.com/contest/2039/problem/E

/*
E. Shohag Loves Inversions
Algorithm: Dynamic Programming with transitions based on inversion counts.
Time Complexity: O(n) per test case
Space Complexity: O(n)

The problem models the process of building arrays by inserting inversion counts at each step.
We use dynamic programming where:
- a[i] represents the number of ways to form an array of length i such that the last element is 0
- b[i] represents the number of ways to form an array of length i such that the last element is 1

Transitions:
- For a[i]: a[i] = (a[i-1] * i - b[i]) % M
- For b[i]: b[i] = (a[i-2] + b[i-1] + 1) % M

Initial values are set as:
- a[2] = 1, b[3] = 1, a[3] = 2

The recurrence relation ensures all valid sequences of insertions leading to distinct arrays of length n are counted.
*/

#include <iostream>

using namespace std;
const long long M = 998244353;
long long a[1000001], b[1000001];
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    a[2] = b[3] = 1;
    a[3] = 2;
    for (int i = 4; i <= n; ++i) {
      b[i] = (a[i - 2] + b[i - 1] + 1 + M) % M; // compute b[i] using previous values
      a[i] = (a[i - 1] * (long long)i - b[i] + M) % M; // compute a[i] using recurrence
    }
    cout << a[n] << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
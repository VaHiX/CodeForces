// Problem: CF 1512 G - Short Task
// https://codeforces.com/contest/1512/problem/G

/*
G. Short Task
Time Complexity: O(Max log Max + t), where Max = 1e7
Space Complexity: O(Max)

Algorithm:
- Precompute for each number n from 1 to Max, the sum of its divisors d(n) using a nested loop.
- For each divisor i of j, add i to yz[j].
- Then, for each possible sum s (up to Max), store the smallest number n such that d(n) = s in ans[s].
- For each query, output ans[n] if it exists, otherwise -1.

Techniques:
- Sieve-like approach to compute divisor sums.
- Preprocessing with lookup table for fast queries.
*/

#include <iostream>

using namespace std;
const int Max = 1e7;
int t, n, yz[Max], ans[Max];  // yz[i] stores sum of divisors of i; ans[i] stores minimal n such that d(n) = i
int main() {
  for (int i = 1; i <= Max; ++i) {       // For each number i from 1 to Max
    for (int j = i; j <= Max; j += i)    // For each multiple j of i
      yz[j] += i;                        // Add i to sum of divisors of j
    if (yz[i] <= Max && !ans[yz[i]])     // If sum of divisors is within range and not yet assigned
      ans[yz[i]] = i;                    // Store the minimal n for this sum
  }
  cin >> t;
  while (t--) {
    cin >> n;
    cout << (ans[n] == 0 ? -1 : ans[n]) << endl;  // Output result or -1 if not found
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
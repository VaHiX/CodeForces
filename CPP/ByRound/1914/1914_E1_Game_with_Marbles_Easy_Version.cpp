// Problem: CF 1914 E1 - Game with Marbles (Easy Version)
// https://codeforces.com/contest/1914/problem/E1

/*
Algorithm: Game Theory with Greedy Strategy
Approach:
- For each color, compute the total number of marbles (Alice's + Bob's).
- Sort colors in descending order of total marbles.
- Simulate the game: 
  - Alice (even indices in sorted list) picks a color and keeps a[idx] - 1 marbles (discards 1).
  - Bob (odd indices in sorted list) picks a color and keeps b[idx] - 1 marbles (discards 1).
- The score is calculated as the difference between Alice's and Bob's final marbles.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the vector of pairs and input arrays
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    std::vector<ll> b(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &b[p]);
    }
    std::vector<std::pair<ll, ll>> s(n);
    for (long p = 0; p < n; p++) {
      // Compute total marbles for each color
      s[p].first = a[p] + b[p];
      s[p].second = p;
    }
    // Sort colors in descending order of total marbles
    sort(s.rbegin(), s.rend());
    ll res(0);
    for (long p = 0; p < n; p++) {
      long idx = s[p].second;
      // If it's Bob's turn (odd index), subtract his remaining marbles (b[idx] - 1)
      if (p % 2) {
        res -= (b[idx] - 1);
      } else {
        // If it's Alice's turn (even index), add her remaining marbles (a[idx] - 1)
        res += a[idx] - 1;
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/CodeForces/
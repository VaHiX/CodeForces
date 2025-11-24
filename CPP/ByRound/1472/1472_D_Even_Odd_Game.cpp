// Problem: CF 1472 D - Even-Odd Game
// https://codeforces.com/contest/1472/problem/D

/*
D. Even-Odd Game
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Algorithms/Techniques:
Greedy approach with sorting.
- Sort the array in descending order to allow optimal selection of elements.
- Alice gains points only when she picks an even number (at even indices in sorted list).
- Bob gains points only when he picks an odd number (at odd indices in sorted list).
- The game alternates turns, so we simulate the process using index parity.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the array.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]); // Read each element of the array
    }
    sort(a.rbegin(), a.rend()); // Sort in descending order to prioritize larger values
    ll score(0); // Alice's net score (positive = Alice wins, negative = Bob wins)
    for (ll p = 0; p < n; p++) {
      if (p % 2 == 0 && a[p] % 2 == 0) {
        // Alice's turn (even index), and she picks an even number → add to her score
        score += a[p];
      }
      if (p % 2 == 1 && a[p] % 2 == 1) {
        // Bob's turn (odd index), and he picks an odd number → subtract from Alice's score (since it's his gain)
        score -= a[p];
      }
    }
    if (score > 0) {
      puts("Alice");
    } else if (score < 0) {
      puts("Bob");
    } else {
      puts("Tie");
    }
  }
}


// https://github.com/VaHiX/codeForces/
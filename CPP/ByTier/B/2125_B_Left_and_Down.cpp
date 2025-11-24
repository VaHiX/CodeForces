// Problem: CF 2125 B - Left and Down
// https://codeforces.com/contest/2125/problem/B

// B. Left and Down
// Problem Description:
// A robot is at position (a, b) on an infinite grid and needs to reach (0, 0).
// Each move consists of moving dx cells left and dy cells down where 0 <= dx, dy <= k.
// The cost of a move is 1 if the pair (dx, dy) is used for the first time, else 0.
// Goal: Find minimum total cost to reach (0, 0).

// Algorithm:
// Key insight: We want to minimize unique pairs used.
// Let g = gcd(a, b). Then we can reduce the problem to finding how many moves
// are needed with steps of size (a/g, b/g), and determine if these fits in k.
//
// If a/g + b/g <= 2*k and both a/g <= k and b/g <= k:
//   - We can reach (0,0) using exactly one unique pair (a/g, b/g)
//   - So cost = 1
// Else:
//   - Need at least two moves (at least two different pairs)
//   - Cost = 2

// Time Complexity: O(log(min(a,b))) per test case due to GCD computation.
// Space Complexity: O(1), only using a few variables.

#include <cstdio>
typedef long long ll;

ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, k;
    scanf("%lld %lld %lld", &a, &b, &k);
    ll g = gcd(a, b); // Find GCD of a and b
    // Check if we can reach (0, 0) with one unique pair (a/g, b/g)
    int res = 2 - (a / g + b / g <= 2 * k && a / g <= k && b / g <= k);
    printf("%d\n", res);
  }
}


// https://github.com/VaHiX/codeForces/
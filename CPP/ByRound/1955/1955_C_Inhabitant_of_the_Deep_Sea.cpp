// Problem: CF 1955 C - Inhabitant of the Deep Sea
// https://codeforces.com/contest/1955/problem/C

/*
C. Inhabitant of the Deep Sea
Algorithm: Simulation with deque to efficiently manage first and last elements.
Time Complexity: O(n) per test case, as each element is pushed/popped at most once from the deque.
Space Complexity: O(n) for storing the deque.

The Kraken attacks ships in alternating order (first, last, first, last, ...).
Each attack reduces durability by 1.
When a ship's durability reaches 0, it sinks and is removed from the fleet.
We simulate this using a deque to efficiently access and remove from both ends.
*/

#include <cstdio>
#include <deque>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::deque<ll> dq(n);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      dq.push_back(x); // Fill deque with ship durabilities
    }
    while (k && dq.size() > 1) {
      int mn = (dq.front() < dq.back() ? dq.front() : dq.back()); // Find minimum durability of first and last ship
      int rem = (k < (2 * mn) ? k : (2 * mn)); // Calculate how many attacks can be made on these two ships before one sinks
      dq.front() -= (rem + 1) / 2;   // Reduce durability of front ship
      dq.back() -= (rem / 2);        // Reduce durability of back ship
      if (dq.front() == 0) {
        dq.pop_front(); // Remove front ship if it sunk
      }
      if (dq.back() == 0) {
        dq.pop_back(); // Remove back ship if it sunk
      }
      k -= rem; // Decrease remaining attacks
    }
    if (!dq.empty()) {
      dq.front() -= k;  // Use leftover attacks on the remaining ship
      if (dq.front() <= 0) {
        dq.pop_front(); // If it sinks, remove it
      }
    }
    printf("%lld\n", n - dq.size()); // Print number of sunk ships
  }
}


// https://github.com/VaHiX/codeForces/
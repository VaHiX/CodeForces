// Problem: CF 1435 A - Finding Sasuke
// https://codeforces.com/contest/1435/problem/A

/*
Code Purpose:
This program solves the problem of finding a set of seal energies that can open a door in Orochimaru's lair.
Each door has n seals with energies a_i, and we need to find energies b_i such that the dot product of a and b is zero.
The algorithm uses a pairing strategy: for every two consecutive seals, we assign b_i = a[i+1] and b[i+1] = -a[i].
This ensures that a[i]*b[i] + a[i+1]*b[i+1] = a[i]*a[i+1] + a[i+1]*(-a[i]) = 0, which satisfies the condition.
Time Complexity: O(n) per door, where n is the number of seals, since we process each pair once.
Space Complexity: O(n) for storing the seal energies.
*/
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
      scanf("%lld", &a[p]);
    }
    // For each pair of consecutive elements, assign b[i] = a[i+1], b[i+1] = -a[i]
    for (ll p = 0; p < n; p += 2) {
      printf("%lld %lld ", a[p + 1], -a[p]);
    }
    puts(""); // Print newline after each door's solution
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
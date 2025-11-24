// Problem: CF 1613 C - Poisoned Dagger
// https://codeforces.com/contest/1613/problem/C

/*
C. Poisoned Dagger
Algorithms/Techniques: Binary search on the answer + greedy validation
Time Complexity: O(n * log(H)) where H is the maximum possible value of h (10^18)
Space Complexity: O(n) for storing attack times

The problem asks to find the minimum poison duration k such that total damage dealt 
by n attacks is at least h. Each attack at second a[i] applies poison that lasts k seconds,
dealing 1 damage per second. If a new attack occurs before previous poison ends, it overwrites it.
We use binary search on k and for each candidate k, we validate if total damage >= h using a greedy sweep.
*/
#include <cstdio>
#include <vector>
typedef long long ll;

// Function to check if poison duration k is sufficient to deal at least h damage
bool check(const std::vector<ll> &a, const ll &h, const ll &k) {
  ll sum(0), cur(0); // sum: total damage, cur: end time of current poison effect
  for (ll p = 0; p < a.size(); p++) {
    // Calculate how much new poison can be added
    ll tst = a[p] + k - cur;
    // Add damage only if there's overlap with existing poison or enough space to add full k seconds
    sum += (tst < k) ? tst : k;
    // Update the end time of current poison effect
    cur = a[p] + k;
  }
  return (sum >= h); // Return true if total damage meets or exceeds required h
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, h;
    scanf("%lld %lld", &n, &h);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    ll left(0), right(h), res(0); // Binary search bounds and result
    while (left <= right) {
      ll mid = (left + right) / 2;
      if (check(a, h, mid)) { // If current k is sufficient
        res = mid;          // Store this as a candidate answer
        right = mid - 1;    // Try smaller k
      } else {
        left = mid + 1;     // Try larger k
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/
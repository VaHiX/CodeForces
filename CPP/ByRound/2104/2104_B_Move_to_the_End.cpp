// Problem: CF 2104 B - Move to the End
// https://codeforces.com/contest/2104/problem/B

/*
B. Move to the End
Algorithms/Techniques: Prefix max, suffix sum
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

For each k from 1 to n:
- Choose an element to move to the end such that the sum of last k elements is maximized.
- This is done by precomputing:
  - mv[p]: maximum value from index 0 to p
  - sv[p]: suffix sum from index p to n-1
- Then for each k, we consider moving an element and compute optimal sum as:
  mv[p] + (sum of elements after p)
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
    std::vector<ll> v(n), mv(n), sv(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
    }
    // mv[p] stores the maximum element from index 0 to p
    mv[0] = v[0];
    for (ll p = 1; p < n; p++) {
      mv[p] = (mv[p - 1] > v[p]) ? mv[p - 1] : v[p];
    }
    // sv[p] stores the suffix sum from index p to n-1
    sv.back() = v.back();
    for (ll p = n - 2; p >= 0; p--) {
      sv[p] = sv[p + 1] + v[p];
    }
    // For each k, compute maximum sum of last k elements by choosing optimal move
    for (ll p = n - 1; p >= 0; p--) {
      printf("%lld ", mv[p] + ((p + 1 < n) ? sv[p + 1] : 0));
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/
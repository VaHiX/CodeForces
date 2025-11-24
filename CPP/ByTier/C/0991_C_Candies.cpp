// Problem: CF 991 C - Candies
// https://codeforces.com/contest/991/problem/C

#include <cstdio>
typedef long long ll;
// Binary search on the answer to find the minimal k such that Vasya eats at least half of n candies.
// Algorithm: 
//   - For a given k, simulate the process and count how many candies Vasya eats.
//   - Use binary search over k from 1 to n+1 to find minimal valid k.
// Time Complexity: O(log n * log n) - binary search takes O(log n), and each check takes O(log n)
// Space Complexity: O(1) - only using a few variables
bool check(ll n, ll k) {
  ll v(0), t(n);
  while (t > 0) {
    ll u = (t < k) ? t : k;  // Vasya eats min(k, remaining candies)
    v += u;
    t -= u;                  // Vasya eats u candies
    t -= (t / 10);           // Petya eats floor(t/10) candies
  }
  return (2 * v >= n);       // Check if Vasya eats at least half of n
}
int main() {
  ll n;
  scanf("%lld", &n);
  ll left(1), right(n + 1), ans(-1);
  while (left <= right) {
    ll mid = (left + right) / 2;
    if (check(n, mid)) {
      ans = mid;
      right = mid - 1;   // Try to find smaller k
    } else {
      left = mid + 1;    // Need larger k
    }
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 1213 C - Book Reading
// https://codeforces.com/contest/1213/problem/C

/*
C. Book Reading
Algorithm: For each query, we calculate the sum of last digits of all pages divisible by m up to n.
We use a pattern recognition approach:
- We find how many full cycles of 10 pages (1-10) are there in the numbers divisible by m.
- Each cycle contributes the same sum of last digits: sum(1%m, 2%m, ..., 10%m)
- The remaining partial cycle (less than 10) is computed separately.
Time Complexity: O(1) per query
Space Complexity: O(1)
*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll b(n / m), s(0); // b = number of pages divisible by m, s = sum of last digits in one full cycle
    std::vector<ll> a(10); // a[p] stores last digit of (p+1)*m
    for (ll p = 0; p < 10; p++) {
      a[p] = ((p + 1) * m) % 10; // compute last digit for multiples of m in range [1, 10]
      s += a[p]; // sum all last digits in one cycle
    }
    ll t = (b / 10) * s; // full cycles contribute this much
    b %= 10;             // remaining pages after full cycles
    for (long p = 0; p < b; p++) {
      t += a[p]; // add last digits for partial cycle
    }
    printf("%lld\n", t);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
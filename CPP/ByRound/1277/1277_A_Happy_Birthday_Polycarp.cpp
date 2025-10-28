// Problem: CF 1277 A - Happy Birthday, Polycarp!
// https://codeforces.com/contest/1277/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll cur(0), cnt(0);
    for (ll p = 0; p < 10; p++) {
      cur = 10 * cur + 1; // Build numbers like 1, 11, 111, etc.
      for (ll u = 1; u <= 9; u++) {
        cnt += (u * cur <= n); // Count how many multiples of current beautiful number are <= n
      }
    }
    printf("%lld\n", cnt);
  }
  return 0;
}
/*
Flowerbox:
Problem: Count beautiful numbers from 1 to n (inclusive), where a beautiful number is composed of only one repeated digit.
Algorithm: Generate all possible beautiful numbers up to 10^10 (since n <= 10^9), and for each, count how many multiples of it are <= n.
Time Complexity: O(1) per test case — constant time since we loop at most 10 digits and 9 multipliers.
Space Complexity: O(1) — only using a few variables.
*/

// https://github.com/VaHiX/codeForces/
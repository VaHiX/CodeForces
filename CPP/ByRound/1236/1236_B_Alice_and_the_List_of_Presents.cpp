// Problem: CF 1236 B - Alice and the List of Presents
// https://codeforces.com/contest/1236/problem/B

/*
Code purpose: This program calculates the number of ways to distribute n kinds of presents into m distinct boxes,
              following the rules that each box can contain at most one present of each kind and every kind must be
              present in at least one box.

Algorithms/Techniques: 
- Inclusion-exclusion principle combined with exponentiation by squaring.
- For each kind of present, we choose a non-empty subset of boxes to place it in.
- The number of ways to distribute n kinds of presents into m boxes, such that each kind is in at least one box, 
  is calculated using the formula (2^m - 1)^n modulo 10^9 + 7.

Time Complexity: O(log m + log n) due to fast exponentiation
Space Complexity: O(1) - only a few variables are used.

*/
#include <stdio.h>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010
#define inf 1e9
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<ll, ll>
using namespace std;
ll mod = 1e9 + 7;
ll fast_expo(ll x, ll y) {
  ll res = 1;
  x = x % mod;
  while (y > 0) {
    if (y & 1) // If y is odd, multiply x with result
      res = (res * x) % mod;
    y = y >> 1; // y = y/2
    x = (x * x) % mod; // x = x^2
  }
  return (res + mod) % mod; // Ensure result is positive
}
int main() {
  int i, j, k;
  ll n, m;
  sffl(n, m);
  ll temp = fast_expo(2, m) - 1; // Calculate 2^m - 1
  cout << (fast_expo(temp, n)) % mod << endl; // Calculate (2^m - 1)^n modulo 10^9 + 7
  return 0;
}


// https://github.com/VaHiX/CodeForces/
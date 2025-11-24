// Problem: CF 1214 A - Optimal Currency Exchange
// https://codeforces.com/contest/1214/problem/A

/*
A. Optimal Currency Exchange
Algorithms/Techniques: Brute force with optimization
time limit per test
1.5 seconds
memory limit per test
512 megabytes
input
standard input
output
standard output

The problem involves finding the minimum number of rubles remaining after buying a combination of dollar and euro bills.
The approach is to iterate over all possible numbers of dollars (p) that can be bought with n rubles,
and for each such p, calculate how many rubles remain after buying p dollars, then try to minimize
the remainder by optimally choosing euro bills.

Since the price of a euro bill is 5 rubles (e *= 5), we iterate over all valid combinations.
The time complexity is O(n / h) where h is the price of a dollar in rubles (which could be up to 100),
and space complexity is O(1).

*/

#include <cstdio>
typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);
  ll d, h;
  scanf("%lld %lld", &d, &h);
  h *= 5;  // Convert euro price to rubles (since smallest bill is 5)
  ll mn(n);  // Initialize minimum remainder
  for (ll p = 0; p * h <= n; p++) {  // Iterate over all possible number of dollars
    ll rem = (n - p * h) % d;  // Calculate remaining rubles after buying p dollars, then take mod d to find leftover
    mn = (mn < rem) ? mn : rem;  // Update minimum remainder
  }
  printf("%lld\n", mn);
  return 0;
}


// https://github.com/VaHiX/codeForces/
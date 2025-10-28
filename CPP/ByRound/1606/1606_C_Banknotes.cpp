// Problem: CF 1606 C - Banknotes
// https://codeforces.com/contest/1606/problem/C

/*
C. Banknotes
Algorithm: Greedy approach to find minimum amount that requires more than k banknotes.
Time Complexity: O(n * log(k)) per test case due to the loop over denominations and division operations.
Space Complexity: O(n) for storing the vector of denominations.

The problem asks to find the smallest positive integer s such that f(s) > k,
where f(s) is the minimum number of banknotes needed to represent s.
We use a greedy strategy:
- Build the denominations as powers of 10.
- Try to construct the amount using the fewest notes possible.
- We iterate through the denominations from smallest to largest, and for each,
  we calculate how many notes of that denomination are needed.
- For each denomination, greedily use the least number of notes possible to
  keep total number of notes under k.
- If we can't fill up k notes with all smaller denominations, then we take what's left
  and calculate cost for the biggest denomination.

*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      ll y(1);
      while (x--) {  // Compute 10^x
        y = 10 * y;
      }
      v[p] = y;  // Store denomination as power of 10
    }
    ll res(0);
    ++k;  // Adjust k to make it easier to handle in the loop
    for (ll p = 1; k > 0 && p < n; p++) {
      ll diff = v[p] / v[p - 1] - 1;  // How many notes of previous denomination we could have used at once
      ll cnt = (k < diff) ? k : diff;  // Take minimal of available k or potential usage
      res += v[p - 1] * cnt;  // Add value that was covered by current denomination
      k -= cnt;  // Reduce remaining note count
    }
    res += k * v.back();  // Fill the rest with largest denomination
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 1916 C - Training Before the Olympiad
// https://codeforces.com/contest/1916/problem/C

/*
C. Training Before the Olympiad
Purpose:
  This program computes the final value of an array after a series of operations,
  where players (Masha and Olya) take turns merging two elements using a specific formula
  until only one element remains. For each prefix of the input array, it determines
  the final number when both players play optimally.

Algorithm:
  - For each prefix of size k, simulate the game using a greedy approach.
  - The key insight is to count odd numbers in the current prefix and decide how many
    merges can be performed based on parity of odd counts.
  - The result is computed dynamically by updating sum and odd count as we process elements.

Time Complexity:
  O(n) per test case, where n is the size of the array.
Space Complexity:
  O(1), as only a constant amount of extra space is used beyond input storage.

Techniques:
  - Prefix processing with cumulative state tracking
  - Greedy merging strategy based on odd count mod 3
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll cs(0), cnt(0);  // cs = cumulative sum, cnt = count of odd numbers
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      cs += x;             // Add current element to sum
      cnt += (x % 2);      // Increment odd count if x is odd
      ll ans(cs);          // Start with total sum as baseline

      // Depending on number of odds, adjust based on how many merges are possible
      if (cnt % 3 == 0 || cnt % 3 == 2) {
        ans -= (cnt / 3);  // If even or 2 mod 3, subtract one less merge
      } else if (cnt % 3 == 1 && p > 0) {
        ans -= ((cnt / 3) + 1);  // If 1 mod 3 and not first element, subtract extra merge
      }
      printf("%lld ", ans);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/
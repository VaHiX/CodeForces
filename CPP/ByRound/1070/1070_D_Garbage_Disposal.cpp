// Problem: CF 1070 D - Garbage Disposal
// https://codeforces.com/contest/1070/problem/D

/*
D. Garbage Disposal
Algorithm: Greedy approach with online processing of garbage units.
Time Complexity: O(n)
Space Complexity: O(1)

This problem uses a greedy strategy to minimize the number of bags needed.
We process each day's garbage and decide whether to carry over any leftover garbage 
from previous days to the current day. A bag is filled completely (up to capacity k) 
whenever possible. Any remainder from this filling is carried forward to the next day.
The total number of bags used is computed by counting:
- Full bags used each day
- Extra bags needed for leftover garbage at the end

Key idea: At each step, we greedily fill as many full bags as possible,
and carry forward any remaining garbage to be used in future days.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  ll prev(0), cnt(0); // prev: leftover garbage from previous day; cnt: total bags used

  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);

    // If there was leftover garbage from yesterday and adding today's garbage
    // would still be less than capacity k, then we need a new bag for today's garbage
    if (prev > 0 && prev + x < k) {
      ++cnt;  // Use one more bag for current day's garbage (we cannot combine it)
      prev = 0;  // No leftover after this
    } else {
      // Combine yesterday's and today's garbage, then compute how many full bags we can make
      x += prev;
      cnt += x / k;   // Add number of full bags needed
      prev = x % k;   // Store leftover for next day
    }
  }

  // If there is any garbage left at the end (prev > 0), it needs one more bag
  cnt += (prev > 0);
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 1084 B - Kvass and the Fair Nut
// https://codeforces.com/contest/1084/problem/B

/*
B. Kvass and the Fair Nut
Algorithms/Techniques: Binary search on the answer, greedy approach
Time complexity: O(n * log(max_v))
Space complexity: O(n)

The problem asks us to determine the maximum possible minimum value in the kegs after pouring s liters of kvass,
where each keg can only contribute up to its current amount of kvass.
We use binary search on the answer: for a given minimum value (mid), we check if it's possible to pour s liters such that
no keg ends up with less than mid liters.

Key idea:
- If we want the minimum value in all kegs to be at least 'mid', then from any keg with value v, 
  we can take at most (v - mid) liters.
- So for each keg, we calculate how much we can take from it: max(0, v - mid).
- Then sum these values and check if total >= s.

In this implementation:
1. We compute total sum of all kegs and minimum keg volume.
2. If s > total, impossible case → return -1.
3. Otherwise, binary search on the answer (the minimum possible value).
*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, s;
  scanf("%lld %lld", &n, &s);
  ll total(0), mn(1e14); // total sum of all kegs, min keg volume
  std::vector<ll> v(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &v[p]);
    mn = (mn < v[p]) ? mn : v[p]; // track minimum value in kegs
    total += v[p];
  }
  if (s > total) {
    puts("-1"); // not enough kvass in all kegs combined
  } else if (s <= total - n * mn) {
    printf("%lld\n", mn); // if we can take all from other kegs except one, minimum is still mn
  } else {
    // otherwise calculate the actual minimum using binary search logic implicitly
    printf("%lld\n", (total - s) / n);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 1130 B - Two Cakes
// https://codeforces.com/contest/1130/problem/B

/*
B. Two Cakes
Algorithms/Techniques: Greedy algorithm, two pointers

Time Complexity: O(n)
Space Complexity: O(n)

Sasha and Dima want to buy two n-tier cakes. Each cake should consist of n different tiers:
from the size of 1 to the size of n. Tiers should go in order from the smallest to the biggest.
They live on the same street, there are 2*n houses in a row from left to right.
Each house has a pastry shop where you can buy a cake tier.
In each pastry shop you can buy only one tier of only one specific size.
Since the guys carry already purchased tiers, and it is impossible to insert a new tier
in the middle of the cake, they agreed to buy tiers from the smallest to the biggest.
That is, each of them buys tiers in order: 1, then 2, then 3 and so on up to n.
Initially, Sasha and Dima are located near the first (leftmost) house.
Output the minimum distance that they will have to walk in total to buy both cakes.
The distance between any two neighboring houses is exactly 1.
*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n + 1, 0), b(n + 1, 0); // a[x] = first position of tier x, b[x] = second position of tier x
  for (ll p = 1; p <= 2 * n; p++) {
    ll x;
    scanf("%lld", &x);
    if (!a[x]) { // if first occurrence of tier x
      a[x] = p;
    } else {
      b[x] = p; // second occurrence of tier x
    }
  }
  ll total(0), pos(1); // pos is current position, total is the accumulated distance
  for (ll p = 1; p <= n; p++) { // Sasha's path for each tier
    ll dist = pos - a[p]; // distance from current position to first occurrence of tier p
    if (dist < 0) {
      dist = -dist;
    }
    total += dist; // add this distance to total
    pos = a[p]; // update Sasha's position to where he bought tier p
  }
  pos = 1; // reset position for Dima
  for (ll p = 1; p <= n; p++) { // Dima's path for each tier
    ll dist = pos - b[p]; // distance from current position to second occurrence of tier p
    if (dist < 0) {
      dist = -dist;
    }
    total += dist; // add this distance to total
    pos = b[p]; // update Dima's position to where he bought tier p
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/
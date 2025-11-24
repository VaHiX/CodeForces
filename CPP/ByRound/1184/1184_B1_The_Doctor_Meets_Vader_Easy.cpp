// Problem: CF 1184 B1 - The Doctor Meets Vader (Easy)
// https://codeforces.com/contest/1184/problem/B1

/*
B1. The Doctor Meets Vader (Easy)
Time Complexity: O(s log s + b log b)
Space Complexity: O(s + b)

Algorithms/Techniques:
- Sorting
- Prefix sum
- Binary search (implicit via two pointers)

This problem involves assigning spaceships to attack bases based on their attacking power.
Each spaceship can attack all bases with defensive power <= its own attacking power.
We want to compute for each spaceship the total gold it can steal from all attackable bases.

Approach:
1. Sort spaceships by attacking power
2. Sort bases by defensive power
3. Compute prefix sums of gold values for bases (to quickly calculate total gold up to a certain base)
4. For each spaceship, use two pointers to find how many bases it can attack and sum their gold using the prefix sums

*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;

int main() {
  ll s, b;
  scanf("%lld %lld", &s, &b);
  std::vector<std::pair<ll, ll>> a(s); // a[i].first = attacking power, a[i].second = original index
  for (ll p = 0; p < s; p++) {
    scanf("%lld", &a[p].first);
    a[p].second = p; // Store original index for result mapping
  }
  std::vector<std::pair<ll, ll>> d(b); // d[i].first = defensive power, d[i].second = gold
  for (ll p = 0; p < b; p++) {
    scanf("%lld %lld", &d[p].first, &d[p].second);
  }
  sort(a.begin(), a.end()); // Sort spaceships by attacking power
  sort(d.begin(), d.end()); // Sort bases by defensive power

  // Compute prefix sums of gold for bases
  std::vector<ll> sg(b, 0);
  sg[0] = d[0].second; // First element prefix sum
  for (ll p = 1; p < b; p++) {
    sg[p] = sg[p - 1] + d[p].second; // Each position stores total gold from base 0 to p
  }

  std::vector<ll> res(s, 0); // Result array for each spaceship
  ll ind(0); // Pointer for bases
  for (ll p = 0; p < s; p++) {
    // Move pointer to find all attackable bases for current spaceship
    while ((ind < b) && (a[p].first >= d[ind].first)) {
      ++ind;
    }
    // Get total gold that can be stolen using prefix sum
    ll gold = (ind > 0) ? sg[ind - 1] : 0; 
    res[a[p].second] = gold; // Place result at original index
  }
  for (ll p = 0; p < s; p++) {
    printf("%lld ", res[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/
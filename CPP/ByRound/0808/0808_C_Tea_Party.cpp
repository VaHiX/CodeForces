// Problem: CF 808 C - Tea Party
// https://codeforces.com/contest/808/problem/C

/*
 * Problem: Tea Party
 * 
 * Algorithm/Technique: Greedy + Sorting
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing cups and their volumes
 * 
 * Approach:
 * 1. For each cup, calculate the minimum amount of tea it needs to contain (at least half its volume).
 * 2. Sort cups by their volumes in ascending order.
 * 3. For each cup (starting from the second), if it contains less tea than the previous one, 
 *    transfer the difference from the previous cup to satisfy the "satisfaction" condition.
 * 4. After ensuring all conditions are met, distribute the remaining tea to the largest cups 
 *    to maintain the satisfaction constraint.
 * 
 * If at any point it's impossible to satisfy constraints, output -1.
 */

#include <algorithm>
#include <iostream>
#include <utility>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, w, x;
  cin >> n >> w;
  pp a[n]; // Store volume and index of each cup
  ll t[n]; // Store actual tea amount for each cup

  // Initialize cups with minimum required tea (half volume, rounded up if odd)
  for (i = 0; i < n; i++) {
    cin >> x;
    a[i] = {x, i};
    if (x % 2)
      t[i] = x / 2 + 1, w -= t[i]; // If volume is odd, add 1 to make it at least half
    else
      t[i] = x / 2, w -= t[i];     // If volume is even, take half
  }

  // If not enough tea to fill minimum requirement, impossible
  if (w >= 0) {
    ll lagbe;
    sort(a, a + n); // Sort cups by volume

    // Ensure no smaller cup has less tea than a larger one
    for (i = 1; i < n; i++) {
      if (t[a[i].second] < t[a[i - 1].second]) {
        lagbe = t[a[i - 1].second] - t[a[i].second];
        if (w < lagbe) { // Not enough tea to make up the difference
          cout << "-1";
          return 0;
        }
        w -= lagbe;
        t[a[i].second] += lagbe;
      }
    }

    // Distribute remaining tea to largest cups
    i = n - 1;
    while (w && i >= 0) {
      lagbe = a[i].first - t[a[i].second];
      if (lagbe < 0)
        i--;
      else {
        if (w > lagbe) {
          t[a[i].second] += lagbe;
          w -= lagbe;
          i--;
        } else {
          t[a[i].second] += w;
          break;
        }
      }
    }
  } else {
    cout << "-1";
    return 0;
  }

  // Output result
  for (i = 0; i < n; i++)
    cout << t[i] << " ";
  return 0;
}


// https://github.com/VaHiX/CodeForces/
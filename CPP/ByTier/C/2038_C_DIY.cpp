// Problem: CF 2038 C - DIY
// https://codeforces.com/contest/2038/problem/C

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

/*
 * Problem: Find four points from a list of integers that form a rectangle
 *          with sides parallel to axes and maximize the area.
 *
 * Algorithm:
 * 1. Sort the input array.
 * 2. Identify all duplicate elements (these can be used as x or y coordinates for the rectangle).
 * 3. From the duplicates, select the 4 smallest and largest to form a rectangle.
 * 4. Compute two possible rectangle areas and pick the maximum one.
 * 5. Output the coordinates of the resulting rectangle.
 *
 * Time Complexity: O(n log n) due to sorting, where n is the number of elements.
 * Space Complexity: O(n) for storing the input and intermediate vectors.
 */

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
    }
    sort(v.begin(), v.end());
    
    // Collect all duplicated elements.
    std::vector<ll> w;
    for (ll p = 1; p < v.size(); p++) {
      if (v[p - 1] == v[p]) {
        w.push_back(v[p]);
        v[p] = -1e9 - 7; // Mark as used to avoid reprocessing
      }
    }

    // If there are less than 4 duplicates, we can't form a valid rectangle.
    if (w.size() < 4) {
      puts("NO");
      continue;
    }

    sort(w.begin(), w.end());

    // Select two smallest and two largest values from duplicates to form x and y coordinates
    std::vector<ll> u(4);
    u[0] = w[0];
    u[1] = w[1];
    u[2] = w[w.size() - 2];
    u[3] = w[w.size() - 1];

    // Calculate two possible rectangle areas
    ll a = (u[2] - u[0]) * (u[3] - u[1]);  // width * height
    ll b = (u[3] - u[0]) * (u[2] - u[1]);  // height * width

    // Choose the larger area and output appropriate coordinates
    if (a > b) {
      printf("YES\n%lld %lld %lld %lld %lld %lld %lld %lld\n", u[0], u[1], u[0],
             u[3], u[2], u[1], u[2], u[3]);
    } else {
      printf("YES\n%lld %lld %lld %lld %lld %lld %lld %lld\n", u[0], u[1], u[0],
             u[2], u[3], u[1], u[3], u[2]);
    }
  }
}

// https://github.com/VaHiX/CodeForces/
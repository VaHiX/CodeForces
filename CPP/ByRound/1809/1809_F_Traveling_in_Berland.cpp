// Problem: CF 1809 F - Traveling in Berland
// https://codeforces.com/contest/1809/problem/F

/*
Purpose: Solve the problem of finding minimum cost to travel through all cities
in a circular ring, where each city has a fuel station and the journey must be
completed in a clockwise direction. The car has a fixed fuel tank capacity and
each road segment requires a certain amount of fuel. Fuel prices vary per city.
We must compute the minimal cost for starting from each city.

Algorithms/Techniques:
- Circular array rotation to simplify processing
- Precomputed prefix and suffix fuel consumption arrays (dl, dr)
- Sliding window technique to efficiently compute total fuel needed for segments
of the journey
- Suffix and prefix sum computation

Time Complexity: O(n) per test case, where n is the number of cities
Space Complexity: O(n) for storing arrays and auxiliary data structures
*/
#include <iostream>
#include <stdio.h>

using namespace std;
#define mx 400005
int a[mx], b[mx];
int aa[mx], bb[mx];
long long dl[mx], dr[mx];
long long ss[mx];
#define endl '\n'
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int tc, n, k;
  cin >> tc;
  while (tc--) {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> b[i];
    int st = -1;
    for (int i = 0; i < n; i++)
      if (b[i] == 1) {
        st = i;
        break;
      }
    if (st == -1) {
      // If no city has fuel price 1, all cities have same price (2), so we can
      // directly compute cost
      long long s = 0;
      for (int i = 0; i < n; i++)
        s += a[i] * b[i];
      for (int i = 0; i < n; i++)
        cout << s << ' ';
      cout << endl;
      continue;
    }
    // Rotate arrays to make the first city with price 1 the starting point
    for (int i = 0; i < n + 1; i++) {
      aa[i] = a[(i + st) % n];
      bb[i] = b[(i + st) % n];
    }
    // Compute prefix fuel needed to reach each city from start (for 0 or 1 fuel
    // price city)
    dl[0] = 0;
    for (int i = 1; i < n; i++) {
      if (bb[i] == 1)
        dl[i] =
            0; // If current city is 1, no extra fuel needed from previous city
      else
        dl[i] = dl[i - 1] + aa[i - 1]; // Accumulate fuel needed from previous
                                       // city to reach this city
    }
    // Compute suffix fuel needed from each city to reach the end (backward)
    dr[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (bb[i] == 1)
        dr[i] = 0; // If current city is 1, no extra fuel needed to reach
                   // destination from next city
      else
        dr[i] =
            dr[i + 1] +
            aa[i]; // Accumulate fuel needed from this city to reach next city
    }
    // Reset ss array
    for (int i = 0; i <= n; i++)
      ss[i] = 0;
    long long s, d, su = 0;
    // Group consecutive cities that do not have fuel price 1 and calculate
    // required fuel
    for (int i = 0, j; i < n; i = j) {
      for (j = i + 1; bb[j] != 1; j++) // Find next city with price 1
        ;
      d = 0;
      for (int t = i; t < j; t++) // Calculate total distance in this segment
        d += aa[t];
      if (d <= k)
        s = d; // If total consumption is less than or equal to tank capacity,
               // no refueling needed
      else
        s = k + (d - k) * 2;          // Otherwise, calculate refueling cost
      for (int t = i + 1; t < j; t++) // Store computed cost for this segment
        ss[t] = s;
      su += s; // Add to total cost
    }
    // For each city, compute the minimal cost to start from it
    for (int i = 0; i < n; i++) {
      int ii = (i + n - st) % n; // Adjust index due to rotation
      if (bb[ii] == 1) { // If this city has lowest fuel price, only pay for the
                         // rest of trip
        cout << su << ' ';
        continue;
      }
      s = su - ss[ii]; // Subtract fuel cost for segment from this city to avoid
                       // double counting
      s += dr[ii] * 2; // Add cost to travel from current city to the end via
                       // the backward path
      if (dl[ii] <= k)
        s += dl[ii]; // Add forward cost
      else
        s += k + (dl[ii] - k) *
                     2; // Add modified cost if forward exceed tank capacity
      cout << s << ' ';
    }
    cout << endl;
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/
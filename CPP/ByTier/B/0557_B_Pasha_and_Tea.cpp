// Problem: CF 557 B - Pasha and Tea
// https://codeforces.com/contest/557/problem/B

/*
Code Purpose:
This program solves the problem of distributing tea between Pasha's friends such that:
- There are n boys and n girls.
- Each girl gets x ml of water, each boy gets 2x ml.
- Total water used does not exceed the teapot capacity w.
- The goal is to maximize the total amount of water distributed.

Algorithm:
1. Sort all cup capacities in ascending order.
2. Try to assign the smallest possible amount of water to each girl (x) such that:
   - Each girl's cup can hold x.
   - Each boy's cup can hold 2x (since boy gets twice as much).
3. Use binary search or direct calculation to find the maximum x such that:
   - Total water needed = n*x + n*2*x = 3*n*x <= w.
4. Return the minimized value between 3*n*x and w.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing cup capacities.
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");
#define inf 1000000000000
using namespace std;
int main() {
  ll i, j, k, l;
  ll n, w;
  cin >> n >> w;
  ll a[2 * n];
  for (i = 0; i < 2 * n; i++)
    cin >> a[i];
  sort(a, a + (n * 2)); // Sort cup capacities in ascending order
  double p;
  // Determine the maximum possible amount per girl
  if (a[0] * 2 <= a[n])
    p = (double)a[0]; // If smallest cup can hold x, then boys' cups should hold at least 2x
  else
    p = (double)a[n] / 2; // If not enough cups for 2x, we cap it at a[n]/2
  // Check if total required water is within limit w
  if (p * 3 * n <= w)
    printf("%lf", (double)p * 3 * n); // Output total water used
  else
    printf("%lf", (double)w); // Cap at teapot capacity
  return 0;
}


// https://github.com/VaHiX/CodeForces/
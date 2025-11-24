// Problem: CF 525 C - Ilya and Sticks
// https://codeforces.com/contest/525/problem/C

/*
 * Problem: Ilya and Sticks
 * 
 * Purpose: To maximize the total area of rectangles formed from given sticks,
 *          where each stick can be reduced in length by at most 1.
 *          Rectangles are formed by 4 sticks with lengths a1, a2, a3, a4 such that:
 *          a1 = a2 and a3 = a4, and a1 <= a2 <= a3 <= a4.
 * 
 * Approach:
 * - Sort the sticks in descending order.
 * - Greedily pair sticks to form rectangles:
 *   - When a stick can be paired with another to form a valid rectangle (difference <= 1),
 *     compute the area and add to the result.
 *   - If a stick cannot form a pair yet, store it and wait for the next one.
 * 
 * Time Complexity: O(n log n) due to sorting, where n is the number of sticks.
 * Space Complexity: O(n) for the array storing stick lengths.
 */

#include <bits/std_abs.h>
#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 310
#define sf(n) scanf("%d", &n)
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  ll a, b, c, d, x;
  sf(n);
  int *arr = new int[n];
  for (i = 0; i < n; i++)
    sf(arr[i]);
  sort(arr, arr + n, greater<int>()); // Sort in descending order to facilitate pairing
  if (n < 4) {
    printf("0");
    return 0;
  }
  ll ans = 0;
  x = 0; // Variable to temporarily hold a stick length for pairing
  for (i = 0; i < n; i += 2) { // Process two sticks at a time
    a = arr[i];
    b = arr[i + 1];
    if (x) {
      // If we already have a stick saved (x), try to pair it with current sticks
      if (abs(a - b) <= 1) {
        // If the difference of the two current sticks is within 1, then they form a valid rectangle
        ans += (x * min(a, b)); // Add area
        x = 0; // Reset x
      } else
        i -= 1; // If not a valid pair, decrement to reprocess this stick later
    } else {
      // If no stick stored in x, try to pair current ones
      if (abs(a - b) <= 1) // Check if current two sticks can be paired
        x = min(a, b); // Store the smaller of the two as one side of a rectangle
      else
        i -= 1; // If not a valid pair, decrement index to reconsider this stick
    }
  }
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
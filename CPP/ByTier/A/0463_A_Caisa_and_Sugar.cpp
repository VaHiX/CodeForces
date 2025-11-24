// Problem: CF 463 A - Caisa and Sugar
// https://codeforces.com/contest/463/problem/A

/*
 * Problem: Caisa and Sugar
 * 
 * Purpose: To determine the maximum number of sweets Caisa can get as change
 *          when buying one type of sugar, given his budget 's' dollars.
 *          Change is given in sweets, where 100 cents = 1 dollar, and change
 *          is maximized by minimizing the dollars in the change.
 * 
 * Algorithm: 
 *   - For each sugar type, check if Caisa can afford it (s >= cost in dollars)
 *   - If affordable, calculate the sweets he gets as change:
 *     - Change in cents = 100 - y[i] (since cents are converted to dollars)
 *   - Track the maximum sweets among all affordable types.
 * 
 * Time Complexity: O(n), where n is the number of sugar types.
 * Space Complexity: O(n), due to storing the cost of each sugar type.
 * 
 * Techniques:
 *   - Greedy approach to maximize sweets in change
 *   - Integer arithmetic for handling dollars and cents
 *   - Simple linear scan through all sugar types
 */

#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define inf 1000000007
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n;
  float s;
  bool f = false; // Flag to check if any sugar is affordable
  ll max = 0;     // Maximum sweets in change
  cin >> n >> s;
  float x[n], y[n]; // Arrays to store cost of each sugar (dollars and cents)

  // Read costs for all sugar types
  for (i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }

  // Check each sugar type for affordability and compute max sweets
  for (i = 0; i < n; i++) {
    // Check if Caisa can afford this sugar type
    if (s >= (x[i] + y[i] / 100)) {
      f = true; // Mark at least one sugar is affordable
      // If the cents are non-zero, calculate sweets in change
      // 100 - y[i] gives the number of sweets for the change
      if (max < (100 - y[i]) && y[i] > 0)
        max = 100 - y[i];
    }
  }

  // Output result
  if (f)
    cout << max;
  else
    cout << "-1";
  return 0;
}


// https://github.com/VaHiX/CodeForces/
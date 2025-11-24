// Problem: CF 2078 D - Scammy Game Ad
// https://codeforces.com/contest/2078/problem/D

/*
 * Problem: D. Scammy Game Ad
 *
 * Purpose: Simulate a game with pairs of gates where each gate performs either
 *          addition (+a) or multiplication (x a) operations on the number of people in lanes.
 *          The goal is to maximize the total number of people at the end.
 *
 * Algorithm:
 * - At each step, process two gates (left and right).
 * - Based on operation types, update three counters x, y, z representing:
 *   - x: left lane count
 *   - y: right lane count
 *   - z: auxiliary sum for computing gains during multipliers
 * - For each pair:
 *   - Add values from both gates with appropriate allocation logic
 *   - Update x and y using z as helper, applying multiplicative operations by updating sums appropriately.
 *   - Handle all combinations (addition-addition, multiplication-addition, etc.)
 *
 * Time Complexity: O(n) per test case, where n is the number of gate pairs.
 * Space Complexity: O(1), constant space usage.
 */

#include <iostream>

#define int long long
using namespace std;
int n, T;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    int x = 1, y = 1, z = 0, a, b;
    char p, q;
    while (n--) {
      cin >> p >> a >> q >> b;  // Read operations for left and right gates
      if (p == '+' && q == '+')
        z += a + b;  // If both are additions, update auxiliary sum
      else if (p == '+' && q == 'x')
        y += z, z = y * (b - 1) + a;  // Left addition, right multiplication: update y and z accordingly
      else if (q == '+' && p == 'x')
        x += z, z = x * (a - 1) + b;  // Right addition, left multiplication: update x and z accordingly
      else if (a == b)
        z += (x + y + z) * (a - 1);  // When both multipliers are same, apply combined effect
      else if (a > b)
        x += z, z = x * (a - 1) + y * (b - 1);  // Left multiplier bigger: use x more, update z
      else if (a < b)
        y += z, z = y * (b - 1) + x * (a - 1);  // Right multiplier bigger: use y more, update z
    }
    cout << x + y + z << "\n";  // Final total number of people
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
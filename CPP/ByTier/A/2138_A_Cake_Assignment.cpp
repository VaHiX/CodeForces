// Problem: CF 2138 A - Cake Assignment
// https://codeforces.com/contest/2138/problem/A

/*
 * Problem: Cake Assignment
 * 
 * Description:
 * Chocola and Vanilla each start with 2^k cakes. They want to redistribute so that
 * Chocola ends up with exactly x cakes. In each step, one can transfer half of the
 * cakes from the person with even number of cakes to the other.
 * 
 * Algorithm:
 * - Represent x in binary form.
 * - Find the position of the first set bit (from LSB).
 * - Use greedy approach based on binary representation to determine how many steps and what operations.
 * 
 * Time Complexity: O(k) per test case (since k <= 60, it's effectively constant)
 * Space Complexity: O(1) additional space
 * 
 * Techniques:
 * - Bit manipulation
 * - Greedy algorithm on binary string of x
 */

#include <iostream>

using namespace std;
#define int long long
int k, x;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> k >> x;
    int pos = 1;
    // Find first set bit in binary representation of x (from LSB)
    for (int i = 1; i <= k + 1; i++)
      if ((x >> i - 1) & 1) {
        pos = i;
        break;
      }
    pos++; // Move to next position since we're dealing with 1-based indexing in output
    cout << k + 1 - pos + 1 << '\n'; // Number of operations needed
    
    // Generate the sequence of operations
    for (int i = pos; i <= k + 1; i++) {
      if ((x >> i - 1) & 1)
        cout << 2 << " "; // Operation 2: Vanilla gives half to Chocola
      else
        cout << 1 << " "; // Operation 1: Chocola gives half to Vanilla
    }
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
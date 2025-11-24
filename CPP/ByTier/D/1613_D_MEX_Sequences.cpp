// Problem: CF 1613 D - MEX Sequences
// https://codeforces.com/contest/1613/problem/D

/*
 * Task: Count the number of non-empty MEX-correct subsequences in an array.
 *
 * Approach:
 * - Uses dynamic programming with two arrays:
 *   - dp1[i]: Number of subsequences ending at position where MEX is i.
 *   - dp2[i]: Number of subsequences where the next element can be added such that MEX is i.
 * - For each element in the array:
 *   - Update dp1[i] based on previous values to maintain MEX correctness.
 *   - Update dp2[i] to track valid extensions to subsequences.
 * - Final answer is sum of all dp1 and dp2 values minus 1 (to exclude empty subsequence).
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int mod = 998244353;

// Utility function to perform modular addition
int add(int x, int y) {
  x = (x + y) % mod;
  return x;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> dp1(n + 2), dp2(n + 2);
    dp1[0] = 1; // Initialize base case: one way to have MEX = 0 with empty sequence
    
    while (n--) {
      int x;
      cin >> x;
      
      // Update dp1 for current element x
      dp1[x + 1] = add(dp1[x + 1], dp1[x + 1]);  // Add existing count (carry forward)
      dp1[x + 1] = add(dp1[x + 1], dp1[x]);      // Add count from previous MEX
      
      // Update dp2 based on element x
      if (x > 0)
        dp2[x - 1] = add(dp2[x - 1], dp2[x - 1]);  // Carry forward
      if (x > 0)
        dp2[x - 1] = add(dp2[x - 1], dp1[x - 1]);  // Add sequences that can extend to x-1
      
      dp2[x + 1] = add(dp2[x + 1], dp2[x + 1]); // Carry forward for current MEX
    }
    
    int ans = 0;
    for (int x : dp1)
      ans = add(ans, x);  // Sum all valid subsequences ending with specific MEX
    for (int x : dp2)
      ans = add(ans, x);  // Sum all valid extensions
    
    // Subtract 1 to exclude empty subsequence, and handle modulo properly
    cout << add(ans, mod - 1) << endl;
  }
}


// https://github.com/VaHiX/CodeForces/
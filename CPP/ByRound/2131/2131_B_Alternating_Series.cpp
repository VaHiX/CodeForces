// Problem: CF 2131 B - Alternating Series
// https://codeforces.com/contest/2131/problem/B

/*
B. Alternating Series
Algorithms/Techniques: Greedy, constructive algorithm
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting output)

The problem asks for constructing a "good" array where:
- Adjacent elements have negative product (alternating signs)
- All subarrays of length >= 2 have positive sum
- The absolute values should form the lexicographically smallest sequence

Strategy:
- Start with -1 to ensure first element is negative
- For even-length arrays, use alternating pattern: 3, -1, 3, -1, ...
- For odd-length arrays, follow same pattern but end with a positive number (2)
- This ensures all subarrays have positive sum (because we're using small absolute values and alternating signs)
*/

#include <iostream>

using namespace std;

void solve() {
  int n;
  cin >> n;
  cout << "-1 ";  // Start with -1 to ensure alternating pattern
  for (int i = 1; i + 2 <= n; i += 2) {  // Process pairs of elements
    cout << "3 -1 ";  // Use 3 and -1 to maintain alternating sign and positive subarray sums
  }
  if (n % 2 == 0)
    cout << 2;  // If even length, end with 2 to have a positive last element
  cout << endl;
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/
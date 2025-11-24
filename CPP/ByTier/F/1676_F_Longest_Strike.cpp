// Problem: CF 1676 F - Longest Strike
// https://codeforces.com/contest/1676/problem/F
 
/*
Purpose: Find the longest contiguous range [l, r] such that every number in the range appears at least k times in the array.
Algorithm: 
    - Count frequency of each number in the array using a map.
    - Iterate through the sorted keys (numbers) in the map.
    - For each number that has frequency >= k, extend the current valid interval if it's contiguous.
    - Track the maximum interval length found.
 
Time Complexity: O(n log n) due to map operations (insertion and iteration)
Space Complexity: O(n) for storing the frequency map
 
Techniques:
    - Frequency counting with map
    - Sliding window / interval merging approach
*/
#include <iostream>
#include <map>
#include <utility>
 
using namespace std;
typedef long long ll;
int n, k, x;
map<int, int> c;
void solve() {
  cin >> n >> k, c.clear(); // Read input and clear frequency map
  for (int i = 1; i <= n; ++i)
    cin >> x, ++c[x]; // Count frequency of each number
  int l = -1, r = -1, L = -1, R = -2; // l,r: current interval; L,R: best interval
  for (auto &[s, t] : c) { // Iterate through sorted numbers
    if (t >= k) { // If number appears at least k times
      if (r < s - 1) // If the current number is not contiguous to the previous interval
        l = r = s; // Start new interval
      else
        r = s; // Extend the interval
      if (R - L + 1 < r - l + 1) // Update best interval if current is longer
        L = l, R = r;
    }
  }
  if (L == -1) // No valid interval found
    cout << -1 << '\n';
  else
    cout << L << ' ' << R << '\n'; // Output the best interval
}
int main() {
  int T;
  cin >> T;
  while (T--)
    solve();
}
 
 
// https://github.com/VaHiX/CodeForces/
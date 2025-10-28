// Problem: CF 1819 A - Constructive Problem
// https://codeforces.com/contest/1819/problem/A

#include <algorithm>
#include <iostream>
#include <map>

using namespace std;
typedef long long ll;
const ll _ = 5e5 + 5;
ll N, n, t, l, r, a[_], i;
bool f;
map<ll, ll> b, c;

// Purpose: Determines if we can increase MEX of the array by exactly 1
//          by assigning some value k to a subsegment of the array.
// Algorithms: 
//   - Uses frequency maps to count occurrences of elements.
//   - Finds the minimum excludant (MEX) of the original array.
//   - Identifies if there's a subsegment that can be filled with (MEX + 1)
//     such that MEX increases by exactly one.
// Time Complexity: O(n) per test case, due to linear traversal and map operations
// Space Complexity: O(n), for storing frequencies and array elements

void P() {
  cin >> n;
  b.clear(); // Clear frequency map of original array
  c.clear(); // Clear frequency map used for checking subsegment
  for (i = 1; i <= n; i++)
    cin >> a[i], b[a[i]]++; // Read and count frequencies of elements
  for (t = 0; b[t]; t++)   // Find MEX of the array
    ;
  for (l = n + 1, r = 0, i = 1; i <= n; i++)
    if (a[i] == t + 1)     // Find bounds of subsegment containing (MEX + 1)
      l = min(l, i), r = max(r, i);
  for (i = l; i <= r; i++)
    c[a[i]]++;             // Count frequencies in this subsegment
  for (f = (t < n), i = 0; i < t; i++)
    if (c[i] == b[i])      // Check if we can make all values from 0 to (MEX-1) appear in same count after update
      f = 0;
  cout << (f ? "Yes\n" : "No\n"); // Output result
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  while (N--)
    P(); // Process multiple test cases
}

// https://github.com/VaHiX/codeForces/
// Problem: CF 2127 A - Mix Mex Max
// https://codeforces.com/contest/2127/problem/A

/*
A. Mix Mex Max
Algorithms/Techniques: Set usage, sliding window analysis, MEX computation

Time Complexity: O(n log n) per test case due to set operations (insert and begin)
Space Complexity: O(n) for the set storage

The problem checks if we can fill -1 values in an array such that for every 
triplet of consecutive elements, the MEX of the triplet equals the difference 
between its max and min. We simplify by considering only non-negative numbers,
and using a set to store unique values to compute MEX efficiently.

Key logic:
- For each test case, we process the input array.
- We only consider non-negative values (ignore -1s).
- If there is at least one element in the set, we check if it's all zeros 
  or has more than one distinct value — which causes MEX != max - min.
*/
#include <iostream>
#include <set>

using namespace std;
int T, n;
set<int> s;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n;
    s.clear(); // Clear the set for new test case
    for (int x; n--;) {
      cin >> x;
      if (x >= 0)
        s.insert(x); // Only insert non-negative numbers
    }
    // If size > 1 or exactly one element which is 0, output "NO"
    // Otherwise, we can make the array good by setting all -1s appropriately
    cout << (s.size() > 1 || s.size() == 1 && !*s.begin() ? "NO\n" : "YES\n");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
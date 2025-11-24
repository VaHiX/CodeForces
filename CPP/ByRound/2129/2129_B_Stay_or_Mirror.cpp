// Problem: CF 2129 B - Stay or Mirror
// https://codeforces.com/contest/2129/problem/B

/*
B. Stay or Mirror
time limit per test2 seconds
memory limit per test256 megabytes

Algorithms/Techniques: Brute Force with Optimization
Time Complexity: O(n^2) per test case
Space Complexity: O(n)

For each element in the permutation, we decide whether to keep it as is (p[i]) 
or mirror it as (2*n - p[i]). For each position, we compute how many elements 
to its right are larger than it in both cases and choose the option that results 
in fewer inversions.

The algorithm calculates for every element:
- How many elements after it are greater than it if we keep it as p[i]
- How many elements after it are greater than it if we mirror it as 2*n - p[i]

Then it takes the minimum of these two values and sums them up.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> v(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }
    for (int i = 0; i < n; i++) {
      int cnt = 0;
      // Count how many elements after i are greater than v[i]
      for (int j = i + 1; j < n; j++) {
        if (v[j] > v[i]) {
          cnt++;
        }
      }
      // cnt2 represents the number of elements that would be greater 
      // than mirrored value (2*n - v[i]) after this element
      int cnt2 = (n - v[i]) - cnt;
      sum += min(cnt, cnt2);
    }
    cout << sum << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 1973 C - Cat, Fox and Double Maximum
// https://codeforces.com/contest/1973/problem/C

/*
Purpose: This code solves the problem of finding a permutation q that maximizes the number of local maxima in the array a, where a[i] = p[i] + q[i].
Algorithms/Techniques: 
  - Greedy approach with careful arrangement of elements based on parity of position of maximum element 'n' in p
  - Sorting pairs of (value, index) to determine optimal placement in q

Time Complexity: O(n log n) per test case due to sorting operations.
Space Complexity: O(n) for storing vectors and pairs.
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <utility>

typedef long long ll;
typedef long double ld;
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++)
      cin >> p[i];
    vector<int> q(n);
    int nid = find(p.begin(), p.end(), n) - p.begin(); // Find index of element 'n' in p
    if (!(nid & 1)) { // If the index of 'n' is even
      vector<pair<int, int>> v;
      // Collect odd-indexed elements from p (1-based) and add p[0] at the end
      for (int i = 1; i < n; i += 2)
        v.push_back({p[i], i});
      v.push_back({p[0], 0});
      // Collect even-indexed elements from p (1-based), skipping last element
      for (int i = 2; i < n; i += 2)
        v.push_back({p[i], i});
      // Sort first half (based on value descending)
      sort(v.begin(), v.begin() + (n / 2), greater<pair<int, int>>());
      // Sort second half (based on value descending)
      sort(v.begin() + (n / 2) + 1, v.begin() + n, greater<pair<int, int>>());
      // Assign values to q based on sorted order
      for (int i = 0; i < n; i++)
        q[v[i].second] = i + 1;
    } else { // If the index of 'n' is odd
      vector<pair<int, int>> v;
      // Collect even-indexed elements from p (1-based)
      for (int i = 0; i < n; i += 2)
        v.push_back({p[i], i});
      v.push_back({p[n - 1], n - 1});
      // Collect odd-indexed elements from p (1-based), skipping last element
      for (int i = 1; i < n - 1; i += 2)
        v.push_back({p[i], i});
      // Sort first half (based on value descending)
      sort(v.begin(), v.begin() + (n / 2), greater<pair<int, int>>());
      // Sort second half (based on value descending)
      sort(v.begin() + (n / 2) + 1, v.begin() + n, greater<pair<int, int>>());
      // Assign values to q based on sorted order
      for (int i = 0; i < n; i++)
        q[v[i].second] = i + 1;
    }
    // Output the constructed permutation q
    for (int i = 0; i < n; i++)
      cout << q[i] << " \n"[i == n - 1];
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
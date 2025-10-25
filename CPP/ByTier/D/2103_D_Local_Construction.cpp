// Problem: CF 2103 D - Local Construction
// https://codeforces.com/contest/2103/problem/D

/*
D. Local Construction

Algorithms/Techniques: Simulation with binary search principles, greedy assignment of values based on removal order.

Time Complexity: O(n log n) per test case due to the iterative process and handling of local minima/maxima.
Space Complexity: O(n) for storing arrays and auxiliary structures.

Task:
Given an array a where each element indicates the iteration when that element is removed from a permutation,
construct any valid permutation p. The removal process alternates between removing non-local minima (odd iterations)
and non-local maxima (even iterations).
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
using pi = pair<int, int>;
const int N = 200005;
int n, a[N], v[N];

void solve() {
  cin >> n;
  vector<int> cur, nxt; // cur holds current indices, nxt will hold indices for next iteration
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    cur.push_back(i); // Initially all elements are in the working set
    if (a[i] == -1)
      a[i] = 0x3f3f3f3f; // Mark unremoved elements as very large
  }
  int l = 1, r = n, idx = 1; // l and r are for assigning values in increasing/decreasing order
  while (cur.size() > 1) {
    nxt.clear(); // Reset next set of indices
    int pre = -1; // Mark previous valid index processed
    for (int i = 0; i < cur.size(); i++) {
      int id = cur[i]; // Get index in current array
      if (a[id] > idx) { // If element would be removed in this step, include it in next iteration
        for (int j = pre + 1; j < i; j++)
          v[cur[j]] = ((idx & 1) ? r-- : l++); // Assign value in alternating order
        nxt.push_back(id);
        pre = i;
      }
    }
    for (int i = cur.size() - 1; i > pre; i--)
      v[cur[i]] = ((idx & 1) ? r-- : l++); // Assign remaining elements to the ends
    idx += 1; // Move to next iteration
    swap(cur, nxt); // Prepare for next loop
  }
  v[cur[0]] = l; // Assign final value to last element
  for (int i = 1; i <= n; i++)
    cout << v[i] << " ";
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/
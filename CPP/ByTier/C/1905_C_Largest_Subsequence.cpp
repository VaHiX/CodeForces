// Problem: CF 1905 C - Largest Subsequence
// https://codeforces.com/contest/1905/problem/C

/*
 * Problem: C. Largest Subsequence
 * 
 * Algorithm/Technique:
 * - Greedy approach to find the lexicographically largest subsequence
 * - Reverse the subsequence to bring characters to the front in sorted order
 * - Check if the final string matches the sorted version
 * - Count operations based on how many characters need to be moved
 * 
 * Time Complexity: O(n log n) per test case due to sorting and linear operations
 * Space Complexity: O(n) for storing indices and temporary strings
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
int n, si;
string a, b;
vector<int> sz;

void solve() {
  cin >> n >> a;
  b = a;
  sort(b.begin(), b.end()); // Sort to get target string
  char c = 'a';
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] >= c) { // If current character is greater than or equal to the last added
      sz.push_back(i); // Store index of this character
      c = a[i]; // Update the maximum character seen so far
    }
  }
  si = sz.size(); // Size of the largest subsequence
  // Reverse the indices to simulate cyclic shifts correctly
  for (int i = 0; i < si / 2; i++) {
    swap(a[sz[i]], a[sz[si - 1 - i]]);
  }
  if (a != b) { // If after transformation it doesn't match sorted string
    cout << -1 << "\n";
  } else {
    int ans = si; // Initial count of operations
    for (auto x : sz) {
      if (a[x] == a[sz[0]]) { // If character at index x matches first in sequence
        ans--; // Reduce count (no additional operation needed)
      }
    }
    cout << ans << "\n";
  }
  sz.clear(); // Clear vector for next test case
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int w;
  cin >> w;
  while (w--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
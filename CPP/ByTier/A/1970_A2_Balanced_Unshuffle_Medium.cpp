// Problem: CF 1970 A2 - Balanced Unshuffle (Medium)
// https://codeforces.com/contest/1970/problem/A2

/*
 * Problem: Balanced Unshuffle (Medium)
 *
 * Algorithm/Technique: Recursive Tree Construction
 *
 * Time Complexity: O(n^2) where n is the length of the input string.
 * Space Complexity: O(n^2) for storing the tree structure in the vector of vectors.
 *
 * The algorithm reconstructs the original balanced parentheses sequence from its
 * balanced shuffle by building a tree structure representing the nesting of
 * parentheses. It uses a recursive DFS approach to traverse the tree and output
 * the parentheses in the correct order.
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  string s;
  cin >> s;
  int n = s.size(), c0 = 0, c1 = 0;
  vector<vector<int>> e(n);  // e[x] stores children of node x in reverse order
  for (int i = 0; i < n; i++)
    if (s[i] == '(')
      e[c0].push_back(++c1);  // incrementing c1 and assigning to current level
    else
      c0++;  // moving to next level when closing bracket is encountered
  auto dfs = [&](auto self, int x) -> void {
    reverse(begin(e[x]), end(e[x]));  // reverse to restore correct order
    for (int y : e[x])  // for each child
      cout << '(', self(self, y), cout << ')';  // recursively process subtree
  };
  dfs(dfs, 0);  // start from root (level 0)
  return 0;
}


// https://github.com/VaHiX/CodeForces/
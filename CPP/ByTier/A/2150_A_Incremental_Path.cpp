// Problem: CF 2150 A - Incremental Path
// https://codeforces.com/contest/2150/problem/A

/*
 * Problem: Rymdkraft - Rymdsylt
 * Algorithms/Techniques: Simulation with Set for Tracking Black Cells
 *
 * Time Complexity: O(n * m * log(m)) where n is the length of the command string and m is the number of initial black cells.
 * Space Complexity: O(m) for storing the set of black cells.
 *
 * Description:
 * We simulate a process on an infinite strip of cells where initially some cells are black.
 * A person starts at cell 1 and executes commands from a given string:
 *   - 'A': move to the next cell (x+1)
 *   - 'B': move to the next white cell (minimum y > x such that y is white)
 * After executing the first i commands in sequence, the final cell visited is colored black,
 * unless it was already black. The final set of black cells is outputted.
 */

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
#define int int64_t
#define all(x) x.begin(), x.end()
int M = 1e9 + 7;

void solve() {
  int n, m;
  string s;
  cin >> n >> m >> s;
  vector<int> v(m);
  for (auto &i : v)
    cin >> i;
  set<int> st(all(v)); // Store initial black cells in a set for fast lookup and insertion
  int x = 1; // Position tracker, starts at cell 1
  for (int i = 0; i < n; i++) {
    if (i && s[i - 1] == 'B') {
      // If previous command was B, skip any existing black cells in the path
      while (st.count(x))
        x++;
    }
    x++; // Move to next cell or jump ahead based on command logic
    if (s[i] == 'B') {
      // If current command is B, find next white cell
      while (st.count(x))
        x++;
    }
    st.insert(x); // Mark current position as black
  }
  cout << st.size() << '\n';
  for (auto &i : st)
    cout << i << ' ';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve(), cout << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/
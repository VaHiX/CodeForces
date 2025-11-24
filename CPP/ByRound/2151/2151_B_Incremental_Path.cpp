// Problem: CF 2151 B - Incremental Path
// https://codeforces.com/contest/2151/problem/B

/*
B. Incremental Path

Algorithms/Techniques: Simulation with Set for tracking black cells
Time Complexity: O(n * log n + m * log m) per test case
Space Complexity: O(n + m)

This problem simulates a process where several people execute command sequences
on a linear strip of cells, coloring the last visited cell black. The commands
are 'A' (move to next cell) and 'B' (jump to next white cell). We track all black
cells using a set for efficient lookup and insertion.
*/

#include <iostream>
#include <set>

using namespace std;
const int N = 1e5 + 5;
int T, n, m;
char s[N];

void Solve() {
  set<int> st; // Set to store positions of black cells
  cin >> n >> m >> s + 1; // Read n, m and the command string (1-indexed)
  
  // Read initial black cell positions
  for (int i = 1, x; i <= m; i++)
    cin >> x, st.insert(x);
    
  int now = 1; // Current position, starts from 1
  
  // Process each of the n commands
  for (int i = 1; i <= n; i++) {
    ++now; // Move to next cell (equivalent to 'A' command)
    
    // If current cell is 'B', find next white cell
    if (s[i] == 'B') {
      while (st.count(now)) // Skip black cells
        ++now;
    }
    
    st.insert(now); // Color the final cell black
    
    // If current command is 'B', we may need to skip again after coloring
    if (s[i] == 'B') {
      while (st.count(now)) // Again skip black cells
        ++now;
    }
  }
  
  // Output results
  cout << st.size() << "\n";
  while (st.size())
    cout << *st.begin() << " ", st.erase(st.begin()); // Print all black cell positions in order
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/
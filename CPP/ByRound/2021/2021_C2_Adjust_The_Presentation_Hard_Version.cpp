// Problem: CF 2021 C2 - Adjust The Presentation (Hard Version)
// https://codeforces.com/contest/2021/problem/C2

/*
C2. Adjust The Presentation (Hard Version)
Algorithm: 
- Uses a set-based approach to maintain order of members presenting slides
- For each slide, we track which member presents it and maintain their positions in sets
- Efficiently updates the set when an element is moved or changed
- Checks if presentation is still "good" after each update

Time Complexity: O((n + m + q) * log(n)) per test case due to set operations (log n for insertion/erase)
Space Complexity: O(n * m) for storing sets and other auxiliary arrays

*/
#include <iostream>
#include <set>
using namespace std;
const int N = 2e5 + 10;
int cnt, a[N], p[N], b[N], n, m, q;
set<int> s[N]; // Each set holds the positions of elements in the b array

void cal(int x, int f) {
  // Update count when changes happen in adjacent sets
  for (int i = x; i <= x + 1; i++) {
    if (i == 1)
      continue;
    int x_val = 1e9, y = 1e9;
    if (s[i].size())
      y = *s[i].begin();
    if (s[i - 1].size())
      x_val = *s[i - 1].begin();
    cnt += (x_val <= y) * f; // Increase or decrease count based on condition
  }
}

void solve() {
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++)
    cin >> a[i], p[a[i]] = i; // Map value to position in initial order
  for (int i = 1; i <= m; i++) {
    cin >> b[i], b[i] = p[b[i]]; // Convert member to its initial position
    s[b[i]].insert(i); // Insert slide number into corresponding set
  }
  cnt = 0;
  // Initialize count of valid transitions
  for (int i = 2; i <= n; i++) {
    int x = 1e9, y = 1e9;
    if (s[i].size())
      y = *s[i].begin();
    if (s[i - 1].size())
      x = *s[i - 1].begin();
    cnt += (x <= y); // Count pairs where preceding element's first occurrence <= current
  }
  if (cnt == n - 1)
    cout << "YA" << '\n';
  else
    cout << "TIDAK" << '\n';

  for (int i = 1; i <= q; i++) {
    int x, y;
    cin >> x >> y;
    y = p[y]; // Convert new member to its initial position
    cal(b[x], -1); // Remove previous contribution from the old set
    s[b[x]].erase(x); // Remove element at position x in original set
    cal(b[x], 1); // Re-evaluate contribution after modification
    b[x] = y; // Update array b at position x
    cal(y, -1); // Remove contribution of new set
    s[y].insert(x); // Insert into updated set
    cal(y, 1); // Add new contribution
    if (cnt == n - 1)
      cout << "YA" << '\n';
    else
      cout << "TIDAK" << '\n';
  }
  for (int i = 1; i <= n; i++)
    s[i].clear(); // Clear sets for next test case
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
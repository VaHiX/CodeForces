// Problem: CF 1765 L - Project Manager
// https://codeforces.com/contest/1765/problem/L

/*
Purpose: This code simulates project completion scheduling for employees at a company.
         Each employee works on specific days of the week, and some days are holidays.
         Projects consist of parts assigned to specific employees.
         Employees work on projects in descending priority order (lower index = higher priority).
         The simulation tracks which day each employee becomes available again after completing tasks,
         considering only working days (excluding holidays).

Algorithms/Techniques:
  - Preprocessing of working days using bitflags and maps
  - Range query optimization with jump pointers for fast lookups
  - Union-find like structure for tracking next valid day
  - Mapping weekdays to indices (0-6) for efficient processing

Time Complexity: O(n * 7 + m + k * P + max_day * 7) where P is total parts across all projects and max_day is up to 1e9
Space Complexity: O(n * 7 + m + max_day * 7)

The solution uses a mapping of each day to the next working day, preprocessed using jump pointers for fast query resolution. It uses dynamic programming concepts with memoization and union-find for path compression.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef long double ld;
#define all(x) x.begin(), x.end()
const int mod = 998244353;
const int iinf = (int)1e9 + 10;
const ll linf = (ll)1e18 + 10;
const int multitest = 0;
const int maxn = 2e5 + 10, N = 3e6;
int h[N]; // Marks holidays
map<int, int> m[maxn]; // Union-find style structure to compress paths for day lookups
int ok[7][maxn]; // ok[j][i] indicates that employee i works on weekday j (0=Monday to 6=Sunday)
vector<int> w[7]; // w[j] stores all days in the week cycle where weekday j occurs
int to[7][N]; // to[j][d] maps day d to the first valid day of weekday j >= d
vector<string> kek{"Monday", "Tuesday",  "Wednesday", "Thursday",
                   "Friday", "Saturday", "Sunday"};
int get(int i, int d) {
  if (!m[i][d])
    return d;
  return m[i][d] = get(i, m[i][d]);
}
int nxt(int i, int d) {
  int res = N;
  for (int j = 0; j < 7; j++) {
    // Iterate through all weekdays and select the earliest next valid working day
    if (ok[j][i]) {
      res = min(res, to[j][d]);
    }
  }
  return res;
}
void ch(int i, int d) {
  // Updates state after completing a task (finds the next available day for employee)
  int dd = nxt(i, d + 1);
  m[i][d] = get(i, dd);
}
int do_query(int i, int d) {
  // Finds current availability of employee i starting from day d
  d = nxt(i, d);
  int res = get(i, d);
  ch(i, res); // Update state for future queries
  return res;
}
void solve() {
  int n, m, k;
  cin >> n >> m >> k; // Read employees count, holidays count, projects count
  for (int i = 0; i < n; i++) {
    int c;
    cin >> c; // Number of days employee works
    while (c--) {
      string s;
      cin >> s; // Read working day name
      for (int j = 0; j < 7; j++) {
        if (kek[j] == s) // Map day name to index
          ok[j][i] = 1;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    int a;
    cin >> a;
    a--;
    if (a < N)
      h[a] = 1; // Mark holiday days
  }
  for (int i = 0; i < N; i++) {
    if (!h[i]) // For non-holiday days, store them grouped by weekday
      w[i % 7].push_back(i);
  }
  for (int j = 0; j < 7; j++) {
    int lst = 0;
    for (int x : w[j]) { // Precompute the "to" array mapping each day to next weekday j
      while (lst <= x) {
        to[j][lst] = x;
        lst++;
      }
    }
  }
  for (int i = 0; i < k; i++) {
    int c;
    cin >> c; // Number of parts in current project
    int st = 0;
    while (c--) {
      int j;
      cin >> j;
      j--; // Convert to 0-based indexing
      st = do_query(j, st) + 1; // Find next available day for employee and advance time
    }
    cout << st << " "; // Output completion day of project
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  if (multitest)
    cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
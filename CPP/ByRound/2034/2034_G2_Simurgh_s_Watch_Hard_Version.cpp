// Problem: CF 2034 G2 - Simurgh's Watch (Hard Version)
// https://codeforces.com/contest/2034/problem/G2

/*
 * Algorithm/Technique:
 * This solution tackles the problem of assigning minimum number of colors to intervals such that
 * for each integer time point covered by at least one interval, there exists a color worn by exactly one interval.
 * 
 * Approach:
 * 1. Compress all unique time points (including boundaries) to reduce the coordinate space.
 * 2. Process intervals in events (start and end) to determine minimum colors needed.
 * 3. Use greedy coloring strategies with:
 *    - Check if 1 color suffices (no overlap in any point)
 *    - Check if 2 colors suffice with a greedy approach
 *    - Else assign 3 colors using a special strategy.
 *
 * Time Complexity: O(n log n) due to sorting and processing of events.
 * Space Complexity: O(n) for storing intervals and auxiliary arrays.
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
const int N = 2e5 + 5;
vector<int> st[N << 2], en[N << 2]; // st[i] = list of intervals starting at i, en[i] = list ending at i
int t, n, k, l[N], r[N], dp[N], col[N], prv[N];

void compress_numbers() {
  vector<int> help;
  // Collect all relevant points for compression including boundaries
  for (int i = 0; i < n; i++) {
    help.push_back(l[i] - 1);
    help.push_back(l[i]);
    help.push_back(r[i]);
    help.push_back(r[i] + 1);
  }
  sort(help.begin(), help.end());
  help.resize(k = unique(help.begin(), help.end()) - help.begin()); // Remove duplicates
  for (int i = 0; i < n; i++) {
    l[i] = lower_bound(help.begin(), help.end(), l[i]) - help.begin(); // Map original to compressed coordinates
    r[i] = lower_bound(help.begin(), help.end(), r[i]) - help.begin();
  }
}

void save_checkpoints() {
  // Populate start and end events
  for (int i = 0; i < n; i++) {
    st[l[i]].push_back(i);
    en[r[i]].push_back(i);
  }
}

bool check_one() {
  // Check if 1 color suffices (i.e., no overlapping intervals)
  for (int i = 0, open = 0; i < k; i++) {
    open += st[i].size();
    if (open > 1)
      return false;
    open -= en[i].size();
  }
  return true;
}

void color_with_two() {
  // Color with exactly 2 colors using a greedy backward approach
  for (int i = k - 1, cur = -1; ~i; i--) {
    if (en[i].empty())
      continue;
    // Greedily move backward until we find valid coloring for current segment
    while (!~cur || i < dp[cur])
      if (~cur && ~prv[cur]) {
        col[prv[cur]] = col[cur];
        if (r[prv[cur]] >= l[cur])
          col[prv[cur]] ^= 1;
        cur = prv[cur];
      } else
        for (int p : en[i])
          if (~dp[p] && (!~cur || dp[p] < dp[cur]))
            cur = p;
    // Assign opposite color to non-cur segments
    for (int p : en[i])
      if (p ^ cur)
        col[p] = col[cur] ^ 1;
  }
}

bool check_two() {
  // Try to color with 2 colors using dynamic approach
  set<int> goods, bads;
  fill(dp, dp + n, -1);
  fill(prv, prv + n, -1);
  for (int i = 0; i < k; i++) {
    int prev = -1;
    if (i)
      for (int p : en[i - 1]) {
        bads.erase(p), goods.erase(p);
        if (~dp[p] && (!~prev || dp[p] < dp[prev]))
          prev = p;
      }
    int open = goods.size() + bads.size();
    if (open == 1 || (open == 2 && !goods.empty())) {
      for (int p : bads) {
        if (open == 1)
          prv[p] = prev;
        else
          prv[p] = *goods.begin();
        goods.insert(p);
        dp[p] = i;
      }
      bads.clear();
    }
    if (open == 1)
      prev = *goods.begin();
    for (int p : st[i])
      if (!open || open == 1 || ~prev) {
        goods.insert(p);
        prv[p] = prev;
        dp[p] = i;
      } else
        bads.insert(p);
    open += st[i].size();
    if (open && goods.empty())
      return false;
  }
  color_with_two();
  return true;
}

void color_with_three() {
  // Assign 3 colors for cases beyond 2-color solution
  int cur = -1, nxt = -1;
  for (int i = 0; i < k; i++) {
    if (st[i].empty())
      continue;
    if (~cur && i > r[cur] && nxt ^ cur) {
      col[nxt] = col[cur] ^ 3;
      cur = nxt;
    }
    if (!~cur || i > r[cur]) {
      for (int p : st[i])
        if (!~cur || r[p] > r[cur])
          cur = p;
      col[nxt = cur] = 1;
    }
    for (int p : st[i])
      if (r[p] > r[nxt])
        nxt = p;
  }
  if (cur ^ nxt)
    col[nxt] = col[cur] ^ 3;
}

void read_input() {
  // Read input for current test case
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> l[i] >> r[i];
}

void solve() {
  compress_numbers();
  save_checkpoints();
  if (check_one())
    return;
  if (check_two())
    return;
  color_with_three();
}

void write_output() {
  // Output the result
  cout << *max_element(col, col + n) + 1 << endl;
  for (int i = 0; i < n; i++)
    cout << col[i] + 1 << "\n "[i < n - 1];
}

void reset_variables() {
  // Reset variables for next test case
  fill(col, col + n, 0);
  for (int i = 0; i < k; i++) {
    st[i].clear();
    en[i].clear();
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; reset_variables())
    read_input(), solve(), write_output();
  return 0;
}


// https://github.com/VaHiX/CodeForces/
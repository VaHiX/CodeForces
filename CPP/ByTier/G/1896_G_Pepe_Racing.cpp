// Problem: CF 1896 G - Pepe Racing
// https://codeforces.com/contest/1896/problem/G

/*
Algorithm: Adaptive Tournament with Grouping and Elimination
Time Complexity: O(n^3)
Space Complexity: O(n^2)

This solution uses an adaptive approach to determine the relative speeds of n^2 pepes.
The key idea is to:
1. First, run n races of n pepes each to find the fastest in each group
2. Then, iteratively eliminate the slowest pepe from the remaining candidates
3. Track group membership and eliminate candidates through race queries
4. Finally, determine the complete ordering of pepe speeds

The algorithm works by:
- Initially grouping pepes into n groups of n each
- Using races to progressively eliminate the slowest pepe from the candidates
- Managing group information to avoid redundant queries
- Terminating when all pepes are ordered
*/

#include <stdio.h>
#include <iostream>
#include <set>

using namespace std;
const int N = 4e2;
int n;
int rk[N];
bool vis[N];
set<int> winner, group[N];
void solve() {
  cin >> n;
  winner.clear();
  for (int i = 1; i <= n; ++i)
    group[i].clear();
  int now = 1;
  for (int i = 1; i <= n * n; ++i)
    vis[i] = false;
  int t = 0;
  // Step 1: Run n races to find initial winners from each group
  for (int l = 1; l <= n * n; l += n) {
    cout << "? ";
    fflush(stdout);
    for (int i = 1; i <= n; ++i) {
      cout << l + i - 1 << " ";
      fflush(stdout);
    }
    cout << endl;
    fflush(stdout);
    int x;
    cin >> x;
    winner.insert(x);
    vis[x] = true;
    ++t;
    for (int i = 1; i <= n; ++i) {
      group[t].insert(l + i - 1);
    }
  }
  // Step 2: Eliminate and process remaining candidates
  t = n * n - 2 * n + 1;
  while (t--) {
    cout << "? ";
    fflush(stdout);
    for (auto i = winner.begin(); i != winner.end(); ++i) {
      cout << *i << " ";
      fflush(stdout);
    }
    cout << endl;
    fflush(stdout);
    cin >> rk[now];
    int x = rk[now];
    winner.erase(x);
    now++;
    int col = 0;
    // Find which group contains the eliminated pepe
    for (int i = 1; i <= n; ++i) {
      if (group[i].find(x) != group[i].end()) {
        col = i;
        group[i].erase(x);
        break;
      }
    }
    // Fill up the group to n pepe size
    int need = n - group[col].size();
    int tmp = 1;
    while (need--) {
      while (vis[tmp] || group[col].find(tmp) != group[col].end())
        tmp++;
      for (int i = 1; i <= n; ++i) {
        if (group[i].find(tmp) != group[i].end()) {
          group[i].erase(tmp);
          break;
        }
      }
      group[col].insert(tmp);
    }
    // Race the updated group to get the fastest
    cout << "? ";
    fflush(stdout);
    for (auto i = group[col].begin(); i != group[col].end(); ++i) {
      cout << *i << " ";
      fflush(stdout);
    }
    cout << endl;
    fflush(stdout);
    cin >> x;
    vis[x] = true;
    winner.insert(x);
  }
  // Step 3: Complete ordering of the final slowest pepe
  t = n - 1;
  while (t--) {
    cout << "? ";
    fflush(stdout);
    int need = n - winner.size();
    int tmp = 1;
    while (need--) {
      while (vis[tmp] || winner.find(tmp) != winner.end())
        tmp++;
      winner.insert(tmp);
    }
    for (auto i = winner.begin(); i != winner.end(); ++i) {
      cout << *i << " ";
      fflush(stdout);
    }
    cout << endl;
    fflush(stdout);
    cin >> rk[now];
    winner.erase(rk[now]);
    now++;
  }
  // Final step: Insert the last remaining pepe
  for (int i = 1; i <= n * n; ++i) {
    if (!vis[i])
      continue;
    if (winner.find(i) != winner.end()) {
      rk[now] = i;
      break;
    }
  }
  cout << "! ";
  fflush(stdout);
  for (int i = 1; i <= now; ++i) {
    cout << rk[i] << " ";
    fflush(stdout);
  }
  cout << endl;
  fflush(stdout);
}
int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/
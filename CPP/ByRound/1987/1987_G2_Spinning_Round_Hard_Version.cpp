// Problem: CF 1987 G2 - Spinning Round (Hard Version)
// https://codeforces.com/contest/1987/problem/G2

/*
Algorithm: 
This solution uses a combination of stack-based preprocessing to compute left and right greater elements for each index, 
followed by a tree DP approach to compute the maximum diameter. The key insight is to use a binary tree structure to model 
the connectivity constraints and perform DFS to compute optimal assignment of '?' characters.

Time Complexity: O(n) - Each element is pushed and popped from the stack at most once, and the DFS traversal is linear.
Space Complexity: O(n) - Stacks, arrays, and recursive call stack are all linear in size.

Approach:
1. Preprocess using monotonic stack to find left and right greater elements for all indices.
2. Try both possible assignments of '?' characters to check if a connected graph is possible.
3. Use tree DP to compute maximum diameter for valid edge assignments.

Techniques:
- Monotonic stack for efficient computation of nearest greater elements
- Tree DP with memoization to compute diameters
- Backtracking with DFS to try valid edge assignment combinations
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int maxn = 1e6 + 5;
int ans, flag;
int a[maxn], sta[maxn];
char s[maxn];
int f[maxn][3];
int ls[maxn], rs[maxn];

// DFS to compute the maximum diameter using tree DP
void dfs(int x) {
  f[x][0] = f[x][1] = f[x][2] = 0;
  if (ls[x])
    dfs(ls[x]);
  if (rs[x])
    dfs(rs[x]);
  // Initialize f[x][0] and f[x][1] based on child nodes
  f[x][0] = f[ls[x]][0], f[x][1] = f[rs[x]][1];
  // Compute f[x][2] as the sum of paths from left and right children
  f[x][2] = f[ls[x]][0] + f[rs[x]][1];
  // Update maximum diameter found so far
  ans = max(ans, f[ls[x]][1] + f[rs[x]][0]);
  // If not root and not forced to R, update left assignment
  if (x != sta[1] && s[x] != 'R') {
    f[x][0] = max(f[x][0], max(f[ls[x]][1], f[rs[x]][0]) + 1);
    f[x][2] = max(f[x][2], max(f[rs[x]][2], f[ls[x]][1] + f[rs[x]][1]) + 1);
    ans = max(ans, max(f[ls[x]][0] + f[rs[x]][0], f[ls[x]][2]) + 1);
  }
  // If not root and not forced to L, update right assignment
  if (x != sta[1] && s[x] != 'L') {
    f[x][1] = max(f[x][1], max(f[ls[x]][1], f[rs[x]][0]) + 1);
    f[x][2] = max(f[x][2], max(f[ls[x]][2], f[ls[x]][0] + f[rs[x]][0]) + 1);
    ans = max(ans, max(f[ls[x]][1] + f[rs[x]][1], f[rs[x]][2]) + 1);
  }
  return;
}

// DFS to try assignment of '?' to 'L'
void dfs0(int x) {
  if (ls[x])
    dfs0(ls[x]);
  // Mark if we would force a node to be 'L'
  if (x != sta[1] && s[x] == 'L')
    flag = 1;
  s[x] = 'R';
  return;
}

// DFS to try assignment of '?' to 'R'
void dfs1(int x) {
  if (rs[x])
    dfs1(rs[x]);
  // Mark if we would force a node to be 'R'
  if (x != sta[1] && s[x] == 'R')
    flag = 1;
  s[x] = 'L';
  return;
}

// Solve function for each test case
void solve() {
  ans = flag = 0;
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i], ls[i] = rs[i] = 0;
  int tot = 0;
  // Monotonic stack to compute left and right nearest greater elements
  for (int i = 1; i <= n; i++) {
    while (tot && a[sta[tot]] < a[i]) {
      ls[i] = sta[tot];
      --tot;
    }
    rs[sta[tot]] = i;
    sta[++tot] = i;
  }
  cin >> s + 1;
  // Try both assignments for '?'
  dfs0(sta[1]);
  dfs1(sta[1]);
  // If impossible to form a connected graph
  if (flag) {
    cout << "-1\n";
    return;
  }
  dfs(sta[1]);
  cout << ans << '\n';
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/
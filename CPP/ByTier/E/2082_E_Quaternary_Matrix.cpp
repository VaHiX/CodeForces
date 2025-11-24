// Problem: CF 2082 E - Quaternary Matrix
// https://codeforces.com/contest/2082/problem/E

// Problem: E. Quaternary Matrix
// Task: Make a given quaternary matrix (with elements 0, 1, 2, 3) "good" by changing minimum elements.
// A matrix is good if XOR of all elements in each row and column equals 0.
// Algorithms/Techniques: Greedy with bit manipulation, constructive algorithm.
//
// Time Complexity: O(n * m) per test case
// Space Complexity: O(n * m) for storing the matrix and auxiliary arrays

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#define Spc putchar(' ')
#define End putchar('\n')
#define For(i, il, ir) for (int i = (il); i <= (ir); ++i)
#define Fr(i, il, ir) for (int i = (il); i < (ir); ++i)
#define Forr(i, ir, il) for (int i = (ir); i >= (il); --i)
#define ForE(u) for (int i = head[u]; ~i; i = e[i].nxt)
#define fi first
#define se second
#define mk make_pair
#define pb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

namespace _TvT_ {
template <typename T> inline void rd(T &x) {
  bool f = 0;
  x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  if (f)
    x = -x;
}
template <typename T, typename... Args> void rd(T &first, Args &...args) {
  rd(first), rd(args...);
}
int write_num[50];
template <typename T> inline void write(T x) {
  int len = 0;
  if (x < 0)
    putchar('-'), x = -x;
  do
    write_num[len++] = x % 10;
  while (x /= 10);
  while (len--)
    putchar(write_num[len] + '0');
}
template <typename T, typename... Args> void write(T first, Args... args) {
  write(first), Spc, write(args...);
}
} // namespace _TvT_
using namespace _TvT_;

const int maxn = 1005;
int n, m;
int a[1005][1005]; // Input matrix
int r[1005], c[1005]; // XOR of each row/column
vector<int> ver[4], vec[4]; // Rows/columns with XOR values 1,2,3
vector<pii> rr, cc; // remaining rows/columns (as pairs of index and value)

void upd(int i, int j, int v) {
  a[i][j] ^= v; // Toggle value in matrix
}
void solve() {
  rd(n, m);
  For(i, 1, n) For(j, 1, m) {
    char ch = getchar();
    while (ch < '0' || ch > '3')
      ch = getchar();
    a[i][j] = ch - '0';
    r[i] ^= a[i][j], c[j] ^= a[i][j]; // Update row/column XORs
  }
  
  For(i, 1, n) ver[r[i]].pb(i);  // Store indices of rows with specific XOR
  For(i, 1, m) vec[c[i]].pb(i);  // Store indices of columns with specific XOR

  int ans = 0;
  For(i, 1, 3) ans += (int)ver[i].size() + (int)vec[i].size(); // Add count of mismatches
  
  // Pair compatible rows/columns to fix them in one step
  For(i, 1, 3) while (!ver[i].empty() && !vec[i].empty()) {
    ans--;
    upd(ver[i].back(), vec[i].back(), i), ver[i].pop_back(), vec[i].pop_back();
  }

  // Try to fix remaining mismatches using combinations with XOR rules
  For(x, 1, 3) if (!ver[x].empty()) For(y, x + 1, 3) if (!ver[y].empty()) {
    int z = x ^ y;  // z is the third number needed for XOR to be zero
    if (vec[z].empty())
      continue;
    while (!ver[x].empty() && !ver[y].empty() && !vec[z].empty()) {
      ans--;
      upd(ver[x].back(), vec[z].back(), x);
      upd(ver[y].back(), vec[z].back(), y);
      ver[x].pop_back(), ver[y].pop_back(), vec[z].pop_back();
    }
  }

  For(x, 1, 3) if (!vec[x].empty()) For(y, x + 1, 3) if (!vec[y].empty()) {
    int z = x ^ y;
    if (ver[z].empty())
      continue;
    while (!vec[x].empty() && !vec[y].empty() && !ver[z].empty()) {
      ans--;
      upd(ver[z].back(), vec[x].back(), x);
      upd(ver[z].back(), vec[y].back(), y);
      ver[z].pop_back(), vec[x].pop_back(), vec[y].pop_back();
    }
  }

  // Handle pairs that require more complex fixes
  For(x, 1, 3) if ((int)ver[x].size() > 1)
      For(y, 1, 3) if ((int)vec[y].size() > 1) while ((int)ver[x].size() > 1 &&
                                                      (int)vec[y].size() > 1) {
    ans--;
    int r1 = ver[x].back(), c1 = vec[y].back();
    ver[x].pop_back(), vec[y].pop_back();
    int r2 = ver[x].back(), c2 = vec[y].back();
    ver[x].pop_back(), vec[y].pop_back();
    upd(r1, c1, x);
    upd(r2, c1, x ^ y); // Correct via XOR
    upd(r2, c2, y);
  }

  For(x, 1, 3) for (int i : ver[x]) rr.pb(mk(i, x)); // Collect unmatched rows
  For(x, 1, 3) for (int i : vec[x]) cc.pb(mk(i, x)); // Collect unmatched columns

  if (!rr.empty() || !cc.empty()) {
    for (int i = 0; i < cc.size(); i++)
      upd(1, cc[i].fi, cc[i].se);   // Fix via fixed row
    for (int i = 0; i < rr.size(); i++)
      upd(rr[i].fi, 1, rr[i].se);   // Fix via fixed column
  }

  write(ans), End;
  For(i, 1, n) {
    For(j, 1, m) write(a[i][j]);
    End;
  }
}
void clear() {
  For(i, 1, n) r[i] = 0;
  For(i, 1, m) c[i] = 0;
  For(i, 0, 3) ver[i].clear(), vec[i].clear();
  rr.clear(), cc.clear();
}

signed main() {
  int T;
  rd(T);
  while (T--)
    solve(), clear();
  return 0;
}


// https://github.com/VaHiX/codeForces/
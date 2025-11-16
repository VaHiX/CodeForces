// Problem: CF 1801 C - Music Festival
// https://codeforces.com/contest/1801/problem/C

/*
Algorithm: Greedy + Fenwick Tree + Dynamic Programming
Approach:
- For each album, we precompute the maximum coolness value in that album.
- We sort albums by their maximum coolness values in ascending order.
- For each album in this sorted order, we process its tracks to find the maximum number of new maximums (impressions).
- We use a Fenwick Tree (Binary Indexed Tree) to keep track of the maximum impression count for a given maximum coolness.
- For each album, we:
  - Find all the new maximums in the album's tracks in order.
  - For each such maximum, we query the Fenwick Tree for the maximum impression that can be achieved with any coolness value less than the current maximum.
  - Update the Fenwick Tree with the computed result.

Time Complexity: O(n * k * log(max_k)) where n is number of albums and k is average number of tracks.
Space Complexity: O(n * k + max_k) for storing albums and Fenwick Tree.

*/
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define formn(i, m, n) for (int i = int(m); i < int(n); i++)
#define X first
#define Y second
const int maxn = 2e5 + 10;
const int base = 31337;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const int logo = 20;
const int off = 1 << logo;
const int treesiz = off << 1;
namespace IO {
#define il inline
const int iL = 1 << 16;
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define getchar()                                                              \
  (iS == iT) ? (iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin),                  \
                (iS == iT) ? EOF : *iS++)                                      \
             : *iS++
template <class T> il void read(T &x) {
  x = 0;
  char c = getchar();
  bool flg = false;
  while (!isdigit(c)) {
    flg |= c == '-';
    c = getchar();
  }
  while (isdigit(c)) {
    x = (x << 1) + (x << 3) + (c & 15);
    c = getchar();
  }
  if (flg)
    x = -x;
}
char Out[iL], *iter = Out;
#define Flush()                                                                \
  fwrite(Out, 1, iter - Out, stdout);                                          \
  iter = Out
template <class T> il void write(T x, char LastChar = '\n') {
  int c[35], len = 0;
  if (x < 0) {
    *iter++ = '-';
    x = -x;
  }
  do {
    c[++len] = x % 10;
    x /= 10;
  } while (x);
  while (len)
    *iter++ = c[len--] + '0';
  *iter++ = LastChar;
  Flush();
}
} // namespace IO
using namespace IO;
using namespace std;
typedef long long ll;
vector<int> arr(200010, 0);
void sol() {
  int i, j, n;
  read(n);
  vector<vector<int>> a(n);
  vector<int> mx(n, 0), idx(n, 0);
  for (i = 0; i < n; i++) {
    int k;
    read(k);
    for (j = 0; j < k; j++) {
      int x;
      read(x);
      mx[i] = max(mx[i], x);
      a[i].push_back(x);
    }
    idx[i] = i;
  }
  sort(idx.begin(), idx.end(), [&](int l, int r) { return mx[l] < mx[r]; });
  auto upd = [&](int x, int v) {
    for (; x < 200010; x += x & -x)
      arr[x] = max(arr[x], v);
  };
  auto clr = [&](int x) {
    for (; x < 200010 && arr[x] > 0; x += x & -x)
      arr[x] = 0;
  };
  auto qur = [&](int x) -> int {
    int ret = 0;
    for (; x > 0; x -= x & -x)
      ret = max(ret, arr[x]);
    return ret;
  };
  int ans = 0;
  for (i = 0; i < n; i++) {
    int t = idx[i];
    vector<int> &o = a[t];
    int mxt = mx[t];
    int curm = 0;
    int cc = 0;
    vector<int> tm;
    for (j = 0; j < o.size(); j++) {
      if (o[j] > curm) {
        tm.push_back(o[j]);
        curm = o[j];
        cc++;
      }
    }
    int mx_ans = 0;
    for (j = tm.size() - 1; j >= 0; j--) {
      int tmp_max = qur(tm[j] - 1) + tm.size() - j;
      mx_ans = max(mx_ans, tmp_max);
    }
    ans = max(ans, mx_ans);
    upd(mxt, mx_ans);
  }
  for (i = 0; i < n; i++)
    clr(mx[i]);
  write(ans, '\n');
}
int main() {
  int t = 1;
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  read(t);
  while (t--)
    sol();
  return 0;
}


// https://github.com/VaHiX/CodeForces/
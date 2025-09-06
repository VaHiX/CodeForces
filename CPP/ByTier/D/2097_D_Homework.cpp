/*
 * Problem URL : https://codeforces.com/problemset/problem/2097/D
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int maxn = 1e6 + 5;

struct BITSET {
  vector<ull> vec;
  void clear() { vec.clear(); }
  bool any() {
    for (int i = 0; i < vec.size(); i++)
      if (vec[i])
        return true;
    return false;
  }
  int _Find_first() {
    for (int i = 0; i < vec.size(); i++)
      if (vec[i])
        return __builtin_ctzll(vec[i]) | (i << 6);
    return -1;
  }
} bt[2][1005], tmp;

void XOR(BITSET &A, BITSET &B) {
  int x = max(A.vec.size(), B.vec.size());
  A.vec.resize(x);
  for (int i = 0; i < B.vec.size(); i++)
    A.vec[i] ^= B.vec[i];
}

char s[2][maxn];
int pos[2][maxn], tot[2];

void ins(int op) {
  while (tmp.any()) {
    int p = tmp._Find_first();
    if (!pos[op][p]) {
      pos[op][p] = ++tot[op], bt[op][tot[op]] = tmp;
      break;
    } else
      XOR(tmp, bt[op][pos[op][p]]);
  }
}

bool tryins(int op) {
  while (tmp.any()) {
    int p = tmp._Find_first();
    if (!pos[op][p])
      return true;
    else
      XOR(tmp, bt[op][pos[op][p]]);
  }
  return false;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void init(int op, int l, int r) {
  tmp.vec.resize(((r - l) >> 6) + 1);
  for (int i = l; i < r; i += 64) {
    ull S = 0;
    for (int j = i; j < r && j < i + 64; j++)
      S |= ((ull)(s[op][j] == '1') << (j - i));
    tmp.vec[(i - l) >> 6] = S;
  }
}

void work() {
  int n;
  cin >> n >> s[0] >> s[1];
  tot[0] = tot[1] = 0;
  int x = n, y = 1;
  while (!(x & 1))
    x >>= 1, y <<= 1;
  for (int op = 0; op < 2; op++)
    for (int i = 0; i < n; i += x)
      init(op, i, i + x), ins(op);

  bool Fl = true;
  if (tot[0] != tot[1])
    Fl = false;
  for (int i = x - 1; ~i && Fl; i--)
    if (pos[0][i]) {
      tmp = bt[0][pos[0][i]];
      if (tryins(1)) {
        Fl = false;
        break;
      }
    }
  for (int i = x - 1; ~i; i--)
    if (pos[0][i])
      bt[0][pos[0][i]].clear(), pos[0][i] = 0;
  for (int i = x - 1; ~i; i--)
    if (pos[1][i])
      bt[1][pos[1][i]].clear(), pos[1][i] = 0;
  cout << (Fl ? "Yes\n" : "No\n");
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);

  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}
/*
 * Problem URL : https://codeforces.com/contest/802/problem/L
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>

#define ll long long

#define ld long double

#define ull unsigned ll

#define db double

#define pint pair<int, int>

#define mk make_pair

#define pb push_back

#define eb emplace_back

#define ins insert

#define fi first

#define se second

#define Rep(x, y, z) for (int x = y; x <= z; x++)

#define Red(x, y, z) for (int x = y; x >= z; x--)

using namespace std;

const int Mod = 1e9 + 7, MAXN = 1e5 + 5;

char buf[1 << 12], *pp1 = buf, *pp2 = buf, nc;
int ny;

inline char gc() {
  return pp1 == pp2 &&
                 (pp2 = (pp1 = buf) + fread(buf, 1, 1 << 12, stdin), pp1 == pp2)
             ? EOF
             : *pp1++;
}

// inline char gc(){return getchar();}

inline int read() {

  int x = 0;
  for (ny = 1; nc = gc(), (nc < 48 || nc > 57) && nc != EOF;)
    if (nc == 45)
      ny = -1;
  if (nc < 0)
    return nc;

  for (x = nc - 48; nc = gc(), 47 < nc && nc < 58 && nc != EOF;
       x = (x << 3) + (x << 1) + (nc ^ 48))
    ;
  return x * ny;
}

int n, sum[MAXN], k[MAXN], b[MAXN];
vector<int> G[MAXN];

inline int Fp(int x, int k) {
  int ans = 1;
  for (; k; k >>= 1, x = 1ll * x * x % Mod)
    if (k & 1)
      ans = 1ll * ans * x % Mod;
  return ans;
}

inline void add(int &x, int y) { x += y, x >= Mod ? x -= Mod : 0; }

inline void sub(int &x, int y) { x -= y, x < 0 ? x += Mod : 0; }

void dfs(int x, int fa) {

  if (G[x].size() == 1) {
    k[x] = 0, b[x] = 0;
    return;
  }

  k[x] = G[x].size(), b[x] = sum[x];

  for (auto y : G[x])
    if (y != fa)
      dfs(y, x), sub(k[x], k[y]), add(b[x], b[y]);

  k[x] = Fp(k[x], Mod - 2), b[x] = 1ll * b[x] * k[x] % Mod;
}

int main() {

  //	freopen("std.in","r",stdin);

  //	freopen("std.out","w",stdout);

  n = read();

  Rep(i, 1, n - 1) {
    int x = read() + 1, y = read() + 1, w = read();
    G[x].pb(y), G[y].pb(x), add(sum[x], w), add(sum[y], w);
  }

  dfs(1, 0), cout << b[1] << '\n';

  return 0;
}

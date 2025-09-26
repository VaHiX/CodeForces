/*
 * Problem URL : https://codeforces.com/contest/1424/problem/N
 * Submit Date : 2025-09-08
 */

/**** Hyperhydrochloric Acid ****\
|                H    H          |
|                 \  /           |
|             H    Cl            |
|              \  /              |
|   H           Cl               |
|    \          |                |
|     Cl        Cl        H      |
|    /  \      /  \      /       |
|   H    Cl--Cl    Cl--Cl    H   |
|       /      \  /      \  /    |
|      H        Cl        Cl     |
|               |           \    |
|               H            H   |
\********************************/
#include <bits/stdc++.h>
using namespace std;
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define loop(i, n) for (int i = 0; i < (n); ++i)
#define cont(i, n) for (int i = 1; i <= (n); ++i)
#define circ(i, a, b) for (int i = (a); i <= (b); ++i)
#define range(i, a, b, c)                                                      \
  for (int i = (a); ((c) > 0 ? i <= (b) : i >= (b)); i += (c))
#define foreach(it, v)                                                         \
  for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define y0 y0O0OO00OO0OO0OO0OOO00OO0OO0O0O000OO0
#define y1 y1II11II11III11I1III11II111IIII1II1I1
#define pub push_back
#define pob pop_back
#define mak make_pair
typedef long long ll;
typedef long double lf;
const int Inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
/* Source code starts here */

int n, k;
int u[1 << 20], v[1 << 20];
bool sel[1 << 14];
vector<pair<int, int>> nei[1 << 14], egs[1 << 14];
bool lgl[1 << 21];
int val[1 << 20], F[1 << 20];

int main() {
  scanf("%d%d", &n, &k);
  cont(i, k) {
    int a, b;
    scanf("%d%d", &a, &b);
    u[i] = a;
    v[i] = b;
    if (a < b)
      swap(a, b); // make a > b
    nei[a].pub(mak(b, i));
    egs[a].pub(mak(b, i));
    egs[b].pub(mak(a, i));
    val[i] = 1;
  }
  cont(i, n) {
    int fix = 0;
    loop(j, SZ(nei[i])) {
      int to = nei[i][j].first, eg = nei[i][j].second;
      if (sel[to]) {
        sel[to] = 0;
        ++val[eg];
      }
    }
    loop(j, SZ(egs[i])) fix += val[egs[i][j].second];
    circ(j, fix - SZ(nei[i]), fix) lgl[j] = 0;
    loop(j, SZ(nei[i])) lgl[F[nei[i][j].first]] = 1;
    // Try to undo opers
    loop(j, SZ(nei[i])) {
      int to = nei[i][j].first, eg = nei[i][j].second;
      if (lgl[fix]) {
        sel[to] = 1;
        --val[eg];
        --fix;
      } else {
        break;
      }
    }
    F[i] = fix;
  }
  int all = 0;
  cont(i, n) all += sel[i];
  printf("%d\n", all);
  cont(i, n) if (sel[i]) printf("%d\n", i);
  cont(i, k) printf("%d %d %d\n", u[i], v[i], val[i]);
  return 0;
}

/**
 * 思考时间：8:50-9:50, 1h
 * 实现时间：9:50-10:10, 20min
 * 实现思路
 *  首先把所有边的边权设为
 * 1，这是一个中间值，有扩展的空间，同时将每个人设为“不选”。
 *  从前往后扫描每一个点，对于一个点的所有比它编号小的邻居（以下简称邻居），如果这个邻居的状态为“选”，则改为“不选”，并将边权加
 * 1（确保邻居的值不变）。
 *  进行完这些操作之后，当前点会有一个权值，此时可以做最多 S 次撤回操作（S
 * 为邻居个数）： 每次撤回，对于一个邻居，将邻居的状态改为“选”，并将边权减
 * 1，此时邻居的权值依然不变，但是当前点的权值减少了 1。 由于所有邻居最多只有 S
 * 个不同值，而撤回状态总共有 S + 1 种（撤回 0..S
 * 次），则一定能找到一个撤回状态，使得当前点的权值与邻居互不相同。
 */

// Problem: CF 1967 F - Next and Prev
// https://codeforces.com/contest/1967/problem/F

/*
Algorithm/Techniques: 
This code uses a segmented approach with bit manipulation and sorting techniques to efficiently calculate 
the sum of minimum differences between next and previous greater elements for subsequences of different lengths.
It is based on a combination of offline processing, binary indexed tree (BIT), and block-based optimization.

Time Complexity: O(n * sqrt(n) * log(n) + Q * sqrt(n))
Space Complexity: O(n * sqrt(n) + Q)

Where n is the size of the permutation and Q is the total number of queries.
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
constexpr int maxn = 300010, maxq = 100010, B = 400;
int n, bn, a[maxn], b[maxn], idx[maxn], nxt[maxn], add[maxn / B + 5],
    mxadd[maxn / B + 5], mx[maxn / B + 5], se[maxn / B + 5], t[maxn];
long long ans[maxq];
vector<int> val[maxn / B + 5], mxval[maxn / B + 5], pre[maxn / B + 5],
    mxpre[maxn / B + 5], pos[maxn / B + 5], ks[maxn];
void vAdd(int i) {
  for (; i <= n; i += (i & -i))
    t[i]++;
}
int nQuery(int i) {
  int s = 0;
  for (; i; i -= (i & -i))
    s += t[i];
  return s;
}
void vWork() {
  int i, j, tot = 0;
  for (i = 1; i <= n; i++)
    b[a[i]] = i;
  for (i = 1; i <= n; i++) {
    int p = b[i], bp = (p - 1) / B + 1;
    val[bp].clear();
    mxval[bp].clear();
    auto radixsort = [](vector<int> &v) {
      if (v.empty())
        return;
      static int buc[1024], res[B + 5];
      auto tmp = minmax_element(v.begin(), v.end());
      int mn = *tmp.first, rg = *tmp.second - mn;
      if (!rg)
        return;
      int lv = __lg(rg) / 2 + 1, len = 1 << lv, i;
      memset(buc, 0, len * 4);
      for (int &it : v)
        it -= mn, buc[it & (len - 1)]++;
      for (i = 1; i < len; i++)
        buc[i] += buc[i - 1];
      for (int it : v)
        res[--buc[it & (len - 1)]] = it;
      memset(buc, 0, len * 4);
      for (int it : v)
        buc[it >> lv]++;
      for (i = 1; i < len; i++)
        buc[i] += buc[i - 1];
      for (i = v.size() - 1; i >= 0; i--)
        v[--buc[res[i] >> lv]] = res[i] + mn;
    };
    auto getpre = [&](vector<int> &pre, const vector<int> &ori) {
      pre.resize(ori.size());
      if (ori.empty())
        return;
      pre[0] = ori[0];
      for (int i = 1; i < (int)ori.size(); i++)
        pre[i] = pre[i - 1] + ori[i];
    };
    int lstmx = mx[bp];
    vAdd(p);
    idx[p] = nQuery(p);
    mx[bp] = nxt[p] = n * 2;
    se[bp] = 0;
    auto it = pos[bp].begin();
    for (; it < pos[bp].end(); it++) {
      j = *it;
      if (j > p)
        break;
      nxt[j] += add[bp];
      if (nxt[j] > lstmx)
        nxt[j] += mxadd[bp];
      nxt[j] = min(nxt[j], idx[p]);
      idx[j] += add[bp];
      if (nxt[j] > mx[bp])
        se[bp] = mx[bp], mx[bp] = nxt[j];
      else if (nxt[j] > se[bp])
        se[bp] = nxt[j];
    }
    it = pos[bp].insert(it, p);
    for (it++; it != pos[bp].end(); it++) {
      j = *it;
      nxt[j] += add[bp];
      if (nxt[j] > lstmx)
        nxt[j] += mxadd[bp];
      nxt[j]++;
      idx[j] += add[bp] + 1;
      if (nxt[j] > mx[bp])
        se[bp] = mx[bp], mx[bp] = nxt[j];
      else if (nxt[j] > se[bp])
        se[bp] = nxt[j];
    }
    for (int j : pos[bp]) {
      if (nxt[j] == mx[bp])
        mxval[bp].push_back(nxt[j] - idx[j]);
      else
        val[bp].push_back(nxt[j] - idx[j]);
    }
    add[bp] = mxadd[bp] = 0;
    radixsort(val[bp]);
    getpre(pre[bp], val[bp]);
    radixsort(mxval[bp]);
    getpre(mxpre[bp], mxval[bp]);
    for (j = bp + 1; j <= bn; j++)
      add[j]++, mx[j]++, se[j]++;
    for (j = 1; j < bp; j++) {
      if (mx[j] <= idx[p])
        continue;
      if (se[j] < idx[p]) {
        mxadd[j] += idx[p] - mx[j], mx[j] = idx[p];
        continue;
      }
      val[j].clear();
      mxval[j].clear();
      lstmx = mx[j];
      mx[j] = idx[p], se[j] = 0;
      for (int x : pos[j]) {
        nxt[x] += add[j];
        idx[x] += add[j];
        if (nxt[x] > lstmx)
          nxt[x] += mxadd[j];
        if (nxt[x] >= idx[p]) {
          nxt[x] = idx[p];
          mxval[j].push_back(nxt[x] - idx[x]);
        } else {
          if (nxt[x] > se[j])
            se[j] = nxt[x];
          val[j].push_back(nxt[x] - idx[x]);
        }
      }
      add[j] = mxadd[j] = 0;
      radixsort(val[j]);
      getpre(pre[j], val[j]);
      radixsort(mxval[j]);
      getpre(mxpre[j], mxval[j]);
    }
    for (int ki : ks[i]) {
      tot++;
      for (j = 1; j <= bn; j++) {
        auto it = lower_bound(val[j].begin(), val[j].end(), ki);
        ans[tot] += (val[j].end() - it) * ki;
        if (it != val[j].begin())
          ans[tot] += pre[j][it - val[j].begin() - 1];
        it = lower_bound(mxval[j].begin(), mxval[j].end(), ki - mxadd[j]);
        ans[tot] += (mxval[j].end() - it) * ki;
        if (it != mxval[j].begin())
          ans[tot] += (it - mxval[j].begin()) * mxadd[j] +
                      mxpre[j][it - mxval[j].begin() - 1];
      }
    }
  }
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int i, ki, tot = 0;
    cin >> n;
    bn = (n - 1) / B + 1;
    for (i = 1; i <= n; i++)
      cin >> a[i];
    for (i = 1; i <= n; i++) {
      cin >> ki;
      ks[i].resize(ki);
      for (int &it : ks[i]) {
        cin >> it;
        ans[++tot] = -(i + it - 1);
      }
    }
    vWork();
    reverse(a + 1, a + n + 1);
    for (int x = 1; x <= n; x++)
      t[x] = 0;
    for (i = 1; i <= bn; i++)
      mx[i] = 0, se[i] = 0, val[i].clear(), mxval[i].clear(), pos[i].clear();
    vWork();
    for (int x = 1; x <= n; x++)
      t[x] = 0;
    for (i = 1; i <= bn; i++)
      mx[i] = 0, se[i] = 0, val[i].clear(), mxval[i].clear(), pos[i].clear();
    for (i = 1; i <= tot; i++)
      cout << ans[i] << '\n';
    tot = 0;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
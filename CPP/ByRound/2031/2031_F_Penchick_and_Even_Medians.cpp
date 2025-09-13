/*
 * Problem URL : https://codeforces.com/contest/2031/problem/F
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
#define pr pair<int, int>
#define mk make_pair
pr ask(vector<int> a) {
  cout << "? " << a.size() << ' ';
  for (auto x : a)
    cout << x << ' ';
  cout << endl;
  pr res;
  cin >> res.first >> res.second;
  if (res.first > res.second)
    swap(res.first, res.second);
  return res;
}
mt19937 rnd(114514);
void sol() {
  int n;
  cin >> n;
  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  int pa = -1, pb = -1;
  while (pa == -1) {
    int x = rnd() % n + 1, y = rnd() % n + 1;
    if (x == y)
      continue;
    vector<int> b;
    for (int i = 1; i <= n; ++i)
      if (i != x && i != y)
        b.push_back(i);
    pr res = ask(b);
    if (res.first == (n >> 1) && res.second == (n >> 1) + 1) {
      pa = x, pb = y;
      if (pa > pb)
        swap(pa, pb);
    }
  }
  vector<int> b;
  for (int i = 1; i <= n; ++i)
    if (i != pa && i != pb)
      b.push_back(i);
  vector<int> c;
  for (int i = 0; i < b.size(); i += 2) {
    pr res = ask({b[i], b[i + 1], pa, pb});
    if (res.first == (n >> 1) || res.second == (n >> 1) ||
        res.first == (n >> 1) + 1 || res.second == (n >> 1) + 1)
      c.push_back(b[i]), c.push_back(b[i + 1]);
  }
  for (int i = 0; i < c.size(); ++i)
    for (int j = i + 1; j < c.size(); ++j)
      if (ask({pa, pb, c[i], c[j]}) == mk(n >> 1, (n >> 1) + 1)) {
        cout << "! " << c[i] << " " << c[j] << endl;
        return;
      }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    sol();
}
/*
从一个子序列里删除2个元素会有怎么样的变化
仅有如下情况：
1. 删掉两中位数——更新两数
2. 删掉一个中位数，则原本那个中位数仍然保留
3. 删掉0个中位数，要么不变要么一个中位数更改
至少可以得到除非删掉2中位数，不然至少保留一个
暴力的想法是直接枚举答案，这部分是len(len-1)/2的，很劣
考虑有没有办法缩短len
发现每次至少有(len/2-1)*2/C(len,2)的概率缩短2
那么期望缩短次数？
*/

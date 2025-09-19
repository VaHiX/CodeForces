/*
 * Problem URL : https://codeforces.com/contest/1090/problem/K
 * Submit Date : 2025-09-08
 */

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
int n;
char p[1010000], q[1010000], tp[1010000];
struct A {
  string s;
  int ck, num;
  bool operator<(const A &p) const { return ck != p.ck ? ck < p.ck : s < p.s; }
} w[101000];
vector<vector<int>> Res;
int main() {
  int i, j;
  scanf("%d", &n);
  for (i = 1; i <= n; i++) {
    scanf("%s%s", p, q);
    int t = 0;
    for (j = 0; q[j]; j++) {
      t |= 1 << (q[j] - 'a');
    }
    w[i].ck = t;
    int L = 0;
    for (j = 0; p[j]; j++)
      ;
    int ck = 0;
    for (j = j - 1; j >= 0; j--) {
      if (!((t >> (p[j] - 'a')) & 1))
        ck = 1;
      if (ck)
        tp[L++] = p[j];
    }
    tp[L] = 0;
    w[i].s = tp;
    w[i].num = i;
  }
  sort(w + 1, w + n + 1);
  vector<int> T;
  T.push_back(w[1].num);
  for (i = 2; i <= n; i++) {
    if (w[i - 1] < w[i]) {
      Res.push_back(T);
      T.clear();
    }
    T.push_back(w[i].num);
  }
  Res.push_back(T);
  printf("%d\n", Res.size());
  for (auto &t : Res) {
    printf("%d ", t.size());
    for (auto &x : t) {
      printf("%d ", x);
    }
    puts("");
  }
}
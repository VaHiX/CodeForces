/*
 * Problem URL : https://codeforces.com/problemset/problem/827/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>

using namespace std;
const int MAXN = 2e6 + 10;
char s[MAXN];
int len[MAXN], ss[MAXN];
char an[MAXN];
int max_n;
int st = 0;
pair<int, int> d[MAXN];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", s + st);
    ss[i] = st;
    len[i] = strlen(s + st);
    st += len[i];
    int m;
    scanf("%d", &m);
    for (int j = 0; j < m; j++) {
      int x;
      scanf("%d", &x);
      max_n = max(max_n, x + len[i] - 1);
      d[x] = max(d[x], make_pair(len[i], i));
    }
  }
  int far = 0, from = -1, id = -1;
  for (int i = 1; i < max_n + 1; i++) {
    if (d[i].first + i - 1 > far) {
      from = i;
      far = d[i].first + i - 1;
      id = d[i].second;
    }
    if (far < i)
      an[i] = 'a';
    else {
      an[i] = s[ss[id] + i - from];
    }
  }
  puts(an + 1);
  return 0;
}
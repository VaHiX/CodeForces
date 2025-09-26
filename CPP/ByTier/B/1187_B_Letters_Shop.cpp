/*
 * Problem URL : https://codeforces.com/problemset/problem/1187/B
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
vector<int> v[127];
char s[N];
int n, m;
int main() {
  scanf("%d%s%d", &n, &s, &m);
  for (int i = 0; s[i]; ++i)
    v[s[i]].push_back(i);
  for (; m--; printf("%d\n", n + 1)) {
    scanf("%s", s);
    vector<int> p(127);
    for (int i = n = 0; s[i]; ++i)
      n = max(n, v[s[i]][p[s[i]]++]);
  }
}

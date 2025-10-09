/*
 * Problem URL : https://codeforces.com/problemset/problem/1251/C
 * Submit Date : 2025-08-19
 */

#include <bits/stdc++.h>
using namespace std;
char s[3000005];
int main() {
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%s", s);
    int len(strlen(s));
    vector<char> v[2];
    for (int i(0); i < len; i++) {
      v[(s[i] - '0') & 1].push_back(s[i]);
    }
    merge(v[0].begin(), v[0].end(), v[1].begin(), v[1].end(), s);
    puts(s);
  }
}
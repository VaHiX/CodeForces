/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
const int MAX = 59;
char ch, s[MAX];
int f(int x, int y) {
  if (s[x] == '0' && x + 1 < y || x + 7 < y)
    return -1;
  ch = s[y], s[y] = 0;
  int c = atoi(s + x);
  s[y] = ch;
  return c > 1000000 ? -1 : c;
}
int main() {
  cin >> s;
  int l = strlen(s), ans = -1;
  for (int i = 1; i < l; i++)
    for (int j = i + 1; j < l; j++) {
      int x = f(0, i), y = f(i, j), z = f(j, l);
      if (x != -1 && y != -1 && z != -1 && x + y + z > ans)
        ans = x + y + z;
    }
  cout << ans;
}

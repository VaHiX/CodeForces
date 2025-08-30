/*
 * Problem URL : https://codeforces.com/problemset/problem/65/D
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 10005;
string str;
int n;
set<pair<pair<int, int>, pair<int, int>>> vis[maxn];
bool ok[4] = {false, false, false, false};
void recur(int pos, int g, int h, int r, int s) {
  if (pos == n) {
    int mini = min({g, h, r, s});
    if (g == mini)
      ok[0] = true;
    if (h == mini)
      ok[1] = true;
    if (r == mini)
      ok[2] = true;
    if (s == mini)
      ok[3] = true;
    return;
  }
  if (vis[pos].count({{g, h}, {r, s}}) != 0)
    return;
  vis[pos].insert({{g, h}, {r, s}});
  if (str[pos] == 'G')
    recur(pos + 1, g + 1, h, r, s);
  if (str[pos] == 'H')
    recur(pos + 1, g, h + 1, r, s);
  if (str[pos] == 'R')
    recur(pos + 1, g, h, r + 1, s);
  if (str[pos] == 'S')
    recur(pos + 1, g, h, r, s + 1);
  if (str[pos] == '?') {
    int mini = min({g, h, r, s});
    if (g == mini)
      recur(pos + 1, g + 1, h, r, s);
    if (h == mini)
      recur(pos + 1, g, h + 1, r, s);
    if (r == mini)
      recur(pos + 1, g, h, r + 1, s);
    if (s == mini)
      recur(pos + 1, g, h, r, s + 1);
  }
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> str;
  recur(0, 0, 0, 0, 0);
  if (ok[0])
    cout << "Gryffindor\n";
  if (ok[1])
    cout << "Hufflepuff\n";
  if (ok[2])
    cout << "Ravenclaw \n";
  if (ok[3])
    cout << "Slytherin\n";
}

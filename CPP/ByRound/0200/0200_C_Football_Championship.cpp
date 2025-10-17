/*
 * Problem URL : https://codeforces.com/problemset/problem/200/C
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int mx, my, top;
string nx, ny;
char c;
map<string, pair<pair<int, int>, pair<int, int>>> mp;
struct node {
  string s;
  int ss, sa, sb;
} stu[15];
bool cmp(node sx, node sy) {
  if (sx.ss > sy.ss)
    return 1;
  else if (sx.ss == sy.ss) {
    if (sx.sa - sx.sb > sy.sa - sy.sb)
      return 1;
    else if (sx.sa - sx.sb == sy.sa - sy.sb) {
      if (sx.sa > sy.sa)
        return 1;
      else if (sx.sa == sy.sa)
        return sx.s < sy.s;
      else
        return 0;
    } else
      return 0;
  } else
    return 0;
}
int main() {
  for (int i = 0; i < 5; i++) {
    cin >> nx >> ny >> mx >> c >> my;
    if (mx == my)
      mp[nx].x.x++, mp[ny].x.x++;
    else if (mx > my)
      mp[nx].x.x += 3;
    else
      mp[ny].x.x += 3;
    mp[nx].y.x += mx, mp[nx].y.y += my, mp[nx].x.y++;
    mp[ny].y.x += my, mp[ny].y.y += mx, mp[ny].x.y++;
  }
  nx = "BERLAND", mp[nx].x.x += 3;
  for (auto i : mp) {
    if (i.y.x.y == 2 && i.x != nx)
      ny = i.x;
  }
  for (int i = 1; i <= 100; i++) {
    for (my = 0; my <= 100; my++) {
      mx = i + my, top = 0;
      mp[nx].y.x += mx, mp[nx].y.y += my;
      mp[ny].y.x += my, mp[ny].y.y += mx;
      for (auto i : mp)
        top++, stu[top].s = i.x, stu[top].ss = i.y.x.x, stu[top].sa = i.y.y.x,
               stu[top].sb = i.y.y.y;
      sort(stu + 1, stu + 5, cmp);
      if (stu[1].s == nx || stu[2].s == nx) {
        cout << mx << ":" << my;
        return 0;
      }
      mp[nx].y.x -= mx, mp[nx].y.y -= my;
      mp[ny].y.x -= my, mp[ny].y.y -= mx;
    }
  }
  cout << "IMPOSSIBLE";
  return 0;
}

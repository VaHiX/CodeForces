/*
 * Problem URL : https://codeforces.com/contest/180/problem/A
 * Submit Date : 2025-09-07
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  vector<int> a(1000);
  int c = 1;
  for (int i = 0; i < k; i++) {
    int x;
    cin >> x;
    for (int j = 0; j < x; j++) {
      int y;
      cin >> y;
      a[y] = c++;
    }
  }
  vector<pair<int, int>> p;
  for (int i = 1; i < c; i++) {
    int escape = find(a.begin() + 1, a.end(), 0) - a.begin();
    int current = find(a.begin() + 1, a.end(), i) - a.begin();
    int next = i;
    if (current == next)
      continue;
    if (next == 0)
      continue;
    if (next != escape)
      p.push_back(make_pair(next, escape));
    p.push_back(make_pair(current, next));
    a[current] = 0;
    a[escape] = a[next];
    a[next] = next;
  }
  cout << p.size() << endl;
  for (int i = 0; i < (int)p.size(); i++)
    cout << p[i].first << " " << p[i].second << endl;
  return 0;
}

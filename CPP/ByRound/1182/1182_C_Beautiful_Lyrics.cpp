/*
 * Problem URL : https://codeforces.com/problemset/problem/1182/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
char s[2 * N], las[N];
int n, st[N], num[N];
vector<pair<int, int>> fiv, sev;
unordered_map<int, unordered_map<char, int>> mp;
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    char *ss = s + st[i];
    scanf("%s", ss);
    st[i + 1] = ss + strlen(ss) + 1 - s;
    for (int j = 0; ss[j]; ++j)
      if (ss[j] == 'a' || ss[j] == 'e' || ss[j] == 'o' || ss[j] == 'i' ||
          ss[j] == 'u') {
        ++num[i];
        las[i] = ss[j];
      }
    if (mp[num[i]].count(las[i])) {
      sev.emplace_back(mp[num[i]][las[i]], i);
      mp[num[i]].erase(las[i]);
    } else
      mp[num[i]][las[i]] = i;
  }
  for (unordered_map<int, unordered_map<char, int>>::iterator it = mp.begin();
       it != mp.end(); ++it) {
    int pre = -1;
    for (auto p : it->second) {
      if (pre < 0)
        pre = p.second;
      else {
        fiv.emplace_back(p.second, pre);
        pre = -1;
      }
    }
  }
  while (sev.size() > fiv.size()) {
    fiv.push_back(sev.back());
    sev.pop_back();
  }
  printf("%d\n", sev.size());
  while (!sev.empty()) {
    printf("%s %s\n%s %s\n", s + st[fiv.back().first], s + st[sev.back().first],
           s + st[fiv.back().second], s + st[sev.back().second]);
    sev.pop_back();
    fiv.pop_back();
  }
}

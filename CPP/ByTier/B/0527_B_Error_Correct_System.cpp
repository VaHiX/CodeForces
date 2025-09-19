/*
 * Problem URL : https://codeforces.com/contest/527/problem/B
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/527/problem/B
 * Submit Date : 2025-09-02
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define inf 1000000000
#define pp pair<char, char>

using namespace std;

int main() {

  int i, j, k;
  int n, m;
  int idx = -1, jdx = -1;
  string s, t;

  cin >> n >> s >> t;

  vector<int> sv[26];
  vector<int> tv[26];

  vector<char> sc;
  vector<char> tc;
  vector<int> v;

  map<pp, bool> mp;

  int cnt = 0;
  for (i = 0; i < n; i++) {
    if (s[i] != t[i]) {
      cnt++;
      sc.push_back(s[i]);
      sv[s[i] - 'a'].push_back(i + 1);
      v.push_back(i + 1);

      tc.push_back(t[i]);
      tv[t[i] - 'a'].push_back(i + 1);

      mp[{s[i], t[i]}] = 1;
    }
  }

  char x, y;
  for (i = 0; i < sc.size(); i++) {
    x = sc[i];
    y = tc[i];
    pp p = {y, x};

    if (mp[p]) {

      cout << cnt - 2 << endl;
      cout << v[i] << " ";

      for (j = 0; j < n; j++) {
        if (s[j] == y && t[j] == x) {
          cout << j + 1 << endl;
          return 0;
        }
      }
    }
  }

  for (i = 0; i < sc.size(); i++) {
    x = sc[i];
    y = tc[i];

    if (sv[y - 'a'].size() > 0) {
      cout << cnt - 1 << endl;
      cout << sv[y - 'a'][0] << " " << v[i] << endl;
      return 0;
    }
  }

  cout << cnt << endl;
  cout << "-1 -1" << endl;

  return 0;
}

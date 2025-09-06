/*
 * Problem URL : https://codeforces.com/contest/716/problem/B
 * Submit Date : 2025-09-02
 */



#include <bits/stdc++.h>

typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
#define N 50

using namespace std;

int main() {

  int i, j, k;
  int n, m, sum;
  string s, t;
  map<char, int> mp;

  cin >> s;

  if (s.length() < 26) {
    cout << "-1";
    return 0;
  }

  i = 0, j = 25;
  for (k = 0; k < 26; k++)
    mp[s[k]]++;

  bool f;
  while (j < s.length()) {
    f = 1;
    sum = 0;

    for (k = 'A'; k <= 'Z'; k++) {
      if (mp[k] > 1) {
        f = 0;
        break;
      }

      else if (mp[k] == 0)
        sum++;
    }

    if (!f) {
      mp[s[i]]--;
      i++;
      j++;
      mp[s[j]]++;
      continue;
    }

    if (sum == mp['?']) {
      stack<char> v;
      for (k = 'A'; k <= 'Z'; k++) {
        if (!mp[k])
          v.push(k);
      }

      for (k = i; k <= j; k++) {
        if (s[k] == '?')
          s[k] = v.top(), v.pop();
      }

      for (k = 0; k < s.length(); k++) {
        if (s[k] == '?')
          s[k] = 'A';
      }

      cout << s;
      return 0;
    }
  }

  cout << "-1";

  return 0;
}

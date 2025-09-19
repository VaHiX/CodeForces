/*
 * Problem URL : https://codeforces.com/problemset/problem/2086/F
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

string f(string &s) {
  int a = 0;
  int b = 0;
  for (char c : s) {
    if (c == 'a')
      a++;
    else
      b++;
  }

  string ret;
  while (a >= 2 || b >= 2) {
    if (a >= 2 && b >= 2) {
      ret += "ab";
      a -= 2;
      b -= 2;
    } else if (a >= 2) {
      ret += "a";
      a -= 2;
    } else if (b >= 2) {
      ret += "b";
      b -= 2;
    }
  }

  if (a == 1)
    ret += 'a';
  else if (b == 1)
    ret += 'b';

  for (int i = ret.sz - 2; i >= 0; i--)
    ret += ret[i];

  return ret;
}

int main() {
  // ios::sync_with_stdio(0);
  // cin.tie(0);
  // cout.tie(0);

  string s;
  while (1) {
    char c;
    cin >> c;

    if (c == '0')
      break;

    s += c;

    if (s.sz & 1) {
      string x = f(s);
      if (x == s) {
        cout << 0 << ' ' << 0 << endl;
        continue;
      }

      int i = -1;
      int j = -1;
      for (int k = 0; k < x.sz; k++) {
        if (x[k] == s[k])
          continue;

        if (i == -1)
          i = k;
        else if (j == -1) {
          j = k;
          break;
        }
      }

      swap(s[i], s[j]);
      cout << i + 1 << ' ' << j + 1 << endl;
      continue;
    }

    s += 'a';
    string x = f(s);
    s.pop_back();

    s += 'b';
    string y = f(s);
    s.pop_back();

    bool flag = false;
    for (int i = 0; i < s.sz; i++) {
      for (int j = i + 1; j < s.sz; j++) {
        swap(s[i], s[j]);

        int diff = 0;
        for (int k = 0; k < s.sz; k++) {
          if (s[k] == x[k])
            continue;

          if (++diff == 3)
            break;
        }

        if (diff == 3) {
          swap(s[i], s[j]);
          continue;
        }

        diff = 0;
        for (int k = 0; k < s.sz; k++) {
          if (s[k] == y[k])
            continue;

          if (++diff == 3)
            break;
        }

        if (diff == 3) {
          swap(s[i], s[j]);
          continue;
        }

        cout << i + 1 << ' ' << j + 1 << endl;
        flag = true;
        break;
      }

      if (flag)
        break;
    }

    if (!flag)
      cout << 0 << ' ' << 0 << endl;
  }
}
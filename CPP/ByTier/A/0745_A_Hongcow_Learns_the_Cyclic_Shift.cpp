/*
 * Problem URL : https://codeforces.com/contest/745/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>

typedef long long int ll;
#define pp pair<ll, ll>

#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)

using namespace std;

int main() {
  ll i, j, k;
  ll count = 0;
  char ch;
  string s, t;

  cin >> s;
  map<string, int> ss;
  k = s.length() - 1;

  for (i = 0; i < s.length(); i++) {
    if (ss[s] == 0) {
      ss[s]++;
      count++;
    }

    t = s.back();
    s.pop_back();
    t.append(s);
    s = t;
  }

  cout << count;

  return 0;
}

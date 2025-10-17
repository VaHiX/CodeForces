/*
 * Problem URL : https://codeforces.com/contest/834/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>

using namespace std;

int main() {

  ll i, j, k;
  ll n, m;
  char ch1, ch2;

  cin >> ch1 >> ch2;
  cin >> n;

  n = n % 4;

  string s = "v<^>";

  char cw, ccw;
  for (i = 0; i < 4; i++) {
    if (s[i] == ch1) {
      j = i;
      break;
    }
  }

  i = j;
  k = n;
  while (k--) {
    i++;
    i = i % 4;
  }

  cw = s[i];

  i = j;
  k = n;
  while (k--) {
    i--;

    if (i < 0)
      i = 3;
  }

  ccw = s[i];

  if (cw == ccw)
    cout << "undefined";
  else if (cw == ch2)
    cout << "cw";
  else if (ccw == ch2)
    cout << "ccw";
  else
    cout << "undefined";

  return 0;
}

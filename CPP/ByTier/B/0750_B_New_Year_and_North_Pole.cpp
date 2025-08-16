/*
 * Problem URL : https://codeforces.com/problemset/problem/750/B
 * Submit Date : 2025-08-14
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
  ll n, m;
  ll cur = 0, ew = 0;
  bool f = true;

  cin >> n;
  string dir[n];
  ll len[n];

  for (i = 0; i < n; i++)
    cin >> len[i] >> dir[i];

  for (i = 0; i < n; i++) {
    if (cur == 0) {
      if (dir[i] == "South" && (cur + len[i]) <= 20000 && (cur + len[i]) >= 0) {
        cur += (len[i]);
      }

      else {
        f = false;
        break;
      }
    }

    else if (cur == 20000) {
      if (dir[i] == "North" && (cur - len[i]) <= 20000 && (cur - len[i]) >= 0) {
        cur -= len[i];
      }

      else {
        f = false;
        break;
      }
    }

    else {
      if (dir[i] == "North" && (cur - len[i] > 20000 || cur - len[i] < 0)) {
        f = false;
        break;
      }

      if (dir[i] == "South" && (cur + len[i] > 20000 || cur + len[i] < 0)) {
        f = false;
        break;
      }

      if (dir[i] == "North" && (cur - len[i]) <= 20000 && (cur - len[i]) >= 0) {
        cur -= len[i];
        continue;
      }

      else if (dir[i] == "South" && (cur + len[i]) <= 20000 &&
               (cur + len[i]) >= 0) {
        cur += len[i];
        continue;
      }

      if (dir[i] == "North" && (cur - len[i]) > 20000 && (cur - len[i]) < 0) {
        f = false;
        break;
      }

      if (dir[i] == "South" && (cur + len[i] > 20000) && (cur + len[i] < 0)) {
        f = false;
        break;
      }
    }
  }

  if (cur == 0 && f == true)
    cout << "YES";
  else
    cout << "NO";

  return 0;
}

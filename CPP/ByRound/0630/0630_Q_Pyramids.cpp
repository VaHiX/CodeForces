/*
 * Problem URL : https://codeforces.com/contest/630/problem/Q
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define pb push_back
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long double a, b, c;
  cin >> a >> b >> c;
  long double t = ((a * a) / sqrt(2)) * a / 6;
  long double s = ((b * b) / sqrt(2)) * b / 3;
  long double p = c * c * .3015028324 * c;
  cout << setprecision(10) << t + s + p << '\n';
  return 0;
}

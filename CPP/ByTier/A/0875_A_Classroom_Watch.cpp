/*
 * Problem URL : https://codeforces.com/contest/875/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
int n, x, i, s;
vector<int> b;
int main() {
  cin >> n;
  for (i = 100; i > 0; i--) {
    for (x = n - i, s = 0; x; x /= 10)
      s += x % 10;
    i == s ? b.push_back(n - i), 0 : 0;
  }
  cout << b.size() << endl;
  for (auto y : b)
    cout << y << " ";
}

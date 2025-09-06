/*
 * Problem URL : https://codeforces.com/problemset/problem/257/B
 * Submit Date : 2025-08-09
 */

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  int Vasya = min(n, m);
  int Petya = n + m - 1 - Vasya;
  cout << Petya << " " << Vasya << endl;
  return 0;
}

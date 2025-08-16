/*
 * Problem URL : https://codeforces.com/problemset/problem/581/A
 * Submit Date : 2025-08-16
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  int i, j, k;
  int n;
  int a, b;

  cin >> a >> b;

  if (a > b) {
    cout << b << " " << (a - b) / 2;
  } else {
    cout << a << " " << (b - a) / 2;
  }

  return 0;
}

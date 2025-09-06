/*
 * Problem URL : https://codeforces.com/contest/714/problem/A
 * Submit Date : 2025-09-02
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
  long long int i, j, k;
  long long int n, count = 1;
  long long int l1, l2, r1, r2;
  long long int s, e;

  cin >> l1 >> r1 >> l2 >> r2 >> k;

  s = max(l1, l2);
  e = min(r1, r2);

  if (s > e) {
    cout << "0";
    return 0;
  }

  if (k >= s && k <= e)
    count--;

  count += abs(s - e);
  cout << count << endl;

  return 0;
}

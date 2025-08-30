/*
 * Problem URL : https://codeforces.com/problemset/problem/327/A
 * Submit Date : 2025-08-09
 */

#include <iostream>

using namespace std;

int main() {
  int n, a, count1(0), extra0(0), extra0max(-1);
  cin >> n;
  while (n--) {
    cin >> a;
    if (a == 1) {
      count1 += 1;
      if (extra0 > 0) {
        extra0 -= 1;
      }
    } else {
      extra0 += 1;
      if (extra0 > extra0max) {
        extra0max = extra0;
      }
    }
  }
  cout << count1 + extra0max << endl;
  return 0;
}

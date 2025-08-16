/*
 * Problem URL : https://codeforces.com/problemset/problem/242/A
 * Submit Date : 2025-08-09
 */

#include <iostream>

using namespace std;

int main() {
  int x, y, a, b;
  cin >> x >> y >> a >> b;
  int count = 0;
  for (int Vasya = a; Vasya <= x; ++Vasya) {
    int end = min(Vasya - 1, y);
    if (b <= end) {
      count += (end - b + 1);
    }
  }
  cout << count << endl;
  for (int Vasya = a; Vasya <= x; ++Vasya) {
    int end = min(Vasya - 1, y);
    for (int Petya = b; Petya <= end; ++Petya) {
      cout << Vasya << " " << Petya << endl;
    }
  }
  return 0;
}

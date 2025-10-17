/*
 * Problem URL : https://codeforces.com/problemset/problem/255/A
 * Submit Date : 2025-08-09
 */

#include <iostream>

using namespace std;

int main() {
  int n, a, b, c, chest(0), biceps(0), back(0);
  cin >> n;
  for (int i = 0; i < n / 3; ++i) {
    cin >> a >> b >> c;
    chest += a;
    biceps += b;
    back += c;
  }
  if (n % 3 == 1) {
    cin >> a;
    chest += a;
  } else if (n % 3 == 2) {
    cin >> a >> b;
    chest += a;
    biceps += b;
  }
  if (chest > biceps && chest > back) {
    cout << "chest" << endl;
  } else if (biceps > back && biceps > chest) {
    cout << "biceps" << endl;
  } else {
    cout << "back" << endl;
  }
  return 0;
}

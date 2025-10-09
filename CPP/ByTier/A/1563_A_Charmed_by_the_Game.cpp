/*
 * Problem URL : https://codeforces.com/contest/1563/problem/A
 * Submit Date : 2025-08-31
 */

#include <iostream> // cin, cout
#include <stdlib.h> // abs

using namespace std;

int main(void) {
  int t;
  cin >> t;

  while (t--) {
    int a;
    int b;
    cin >> a >> b;

    int d = abs(a - b) / 2;
    int k = 0;
    if (0 == (a + b) % 2) {
      int c = 0;
      for (int i = 0; k < a + b - d; i += 2) {
        k = d + i;
        c++;
      }
      cout << c << endl;
      k = 0;
      for (int i = 0; k < a + b - d; i += 2) {
        k = d + i;
        cout << k << " ";
      }
      cout << endl;
    } else {
      int c = 0;
      for (int i = 0; k < a + b - d; i += 1) {
        k = d + i;
        c++;
      }
      cout << c << endl;
      k = 0;
      for (int i = 0; k < a + b - d; i += 1) {
        k = d + i;
        cout << k << " ";
      }
      cout << endl;
    }
  }
  return 0;
}

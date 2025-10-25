/*
 * Problem URL : https://codeforces.com/problemset/problem/1253/A
 * Submit Date : 2025-08-21
 */

#include <iostream>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    long int n;
    cin >> n;
    int i, k = 0;
    long a[n], b[n], c[n];
    for (i = 0; i < n; i++) {
      cin >> a[i];
    }
    for (i = 0; i < n; i++) {
      cin >> b[i];
      c[i] = b[i] - a[i];
      if (c[i] != 0 && c[i] != c[i - 1])
        if (c[i] > 0)
          k++;
        else
          k = 3;
    }
    if (k > 1)
      cout << "No" << endl;
    else
      cout << "Yes" << endl;
  }
}
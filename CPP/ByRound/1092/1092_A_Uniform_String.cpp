/*
 * Problem URL : https://codeforces.com/contest/1092/problem/A
 * Submit Date : 2025-08-29
 */

#include <iostream>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
      cout << char(i % k + 'a');
    cout << endl;
  }
}
/*
 * Problem URL : https://codeforces.com/contest/403/problem/A
 * Submit Date : 2025-09-06
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, p;
    cin >> n >> p;
    int egdes = 0;
    for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++) {
        if (egdes < 2 * n + p) {
          egdes++;
          cout << i << " " << j << endl;
        } else {
          break;
        };
      }
  }
}
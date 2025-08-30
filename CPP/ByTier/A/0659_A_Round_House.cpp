/*
 * Problem URL : https://codeforces.com/problemset/problem/659/A
 * Submit Date : 2025-08-16
 */

#import <iostream>
using namespace std;
int a, b, n;
main() {
  cin >> n >> a >> b;
  cout << (100 * n + a + b - 1) % n + 1;
}
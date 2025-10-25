/*
 * Problem URL : https://codeforces.com/contest/1165/problem/A
 * Submit Date : 2025-08-28
 */

#import "iostream"
main() {
  int n, x, y, a = 1, i = 0;
  std::cin >> n >> x >> y;
  for (getchar();
       i < n && (a += getchar() - "01"[i == n - y - 1] && i + x >= n); i++)
    ;
  std::cout << a - 1;
}
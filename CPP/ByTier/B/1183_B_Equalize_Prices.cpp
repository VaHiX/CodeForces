/*
 * Problem URL : https://codeforces.com/problemset/problem/1183/B
 * Submit Date : 2025-08-21
 */

#import <iostream>
int t, n, k, M, m, e;
main() {
  for (std::cin >> t; t--; printf("%d\n", m + k >= M - k ? m + k : -1))
    for (M = 0, m = 1e9, std::cin >> n >> k; n--;
         e > m ?: m = e, e < M ?: M = e)
      std::cin >> e;
}
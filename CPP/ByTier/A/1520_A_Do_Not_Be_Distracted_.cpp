/*
 * Problem URL : https://codeforces.com/problemset/problem/1520/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
int t, i, j, k, f, n;
std::string s;
main() {
  for (std::cin >> t; t--;) {
    std::cin >> n >> s, f = 0;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        for (int k = i + 1; k < j; k++)
          if (s[i] == s[j] && s[i] != s[k])
            f = 1;
    puts(f ? "NO" : "YES");
  }
}
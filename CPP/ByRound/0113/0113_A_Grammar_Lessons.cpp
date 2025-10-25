/*
 * Problem URL : https://codeforces.com/problemset/problem/113/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
string t, s[6] = {"lios", "liala", "etr", "etra", "initis", "inites"};
int o, O = 1, f, z, i, d, K, v;
int main() {
  while (!(K = !O) && cin >> t)
    for (i = O = 0; i < 6; ((d = t.size() - s[i].size()) >= 0 &&
                            t.substr(d) == s[i] && !(z && v > i))
                           ? O = 1,
        v = i, z++, f += i / 2 % 2, o += i % 2 : 0, i++)
      ;
  cout << (K || z - 1 && (o % z || f - 1) ? "NO" : "YES");
} /*1698481457.4403214*/
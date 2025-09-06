/*
 * Problem URL : https://codeforces.com/problemset/problem/101/A
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;

int cnt[30], rem[30], n, k, i, j;
pair<int, int> wt[30];
string str;

int main() {
  cin >> str >> k;
  for (char c : str)
    cnt[c - 'a']++;
  for (i = 0; i < 26; i++)
    wt[i] = {cnt[i], i};
  sort(wt, wt + 26);
  for (i = 0; i < 26; i++) {
    k -= wt[i].first;
    if (k >= 0)
      rem[wt[i].second] = 1, n++;
  }
  printf("%d\n", 26 - n);
  for (char c : str)
    if (!rem[c - 'a'])
      putchar(c);
  return 0;
}
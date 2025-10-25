/*
 * Problem URL : https://codeforces.com/problemset/problem/37/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1 << 10;
pair<int, int> a[N];
string s[N];
int n, p;
void Trie(string t) {
  if (p >= n)
    return;
  if (t.size() == a[p].first) {
    s[a[p++].second] = t;
    return;
  }
  Trie(t + '0');
  Trie(t + '1');
}
int main() {
  cin >> n;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    a[i] = {x, i};
  }
  sort(a, a + n);
  Trie("");
  if (p ^ n)
    return cout << "NO", 0;
  cout << "YES\n";
  for (int i = 0; i < n; i++)
    cout << s[i] << '\n';
}

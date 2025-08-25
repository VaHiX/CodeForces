/*
 * Problem URL : https://codeforces.com/problemset/problem/1889/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int T_T, n, i;
string s;
vector<int> op;
int main() {
  for (cin >> T_T; T_T--;) {
    cin >> n >> s;
    op.clear();
    if ((n & 1) || count(begin(s), end(s), '0') != n / 2) {
      puts("-1");
      continue;
    }
    for (i = 0; i < n / 2; ++i)
      if (s[i] == s[n - i - 1])
        if (s[i] == '0') {
          op.push_back(n - i);
          s.insert(begin(s) + n - i, {'0', '1'}), n += 2;
        } else {
          op.push_back(i);
          s.insert(begin(s) + i, {'0', '1'});
          n += 2;
        }
    cout << op.size() << endl;
    for (int x : op)
      printf("%d ", x);
    puts("");
  }
}
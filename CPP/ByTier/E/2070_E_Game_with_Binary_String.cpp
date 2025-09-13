/*
 * Problem URL : https://codeforces.com/problemset/problem/2070/E
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int N = 3e5 + 10, P = N * 3;
int n;
char s[N];
int c[N], b[N * 4];
int tr[N * 4];
LL ans;
int lowbit(int x) { return x & -x; }
void add(int x, int c) {
  for (int i = x; i < N * 4; i += lowbit(i))
    tr[i] += c;
}
int sum(int x) {
  int res = 0;
  for (int i = x; i; i -= lowbit(i))
    res += tr[i];
  return res;
}
int main() {
  cin >> n;
  scanf("%s", s + 1);
  b[P]++;
  add(P, 1);
  for (int i = 1; i <= n; i++) {
    c[i] = c[i - 1] + (s[i] == '0');
    int x = 4 * c[i] - 3 * i;
    ans += b[x + 1 + P] + sum(x - 2 + P);
    b[x + P]++;
    add(x + P, 1);
    // cout<<i<<" "<<ans<<" "<<x<<endl;
  }
  cout << ans << endl;
  return 0;
}
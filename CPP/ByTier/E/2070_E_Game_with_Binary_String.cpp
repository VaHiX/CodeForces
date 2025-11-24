// Problem: CF 2070 E - Game with Binary String
// https://codeforces.com/contest/2070/problem/E

#include <cstdio>
#include <iostream>
#include <utility>

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
  add(P, 1); // Initialize BIT with base case
  for (int i = 1; i <= n; i++) {
    c[i] = c[i - 1] + (s[i] == '0'); // Count of zeros up to index i
    int x = 4 * c[i] - 3 * i; // Transformation for coordinate compression
    ans += b[x + 1 + P] + sum(x - 2 + P); // Count valid previous states contributing to win
    b[x + P]++; // Increment frequency of current state
    add(x + P, 1); // Add current state to BIT for future queries
  }
  cout << ans << endl;
  return 0;
}

// https://github.com/VaHiX/codeForces/
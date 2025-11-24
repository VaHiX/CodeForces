// Problem: CF 1849 C - Binary String Copying
// https://codeforces.com/contest/1849/problem/C

/*
 * Problem: Binary String Copying
 * 
 * Algorithm/Technique: 
 * - Preprocessing to determine how each character in the original string can be moved by sorting operations
 * - For each operation, compute the new position range of characters that would be sorted
 * - Sort and deduplicate the ranges to count unique resulting strings
 * 
 * Time Complexity: O(n + m * log(m)) where n is string length, m is number of operations
 * Space Complexity: O(n + m) for storing string, move arrays and operation ranges
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int M = 2e5 + 5;
int t, n, m, move0[M], move1[M];
char s[M];
struct node {
  int l, r;
} a[M];
bool cmp(node A, node B) {
  if (A.l != B.l)
    return A.l < B.l;
  return A.r < B.r;
}
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    // Initialize move0 and move1 arrays
    for (int i = 1; i <= n; i++)
      move0[i] = move1[i] = i;
    int flag = -1, st = 1;
    // Preprocessing to find ranges where characters can be moved
    for (int i = 1; i <= n; i++) {
      if (flag == -1) {
        flag = s[i] - '0';
        continue;
      }
      if (flag != s[i] - '0') {
        // Update move0 and move1 based on character transitions
        for (int j = st; j < i; j++) {
          if (flag == 0)
            move0[j] = i - 1;
          else
            move1[j] = st;
        }
        st = i;
        flag = s[i] - '0';
      }
    }
    // Handle the last segment
    for (int j = st; j <= n; j++) {
      if (flag == 0)
        move0[j] = n;
      else
        move1[j] = st;
    }
    int ans = 0, cnt = 0;
    // Process each operation
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      // Adjust positions based on preprocessed data
      if (s[x] == '0')
        x = move0[x] + 1;
      if (s[y] == '1')
        y = move1[y] - 1;
      // If x >= y, result is the same as original string
      if (x >= y)
        ans = 1;
      else
        // Store the range of indices that will be changed
        a[++cnt].l = x, a[cnt].r = y;
    }
    // Sort the ranges
    sort(a + 1, a + 1 + cnt, cmp);
    if (cnt >= 1)
      ans++;
    // Count unique ranges
    for (int i = 2; i <= cnt; i++) {
      if (a[i].l != a[i - 1].l || a[i].r != a[i - 1].r)
        ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
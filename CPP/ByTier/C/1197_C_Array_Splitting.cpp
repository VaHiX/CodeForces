/*
 * Problem URL : https://codeforces.com/contest/1197/problem/C
 * Submit Date : 2025-08-29
 */

/*
 * Problem URL : https://codeforces.com/contest/1197/problem/C
 * Submit Date : 2025-08-28
 */

#include <queue>
#include <stdio.h>
int a, b, c, n, k;
std::priority_queue<int> Q;
int main() {
  scanf("%d%d%d", &n, &k, &b);
  a = c = b;
  for (int i = 2; i <= n; i++, b = a) {
    scanf("%d", &a);
    Q.push(a - b);
  }
  c = a - c;
  while (--k && !Q.empty()) {
    c -= Q.top();
    Q.pop();
  }
  printf("%d", c);
}

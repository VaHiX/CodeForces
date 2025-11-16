// Problem: CF 1863 E - Speedrun
// https://codeforces.com/contest/1863/problem/E

/*
Algorithm: Topological Sort + Dynamic Programming + Sliding Window Technique
Time Complexity: O(n + m + n * log(n)) due to topological sorting, DP, and sorting phase
Space Complexity: O(n + m) for storing graph and auxiliary arrays

Approach:
1. Build a directed graph from dependencies
2. Perform topological sort using Kahn's algorithm
3. For each node, compute the earliest time it can be completed (li) and latest time it can be completed (ri) 
   using dynamic programming
4. Use prefix and suffix maxima to find optimal start time that minimizes total execution time
5. Return minimum completion time over all valid starting points

Key components:
- Topological sorting with in-degree tracking
- Dynamic programming to propagate earliest and latest completion times
- Sorting and two-pass prefix/suffix max computations to minimize total time
*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define SWAP(T, A, B)                                                          \
  do {                                                                         \
    T t = A;                                                                   \
    A = B;                                                                     \
    B = t;                                                                     \
  } while (0)
#define RN 1000005
int64_t ai[RN];
int head[RN], nxt[RN], to[RN];
int ideg[RN], queue[RN];
int64_t li[RN], ri[RN];
int64_t pre[RN], suf[RN];
void run(void) {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &ai[i]);
    li[i] = ai[i];
  }
  int ecnt = 0;
  memset(head, 0, sizeof(int) * (n + 2));
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    nxt[++ecnt] = head[u];
    to[ecnt] = v;
    head[u] = ecnt;
    ideg[v]++;
  }
  memset(ri, 0, sizeof(int64_t) * (n + 2));
  int fr = 1, ba = 0;
  for (int i = 1; i <= n; i++) {
    if (!ideg[i]) {
      queue[++ba] = i;
    }
  }
  while (fr <= ba) {
    int x = queue[fr++];
    for (int i = head[x]; i; i = nxt[i]) {
      int v = to[i];
      ideg[v]--;
      if (!ideg[v]) {
        queue[++ba] = v;
      }
      // Update the latest possible completion time for v based on x
      ri[v] = MAX(ri[v], ri[x] + (ai[v] - ai[x] + k) % k);
    }
  }
  // Sorting phase - used for specific internal logic but may appear to be non-standard
  for (int i = n, flag = 1; i || flag; i = i * 10 / 13) {
    i = i ? (i == 9 || i == 10 ? 11 : i) : 1;
    flag = 0;
    for (int j = 1, k = 1 + i; k <= n; j++, k++) {
      if (li[k] < li[j]) {
        SWAP(int64_t, li[j], li[k]);
        SWAP(int64_t, ri[j], ri[k]);
        flag = 1;
      }
    }
  }
  pre[0] = suf[n + 1] = -1e18;
  for (int i = 1; i <= n; i++) {
    pre[i] = MAX(pre[i - 1], ri[i] - li[i]);
  }
  for (int i = n; i; i--) {
    suf[i] = MAX(suf[i + 1], ri[i] - li[i] + k);
  }
  int64_t ans = suf[1];
  for (int i = 1; i <= n; i++) {
    ans = MIN(ans, MAX(pre[i], suf[i + 1]) + li[i]);
  }
  printf("%lld\n", ans);
}
int main(void) {
  int t;
  scanf("%d", &t);
  while (t--) {
    run();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 1784 C - Monsters (hard version)
// https://codeforces.com/contest/1784/problem/C

/*
 * Problem: C. Monsters (hard version)
 * 
 * Purpose:
 *   This code solves the problem of finding the minimum number of type 1 spells 
 *   needed to kill all monsters in the first k monsters for every prefix k = 1..n.
 * 
 * Techniques:
 *   - Sorting monsters by health
 *   - Greedy algorithm with set operations to simulate spell usage
 *   - Preprocessing and reverse processing to avoid recomputation
 * 
 * Time Complexity: O(n log n) per test case due to sorting and set operations.
 * Space Complexity: O(n) for arrays and sets.
 */
#include <stdio.h>
#include <algorithm>
#include <set>

using namespace std;
const int maxn = 2e5 + 7;
int t, n, a[maxn], q, v[maxn], e[maxn], b[maxn];
long long s[maxn], sum;
set<int> ee;
signed main() {
  scanf("%d", &t);
  while (t--) {
    ee.clear();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), b[i] = a[i];
    sort(a + 1, a + n + 1);
    sum = 0;
    s[0] = 0;
    q = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] > q)
        sum += a[i] - q - 1, q++, v[q]++;
      else
        v[a[i]]++;
    }
    for (int i = 1; i <= q; i++)
      if (v[i] > 1)
        ee.insert(i);
    s[++s[0]] = sum;
    set<int>::iterator op;
    for (int i = n; i > 1; i--) {
      if (b[i] >= q) {
        v[q]--;
        sum -= (b[i] - q);
        while (q && v[q] == 0)
          q--;
      } else {
        v[b[i]]--;
        if (v[b[i]] == 0) {
          op = ee.upper_bound(b[i]);
          while (op != ee.end() && (!ee.empty()) && v[*op] <= 1) {
            ee.erase(*op);
            op = ee.upper_bound(b[i]);
          }
          int ep;
          if (op == ee.end() || ee.empty())
            ep = q;
          else
            ep = *op;
          sum += (ep - b[i]);
          v[ep]--;
          v[b[i]]++;
          while (v[q] == 0 && q)
            q--;
        }
      }
      s[++s[0]] = sum;
    }
    for (int i = 0; i <= n; i++)
      v[i] = 0;
    while (s[0] != 0) {
      printf("%lld ", s[s[0]]);
      s[0]--;
    }
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
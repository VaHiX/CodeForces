// Problem: CF 802 N - April Fools' Problem (medium)
// https://codeforces.com/contest/802/problem/N

/*
 * Problem: April Fools' Problem (medium)
 * Algorithm: Binary search on the answer + greedy with priority queue
 * 
 * Approach:
 * - We binary search on the total cost (t), trying to find the minimum t such that we can prepare and print exactly k problems
 *   with the constraint that preparation must come before printing and both can happen on the same day.
 * - For a fixed t, we use a greedy method:
 *   - For each day i, add its preparation cost (a[i] - t) to a min-heap.
 *   - If there exists a problem in the heap where combining its preparation cost with current day's printing cost (b[i]) is negative,
 *     we take that problem, remove it from heap, and add the printing cost (-b[i]) to heap.
 *   - The number of such taken problems (cnt) is counted.
 *   - We adjust binary search range based on whether cnt equals k.
 * 
 * Time Complexity: O(n * log(1e18)) where n <= 2200
 * Space Complexity: O(n) for storing arrays and priority queue
 */

#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
const int N = 500000;
template <typename Tp>
using min_pq = priority_queue<Tp, vector<Tp>, greater<Tp>>;
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  static int a[N], b[N];
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  for (int i = 0; i < n; i++)
    scanf("%d", &b[i]);
  long long low = 0, hi = 1e18, ans = -1;
  while (low < hi) {
    long long t = (low + hi) / 2;
    min_pq<pair<long long, int>> pq;
    long long sum = 0;
    int cnt = 0;
#if 0
    printf("testing %lld\n", t);
#endif
    for (int i = 0; i < n; i++) {
      pq.push({a[i] - t, 0});  // Push preparation cost adjusted by t, with flag 0
      auto [x, v] = pq.top();
      if (x + b[i] < 0) {      // If taking this problem reduces the cost
        pq.pop();
        sum += x + b[i];       // Accumulate net cost
        cnt += v ^ 1;          // Increment counter if taken (v ^ 1 gives 1 if v=0)
        pq.push({-b[i], 1});   // Add printing cost to heap with flag 1
      }
    }
#if 0
    printf("got %d\n", cnt);
#endif
    if (cnt == k) {
      ans = sum + t * k;      // Final answer is adjusted cost + k * t
      break;
    } else if (cnt < k)
      low = t + 1;            // Need more problems, increase t
    else
      hi = t - 1;             // Too many problems taken, decrease t
  }
  assert(ans != -1);
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
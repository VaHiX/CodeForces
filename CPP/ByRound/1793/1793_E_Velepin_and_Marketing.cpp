// Problem: CF 1793 E - Velepin and Marketing
// https://codeforces.com/contest/1793/problem/E

/*
Algorithm: Greedy + Sorting + Dynamic Programming
Time Complexity: O(n log n + n + q)
Space Complexity: O(n)

Approach:
1. Sort the array 'a' to process elements in increasing order.
2. Use a greedy method to assign books:
   - For each reader, determine how many readers we can satisfy with the book they choose.
   - Use dynamic programming to find optimal assignments.
   - Precompute the maximum number of satisfied readers for different numbers of books.
3. For each query, output the precomputed result.

The algorithm works by:
- Sorting readers by their required number of people (a[i])
- Using dynamic programming to track how many readers can be satisfied with k books
- Storing results in a way that allows for efficient querying

Key steps:
- Sort the array a
- For each element, calculate the number of people that could be satisfied if given k books
- Use DP to compute the maximum readers that can be satisfied for k books
- Preprocess answers for all possible k values
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 3e5 + 5;
int n, q;
int a[N], ans[N], pre[N], dp[N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; i++) {
    if (a[i] > i) {
      ans[1 + n - a[i]] = max(ans[1 + n - a[i]], i);
    } else
      ans[1 + n - i] = max(ans[1 + n - i], i);
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] <= i)
      dp[i] = pre[i - a[i]] + 1;
    else
      dp[i] = -0x3f3f3f3f;
    if (dp[i] >= 1)
      ans[dp[i] + n - i] = max(ans[dp[i] + n - i], i);
    pre[i] = max(pre[i - 1], dp[i]);
  }
  for (int i = n - 1; i >= 1; i--) {
    ans[i] = max(ans[i + 1], ans[i]);
  }
  cin >> q;
  int k;
  for (int i = 1; i <= q; i++) {
    cin >> k;
    cout << ans[k] << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
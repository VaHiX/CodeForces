// Problem: CF 1965 F - Conference
// https://codeforces.com/contest/1965/problem/F

/*
Purpose: This code solves the problem of finding how many ways there are to choose a segment of k consecutive days for a conference, where each day must have an available lecturer and no lecturer can be assigned more than once.

Algorithm:
1. For each day, we store the end day of all lecturers who are available on that day.
2. We process the days from left to right to compute the earliest valid end day (r[i]) for each start day (l[i]), using a priority queue to track availability.
3. A sweep line technique is used to compute valid intervals.
4. Finally, we use a sliding window approach to count the number of valid segments of length k.

Time Complexity: O(n log n + m), where m is the maximum day (2e5), due to processing intervals and using priority queue operations.
Space Complexity: O(m + n), to store intervals and auxiliary arrays.

Techniques:
- Sweep line
- Priority queue
- Sliding window
*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <string>
#include <vector>

using namespace std;
int k, n, m = 2e5, x, y, l[200001], r[200001], a[200001], b[200001],
          ans[200001];
basic_string<int> G[200001];
priority_queue<int, vector<int>, greater<int>> q;
int main() {
  scanf("%d", &k);
  for (int i = 1; i <= k; i++)
    scanf("%d%d", &x, &y), G[x] += y;  // Store end day for each start day
  for (int i = 1; i <= m; i++) {
    for (int j : G[i])
      q.push(j);  // Add all end days for day i to priority queue
    while (q.size() && q.top() < i)
      q.pop();  // Remove end days that are earlier than current day
    if (q.size())
      l[++n] = i, r[n] = q.top(), q.pop();  // Record valid interval
  }
  for (int i = 1; i <= n; i++)
    a[r[i]]++, b[l[i]] = 1;  // Mark interval ends and starts
  for (int i = m, j = m, k = 0; i >= 1; i--) {
    k += a[i];  // Count number of intervals ending at day i
    while (j >= i && k < j - i + 1)  // Shrink window if not enough intervals
      k -= b[j--];
    ans[j - i + 1]++;  // Increment result for segment length
  }
  for (int i = k - 1; i >= 1; i--)
    ans[i] += ans[i + 1];  // Cumulative sum from right to left
  for (int i = 1; i <= k; i++)
    printf("%d\n", ans[i]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
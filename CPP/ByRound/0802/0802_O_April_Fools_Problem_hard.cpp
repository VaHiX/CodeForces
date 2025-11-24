// Problem: CF 802 O - April Fools' Problem (hard)
// https://codeforces.com/contest/802/problem/O

/*
 * Problem: O. April Fools' Problem (hard)
 * 
 * Algorithm: Binary search on the answer combined with a greedy approach using two priority queues.
 * 
 * Time Complexity: O(n * log(max_val)) where max_val is up to 1e9, so effectively O(n * 30) ≈ O(n)
 * Space Complexity: O(n) for the arrays and priority queues storage.
 * 
 * Approach:
 * - We perform binary search on the value of 'mid' (the target sum).
 * - For each 'mid', we simulate a greedy selection process:
 *   - Use a min-heap (pqA) to track small values from (a[i] - mid)
 *   - Use a max-heap (pqB) to track large values from (b[i] - mid)
 *   - At each step, decide whether to pair a[i] with current b[i] or not,
 *     based on which choice gives a better gain (minimizing negative contributions).
 * - After evaluating the number of selected pairs (cnt), adjust binary search bounds:
 *   - If cnt >= k, try smaller 'mid' (move high = mid)
 *   - Else, try larger 'mid' (move low = mid + 1)
 * - Finally, compute result by calling solve(low) and adding 2 * k * low
 *   (as per problem logic involving optimal pairing and adjustment).
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int N = 500005;
int n, k;
int a[N], b[N];
int cnt;
long long solve(int mid) {
  priority_queue<int, vector<int>, greater<int>> pqA;  // Min-heap for a[i] - mid
  priority_queue<int> pqB;                            // Max-heap for b[i] - mid
  cnt = 0;
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    pqA.push(a[i] - mid);
    long long add1 = pqA.top() + b[i] - mid;  // Potential gain if we take a[i], b[i] pair
    long long add2 = 0;
    if (pqB.size())
      add2 = b[i] - mid - pqB.top();  // Potential gain if we use existing b pair
    if (add1 <= add2 && add1 < 0) {
      // Choose pairing with a[i] (take from pqA and push to pqB)
      ans += add1;
      cnt++;
      pqA.pop();
      pqB.push(b[i] - mid);
    } else if (add2 <= add1 && add2 < 0) {
      // Choose pairing with b[i] (pop from pqB and push new b[i])
      ans += add2;
      pqB.pop();
      pqB.push(b[i] - mid);
    }
  }
  return ans;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
    cin >> b[i];
  int low = (int)0, high = (int)1e9;
  while (low < high) {
    int mid = (low + high) >> 1;
    solve(mid);
    if (cnt >= k)
      high = mid;
    else
      low = mid + 1;
  }
  cout << solve(low) + 2LL * k * low << '\n';
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2079 D - Cute Subsequences
// https://codeforces.com/contest/2079/problem/D

/*
 * Problem: Cute Subsequences
 * Purpose: Divide an array into k non-empty subsequences to maximize the sum of their values.
 *          Each subsequence value is defined as max(a[j_m] + m) over all elements in it.
 * Algorithms/Techniques:
 *   - Sliding window with a min-heap (priority queue)
 *   - Greedy approach for optimal partitioning
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */

#include <stddef.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define ll long long
const int nx = 5e5 + 5;
ll n, k, x, sm, ans, a[nx];
priority_queue<ll, vector<ll>, greater<ll>> pq; // Min-heap to maintain smallest elements in current window

int main() {
  cin.tie(NULL)->sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  
  // Initialize the first k-1 elements into the heap and sum
  for (int i = 1; i < k; i++)
    pq.push(a[i]), sm += a[i];

  // Sliding window over the remaining elements
  for (int i = k; i <= n; i++) {
    // Calculate maximum cost for current partition ending at index i
    ans = max(ans, sm + a[i] + i);
    
    // Add current element to sum and push into heap
    sm += a[i];
    pq.push(a[i]);
    
    // Remove the smallest element from window (min-heap top)
    sm -= pq.top();
    pq.pop();
  }
  
  cout << ans;
}


// https://github.com/VaHiX/codeForces/
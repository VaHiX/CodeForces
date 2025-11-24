// Problem: CF 1827 B2 - Range Sorting (Hard Version)
// https://codeforces.com/contest/1827/problem/B2

/*
 * Problem: B2. Range Sorting (Hard Version)
 *
 * Purpose: Calculate the sum of beauty over all subarrays of array a.
 * Beauty of a subarray is defined as the minimum time needed to sort it using range-sort operations.
 * Each operation sorts a subarray in r - l seconds.
 *
 * Algorithm:
 * - For each subarray, the beauty is the number of range-sort operations needed.
 * - Use monotonic stacks to precompute:
 *   - ks[i]: index of the previous element greater than arr[i]
 *   - ys[i]: index of the next element greater than arr[i]
 *   - xs[i]: index of the next element smaller than arr[i]
 * - Then compute contribution of each element to the final result.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tc;
  cin >> tc;
  while (tc--) {
    ll n;
    cin >> n;
    vi arr(n);
    for (auto &x : arr)
      cin >> x;
    ll ans = 0;
    // Compute total possible subarrays and initialize ans with that
    for (int i = 1; i < n; i++)
      ans += i * (n - i);
    
    // ks[i] stores index of previous element greater than arr[i]
    vi ks(n);
    // ys[i] stores index of next element greater than arr[i]
    vi ys(n);
    stack<ll> yst;
    // Process from right to left to find next greater element
    for (int i = n - 1; i >= 0; i--) {
      while (!yst.empty() && arr[yst.top()] > arr[i])
        yst.pop();
      ys[i] = yst.empty() ? n : yst.top();
      yst.emplace(i);
    }
    stack<ll> kst;
    // Process from left to right to find previous greater element
    for (int i = 0; i < n; i++) {
      while (!kst.empty() && arr[kst.top()] > arr[i])
        kst.pop();
      ks[i] = kst.empty() ? -1 : kst.top();
      kst.emplace(i);
    }
    // xs[i] stores index of next element smaller than arr[i]
    vi xs(n, -1);
    stack<ll> waitx, readyx;
    // Process from right to left to find next smaller element
    for (int i = n - 1; i >= 0; i--) {
      while (!readyx.empty() && arr[i] > arr[readyx.top()]) {
        xs[readyx.top()] = i;
        readyx.pop();
      }
      while (!waitx.empty() && arr[i] < arr[waitx.top()]) {
        readyx.emplace(waitx.top());
        waitx.pop();
      }
      waitx.emplace(i);
    }
    // Subtract invalid cases from ans
    for (int i = 0; i < n; i++) {
      ans -= (ks[i] - xs[i]) * (ys[i] - i);
    }
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
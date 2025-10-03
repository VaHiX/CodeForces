// Problem: CF 2149 E - Hidden Knowledge of the Ancients
// https://codeforces.com/contest/2149/problem/E

/*
E. Hidden Knowledge of the Ancients
Algorithm: Sliding window technique with frequency map
Time Complexity: O(n) per test case, where n is the size of the array
Space Complexity: O(n) for the frequency map and input array

The problem asks to count the number of subarrays that contain exactly k distinct numbers 
and whose length is between l and r (inclusive).

Approach:
- Use a helper function 'help' which counts the number of valid subarrays with at most K distinct elements
  and length at most L.
- The key idea is to use two pointers (sliding window) to maintain a window with at most K distinct elements.
- For each valid window, we add min(window_size, L) to the result.

To compute the final answer for a given range [l,r]:
- f1 = count of subarrays with exactly k distinct numbers and length <= r
- f2 = count of subarrays with exactly k distinct numbers and length <= l - 1
- f3 = count of subarrays with exactly k - 1 distinct numbers and length <= r
- f4 = count of subarrays with exactly k - 1 distinct numbers and length <= l - 1
- Result = (f1 - f2) - (f3 - f4)

This effectively calculates the number of subarrays with exactly k distinct elements and length in [l, r].
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using ll = long long;

// Helper function to count subarrays with at most K distinct numbers and length <= L
ll help(vector<ll> &arr, int K, int L) {
  map<ll, int> freq; // Frequency map to maintain count of elements in current window
  int i = 0;         // Left pointer of sliding window
  ll ans = 0;        // Result counter

  for (int j = 0; j < (int)arr.size(); j++) {
    freq[arr[j]]++; // Expand window by including arr[j]

    // Shrink window until number of distinct elements <= K
    while (freq.size() > K) {
      if (--freq[arr[i]] == 0)
        freq.erase(arr[i]); // Remove element from frequency map if count drops to 0
      i++; // Move left pointer
    }

    // Add number of valid subarrays ending at j
    ans += min(j - i + 1, L);
  }

  return ans;
}

void solve() {
  int n, k, l, r;
  cin >> n >> k >> l >> r;

  vector<ll> arr(n);
  for (auto &a : arr)
    cin >> a;

  // Compute required counts using helper function
  ll f1 = help(arr, k, r);         // Valid subarrays with exactly k distinct elements and len <= r
  ll f2 = help(arr, k, l - 1);     // Valid subarrays with exactly k distinct elements and len <= l-1
  ll f3 = help(arr, k - 1, r);     // Valid subarrays with exactly k-1 distinct elements and len <= r
  ll f4 = help(arr, k - 1, l - 1); // Valid subarrays with exactly k-1 distinct elements and len <= l-1

  // Final answer: difference of ranges gives count in [l, r]
  ll ans = (f1 - f2) - (f3 - f4);
  cout << ans << endl;
  return;
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/
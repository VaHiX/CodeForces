// Problem: CF 2064 F - We Be Summing
// https://codeforces.com/contest/2064/problem/F

/*
F. We Be Summing
Algorithms/Techniques: 
- Using monotonic stacks to precompute left and right boundaries for elements
- Two-pointer technique with segment-like updates using arrays as frequency counters
- Efficient counting of valid subarrays by maintaining min/max counts in a sliding window fashion

Time Complexity: O(n) amortized per test case due to the use of stack and two-pass scanning.
Space Complexity: O(n) for storing auxiliary arrays and stack structures.

Problem:
Count the number of epic subarrays, where an epic subarray is one with partition point i such that 
min(b[0..i]) + max(b[i+1..m-1]) = k.

Input:
- t test cases
- For each case: n (length), k (target sum)
- Array a of size n

Output:
Number of epic subarrays.
*/

#include <string.h>
#include <array>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define ar array
const int mxN = 2e5;
int t, n, k, a[mxN], l[mxN], r[mxN], mnb[mxN], mxb[mxN];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> k, k -= 2; // Adjusting k for indexing
    for (int i = 0; i < n; ++i) {
      cin >> a[i], --a[i]; // Convert to 0-based indexing
      l[i] = i - 1;        // Initialize left boundary to previous element
      while (~l[i] && a[l[i]] > a[i]) // While we have a larger element to the left...
        l[i] = l[l[i]]; // Jump to the next smaller element using previously calculated boundaries
    }
    for (int i = n - 1; ~i; --i) {
      r[i] = i + 1;           // Initialize right boundary to next element
      while (r[i] < n && a[r[i]] < a[i]) // While we have a smaller element to the right...
        r[i] = r[r[i]];   // Jump to the next larger element using previously calculated boundaries
    }
    memset(mnb, 0, 4 * n); // Reset min freq array
    memset(mxb, 0, 4 * n); // Reset max freq array
    ll ans = 0;
    
    // Lambda function to update min frequency and compute contributions
    auto addmn = [&](int i, int x) {
      mnb[i] += x; // Add x elements with value i to the frequency of mins
      if (0 <= k - i && k - i < n)
        ans += (ll)x * mxb[k - i]; // Contribute based on matches from max array
    };
    
    // Lambda function to update max frequency and compute contributions
    auto addmx = [&](int i, int x) {
      mxb[i] += x; // Add x elements with value i to the frequency of maxes
      if (0 <= k - i && k - i < n)
        ans += (ll)x * mnb[k - i]; // Contribute based on matches from min array
    };
    
    vector<ar<int, 4>> rs; // Not used but declared
    
    {
      int i = 0;
      while (i < n) {
        addmx(a[i], r[i] - i); // Add to max bucket for elements from i to r[i]-1
        i = r[i]; // Jump to the end of current segment
      }
    }
    
    for (int i = 0; i < n - 1; ++i) {
      int j1 = i - 1;
      while (~j1 && a[j1] > a[i]) { // Backtrack through elements greater than a[i]
        mnb[a[j1]] -= j1 - l[j1]; // Remove contribution of element
        j1 = l[j1]; // Move back to next smaller element's left boundary
      }
      mxb[a[i]] -= r[i] - i; // Reduce count for current a[i] in max bucket
      addmn(a[i], i - j1);   // Add to min bucket for contribution of current range
      int j2 = i + 1;
      while (j2 < n && a[j2] < a[i]) { // Forward scan to smaller elements
        addmx(a[j2], r[j2] - j2); // Add to max buckets
        j2 = r[j2]; // Move beyond this segment
      }
    }
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 689 D - Friends and Subsequences
// https://codeforces.com/contest/689/problem/D

/*
D. Friends and Subsequences
Algorithm: Two Pointers with Monotonic Deques
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks us to count how many subarrays [l, r] satisfy that the maximum element in a[l..r] equals the minimum element in b[l..r].

We use two deques (mxq and mnq) to maintain indices of elements in a and b respectively such that their values are in decreasing (for max) and increasing (for min) order.

For each right pointer r:
  - Add current index to deques maintaining monotonicity.
  - Shrink the left pointer until max(a[l..r]) <= min(b[l..r]).
  - Count valid subarrays where max(a[l..r]) == min(b[l..r]).
*/

#include <cstdio>
#include <deque>
#include <vector>
typedef long long ll;
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n), b(n);
  for (int p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  for (int p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }
  ll cnt(0);
  long left(0);
  std::deque<long> mxq, mnq;
  for (int p = 0; p < n; p++) {
    // Maintain decreasing order in mxq (max)
    while (!mxq.empty() && a[mxq.back()] <= a[p]) {
      mxq.pop_back();
    }
    // Maintain increasing order in mnq (min)
    while (!mnq.empty() && b[mnq.back()] >= b[p]) {
      mnq.pop_back();
    }
    mxq.push_back(p);
    mnq.push_back(p);
    
    // Shrink window from left while max(a[left..p]) > min(b[left..p])
    while (left <= p && a[mxq.front()] > b[mnq.front()]) {
      ++left;
      // Remove elements out of current window
      while (!mxq.empty() && mxq.front() < left) {
        mxq.pop_front();
      }
      while (!mnq.empty() && mnq.front() < left) {
        mnq.pop_front();
      }
    }
    
    // Check if valid interval exists where max(a) == min(b)
    if (!mxq.empty() && !mnq.empty() && a[mxq.front()] == b[mnq.front()]) {
      cnt += (mxq.front() < mnq.front() ? mxq.front() : mnq.front()) - left + 1;
    }
  }
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/
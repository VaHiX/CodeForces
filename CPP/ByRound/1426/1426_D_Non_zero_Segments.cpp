// Problem: CF 1426 D - Non-zero Segments
// https://codeforces.com/contest/1426/problem/D

#include <cstdio>
#include <set>
typedef long long ll;
/*
D. Non-zero Segments
Algorithm: Prefix Sum with Set
Time Complexity: O(n log n)
Space Complexity: O(n)

The problem asks to find the minimum number of integers to insert into an array 
such that no subsegment has a sum of zero. We use prefix sums to detect zero-sum 
subsegments. If a prefix sum repeats, it means there's a subsegment with sum zero.

We maintain a set of prefix sums. As we iterate through the array:
- Compute the cumulative sum (prefix sum).
- Check if this prefix sum has been seen before.
  - If yes, it means we found a zero-sum subsegment.
    - Increment the count of insertions needed.
    - Clear the set and start fresh with a new segment.
  - Insert current prefix sum into set.
This ensures we detect and avoid all zero-sum subsegments with minimal insertions.
*/
int main() {
  ll n;
  scanf("%lld", &n);
  std::set<ll> s; // Set to store prefix sums
  s.insert(0);    // Initialize with 0 (empty prefix)
  ll acc(0), cnt(0); // acc: current prefix sum, cnt: number of insertions
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    acc += x; // Update prefix sum
    if (s.count(acc)) { // If prefix sum repeats, we found zero-sum subsegment
      s.clear();        // Start fresh for new segment
      s.insert(0);      // Insert 0 for new segment's empty prefix
      ++cnt;            // Increment insertion count
      acc = x;          // Reset prefix sum to current element
    }
    s.insert(acc); // Insert current prefix sum
  }
  printf("%lld\n", cnt);
  return 0;
}

// https://github.com/VaHiX/codeForces/
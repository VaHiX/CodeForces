// Problem: CF 2060 C - Game of Mathletes
// https://codeforces.com/contest/2060/problem/C

/*
C. Game of Mathletes
Algorithm: Two Pointers Technique
Time Complexity: O(n log n) per test case due to sorting, O(1) for the two-pointer traversal
Space Complexity: O(n) for the vector storage

This problem involves a game where Alice and Bob pick numbers optimally from a list,
trying to form pairs that sum up to k. Alice wants to minimize the score (number of valid pairs),
while Bob wants to maximize it. Using a greedy two-pointer approach on a sorted array allows
us to find the maximum number of such pairs efficiently.

The algorithm sorts the vector first, then uses two pointers (left and right) to scan for 
pairs that sum to k. If the sum is equal to k, we increment the count and move both pointers.
If it's less than k, move left pointer forward; otherwise, move right pointer backward.
This ensures optimal pairing under adversarial play conditions.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    sort(v.begin(), v.end()); // Sort the array to apply two-pointer technique
    long left(0), right(n - 1), cnt(0);
    while (left < right) {
      long sum = v[left] + v[right];
      if (sum == k) {
        ++cnt;
        ++left;   // Move both pointers when a valid pair is found
        --right;
      } else if (sum < k) {
        ++left;   // If sum is too small, increase left to get larger values
      } else if (sum > k) {
        --right;  // If sum is too large, decrease right to get smaller values
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/
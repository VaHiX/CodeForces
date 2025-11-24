// Problem: CF 1798 D - Shocking Arrangement
// https://codeforces.com/contest/1798/problem/D

#include <cstdio>
#include <vector>
/*
 * Code Purpose:
 * This program attempts to rearrange an array of integers (with sum 0) such that
 * the maximum absolute subarray sum is strictly less than the difference between
 * the maximum and minimum elements of the original array.
 *
 * Approach:
 * - Separate positive and negative numbers.
 * - Use a greedy strategy: alternate between picking from positive and negative lists,
 *   always picking the element which keeps the current prefix sum non-positive if possible.
 * - This is based on the idea that if we can maintain a running sum that doesn't go too far
 *   into the positive or negative side, we can bound the maximum subarray sum.
 *
 * Time Complexity: O(n log n), due to sorting of positive and negative elements.
 * Space Complexity: O(n), to store the lists of positives and negatives, and the output array.
 */
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> neg, pos;
    long mx(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x >= 0) {
        pos.push_back(x);
      } else {
        neg.push_back(x);
      }
      mx = (mx > x ? mx : x);  // Track the maximum element
    }
    if (!mx) {
      puts("No");  // If max element is 0, no rearrangement will help
      continue;
    }
    puts("Yes");
    std::vector<long> ans;
    long long cs(0);  // Running prefix sum
    for (long p = 0; p < n; p++) {
      if (cs <= 0) {
        // If prefix sum is non-positive, pick from positive to keep it balanced
        ans.push_back(pos.back());
        pos.pop_back();
      } else {
        // If prefix sum is positive, pick from negative to pull it back down
        ans.push_back(neg.back());
        neg.pop_back();
      }
      cs += ans.back();  // Update running sum
    }
    for (long x : ans) {
      printf("%ld ", x);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 873 D - Merge Sort
// https://codeforces.com/contest/873/problem/D

/*
 * Problem: D. Merge Sort
 * 
 * Purpose: 
 *   Given a permutation of size n and a target number of merge sort calls k,
 *   construct a permutation such that exactly k merge sort calls are made.
 *   
 * Algorithm:
 *   - Recursively split the array into left and right halves
 *   - Distribute the k calls between left and right subarrays
 *   - For each recursive call, check if it's possible to distribute k calls
 *   - When splitting, ensure we don't split into already sorted segments
 *   - If there's no valid split, return false
 *
 * Time Complexity: O(n * log n)
 *   - The recursive function builds a call tree with depth up to log n
 *   - For each level, we do O(n) work to split and merge vectors
 *   - The total number of operations is bounded by O(n * log n)
 *
 * Space Complexity: O(n * log n)
 *   - Each recursive call stores the split arrays
 *   - At maximum depth log n, we store up to n elements per level
 *   - Total space usage is O(n * log n)
 */

#include <cstdio>
#include <vector>
bool f(std::vector<long> &a, long k) {
  // Base case: if array size is 1 or less, but k > 1, impossible to have k calls
  if (a.size() <= 1 && k > 1) {
    return false;
  }
  // If k is impossible to achieve, return false (even numbers not allowed for valid splits)
  if (k < 0 || k % 2 == 0) {
    return false;
  }
  // Decrement k since we're making one merge sort call at this level
  k--;
  // If k becomes 0, we've assigned all calls
  if (k == 0) {
    return true;
  }
  // Split the array into left and right parts
  std::vector<long> lv, rv;
  for (long p = 0; p < a.size(); p++) {
    if (p < (a.size() + 1) / 2) {
      lv.push_back(a[p]); // Add to left half
    } else {
      rv.push_back(a[p]); // Add to right half
    }
  }
  // Calculate how many calls to assign to left and right
  long lk(0), rk(0);
  if ((k / 2) & 1) {
    // Distribute evenly among left and right
    lk = rk = k / 2;
  } else {
    // If odd division, assign one more to left
    lk = (k / 2) + 1;
    rk = (k / 2) - 1;
  }
  // Recursively solve for left and right parts
  bool lp = f(lv, lk);
  bool rp = f(rv, rk);
  // If either part fails, return false
  if (!lp || !rp) {
    return false;
  }
  // Combine results in order to build final array
  std::vector<long> b;
  for (long p = 0; p < rv.size(); p++) {
    b.push_back(rv[p]);
  }
  for (long p = 0; p < lv.size(); p++) {
    b.push_back(lv[p]);
  }
  a = b; // Update the original array
  return true;
}
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  // Initialize the array with values [1, 2, ..., n]
  for (long p = 0; p < n; p++) {
    a[p] = p + 1;
  }
  // Attempt to construct a permutation that requires exactly k calls
  bool possible = f(a, k);
  // Output result
  if (possible) {
    for (long p = 0; p < a.size(); p++) {
      printf("%ld ", a[p]);
    };
    puts("");
  } else {
    puts("-1");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
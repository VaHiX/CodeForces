// Problem: CF 978 A - Remove Duplicates
// https://codeforces.com/contest/978/problem/A

/*
 * Problem: Remove Duplicates
 * Algorithm: Iterate from right to left, use a boolean array to track seen elements.
 *            Only add an element to the result if it hasn't been seen from the right.
 *            Reverse the final result to maintain original order.
 *
 * Time Complexity: O(n + max_value), where n is the array length and max_value is the maximum element (1000).
 * Space Complexity: O(max_value + n), for the boolean array and result vector.
 */

#include <cstdio>
#include <vector>
int main() {
  const long N = 1007; // Maximum possible value + 1 to cover all elements up to 1000
  long n;
  scanf("%ld", &n);
  std::vector<bool> already(N, 0); // Track which values have been seen
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b; // Store unique elements in reverse order (from right)
  for (long p = n - 1; p >= 0; p--) {
    if (already[a[p]]) { // If already seen from the right, skip
      continue;
    }
    already[a[p]] = 1; // Mark as seen
    b.push_back(a[p]); // Add to result
  }
  printf("%ld\n", b.size()); // Print number of unique elements
  for (long p = b.size() - 1; p >= 0; p--) {
    printf("%ld ", b[p]); // Print in correct order (reverse of b)
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/
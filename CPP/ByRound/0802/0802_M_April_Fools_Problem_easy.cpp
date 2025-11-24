// Problem: CF 802 M - April Fools' Problem (easy)
// https://codeforces.com/contest/802/problem/M

/*
 * Code Purpose: This program finds the sum of the k smallest elements in a given sequence of n positive integers.
 * 
 * Algorithm: 
 *   - Read n and k from input.
 *   - Read the sequence of n integers into a vector.
 *   - Sort the vector in ascending order.
 *   - Sum the first k elements of the sorted vector.
 *   - Output the result.
 * 
 * Time Complexity: O(n log n) due to sorting.
 * Space Complexity: O(n) for storing the vector of integers.
 */
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());  // Sort the array in ascending order
  long sum(0);
  for (long p = 0; p < k; p++) {
    sum += a[p];  // Add the first k elements (smallest ones)
  }
  printf("%ld\n", sum);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
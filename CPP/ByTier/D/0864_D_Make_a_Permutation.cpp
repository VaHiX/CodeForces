// Problem: CF 864 D - Make a Permutation!
// https://codeforces.com/contest/864/problem/D

/*
 * Problem: Make a Permutation!
 * 
 * Purpose: Given an array of integers from 1 to n, transform it into a permutation
 *          with minimal changes. If multiple solutions exist, choose the lexicographically
 *          smallest one.
 * 
 * Algorithm:
 * 1. Count occurrences of each number in the array.
 * 2. Iterate through the array from left to right:
 *    - If current element's count is 1 or if it can be replaced with a smaller unused number,
 *      keep it or mark it as used.
 *    - Otherwise, replace it with the smallest unused number and increment the change count.
 * 3. Output the number of changes and the resulting permutation.
 * 
 * Time Complexity: O(n), each element is processed at most once, and the loop for finding
 *                  the next unused number is amortized O(n) over all iterations.
 * Space Complexity: O(n), for the arrays and vectors used to track counts and usage.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n, 0), b(n + 1, 0); // a: input array, b: count of each number
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    ++b[a[p]]; // Count occurrences of each number
  }
  std::vector<bool> found(n + 1, 0); // Tracks if a number is used in the result
  long ind(1), count(0); // ind: smallest unused number, count: number of changes needed
  while (b[ind] > 0) {
    ++ind; // Find the first unused number
  }
  for (long p = 0; p < n; p++) {
    long u = a[p];
    // If the number appears only once or we can replace it with a smaller unused number
    if ((b[u] <= 1) || ((ind > u) && (!found[u]))) {
      found[u] = true; // Mark as used
    } else {
      // Replace this number with the smallest unused number
      ++count;
      --b[u]; // Decrease count of old number
      b[ind] = 1; // Mark new number as used
      found[ind] = true;
      a[p] = ind; // Update the array
      while (b[ind] > 0) {
        ++ind; // Find next unused number
      }
    }
  }
  printf("%ld\n", count);
  for (long p = 0; p < n; p++) {
    printf("%ld ", a[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/
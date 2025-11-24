// Problem: CF 847 B - Preparing for Merge Sort
// https://codeforces.com/contest/847/problem/B

/*
 * Code Purpose: 
 * This program implements an algorithm to decompose an array into one or more
 * increasing subsequences based on a specific greedy procedure. The procedure
 * processes elements from left to right and assigns each element to the leftmost
 * subsequence where it maintains the increasing property.
 * 
 * Algorithm:
 * - Use a vector of vectors 'f' to store the subsequences.
 * - Use a vector 'h' to keep track of the last element of each subsequence.
 * - For each new element:
 *   - If it's larger than the last element of the last subsequence, start a new subsequence.
 *   - Otherwise, find the leftmost subsequence where this element can be placed
 *     (using binary search on 'h') and append it there.
 * 
 * Time Complexity: O(n log n) - Each element is processed once, and binary search is O(log n)
 * Space Complexity: O(n) - Storing the subsequences and auxiliary arrays
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::vector<long>> f;  // Stores the resulting increasing subsequences
  std::vector<long> h;              // Stores the last element of each subsequence
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    if (h.size() <= 0 || a < h.back()) {
      // If a is smaller than the last element of last subsequence,
      // start a new subsequence
      h.push_back(a);
      f.push_back(std::vector<long>(1, a));
    } else {
      // Binary search to find the correct subsequence to append 'a' to
      long left(0), right(h.size() - 1), pos(h.size() - 1);
      while (left <= right) {
        long mid = (left + right) / 2;
        if (h[mid] <= a) {
          // 'a' can be placed in subsequence 'mid', try to find a leftmost one
          pos = mid;
          right = mid - 1;
        } else {
          // 'a' is smaller than h[mid], look in right half
          left = left + 1;
        }
      }
      h[pos] = a; // Update the last element of the chosen subsequence
      f[pos].push_back(a); // Add 'a' to the chosen subsequence
    }
  }
  for (long p = 0; p < f.size(); p++) {
    for (long q = 0; q < f[p].size(); q++) {
      printf("%ld ", f[p][q]);
    };
    puts(""); // Print each subsequence on a new line
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2024 C - Concatenation of Arrays
// https://codeforces.com/contest/2024/problem/C

/*
 * Problem: Concatenation of Arrays
 * 
 * Task: Given n arrays of length 2, concatenate them into a single array of length 2n
 * such that the number of inversions is minimized.
 * 
 * Approach:
 * - For each array [a, b], calculate the sum a + b and store it with the original array.
 * - Sort the arrays based on the sum a + b in ascending order.
 * - Output the elements of the sorted arrays in order.
 * 
 * Key Insight:
 * - By sorting the arrays by sum, we minimize the chances of large elements appearing before smaller ones,
 *   which reduces inversions.
 * 
 * Time Complexity: O(n log n) due to sorting.
 * Space Complexity: O(n) for storing the pairs.
 * 
 * Algorithms/Techniques:
 * - Sorting with custom comparator (by sum of elements)
 * - Greedy strategy to minimize inversions
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Vector to store pairs: (sum of elements, (first element, second element))
    std::vector<std::pair<long, std::pair<long, long>>> v(n);
    for (long p = 0; p < n; p++) {
      long a, b;
      scanf("%ld %ld", &a, &b);
      v[p].first = a + b;          // Store sum for sorting
      v[p].second.first = a;       // Store first element
      v[p].second.second = b;      // Store second element
    }
    sort(v.begin(), v.end());      // Sort by sum of elements
    for (long p = 0; p < n; p++) {
      printf("%ld %ld ", v[p].second.first, v[p].second.second); // Output the elements in order
    }
    puts("");                      // Print newline after each test case
  }
}


// https://github.com/VaHiX/CodeForces/
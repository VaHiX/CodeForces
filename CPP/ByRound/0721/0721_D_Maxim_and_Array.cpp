// Problem: CF 721 D - Maxim and Array
// https://codeforces.com/contest/721/problem/D

/*
Algorithm: Greedy with Set
Approach:
- The goal is to minimize the product of the array elements by applying at most k operations.
- Each operation allows us to add or subtract x from any element.
- To minimize the product:
  - If the current product is positive, we'd like to make it negative (by flipping the sign of one element).
  - If the current product is negative, we'd like to make it more negative (by increasing the absolute value of the element with the smallest absolute value).
- We maintain a set of elements sorted by absolute value to always act on the element with the smallest absolute value.
- We track the sign of the product using a variable 'z' (1 for positive, -1 for negative).
- In each step, we select the element with the smallest absolute value, adjust it to reduce the overall product (by making the sign of the product flip or increasing the magnitude of a negative element).
Time Complexity: O(n log n + k log n) due to sorting and k operations on a set.
Space Complexity: O(n) for storing the array and the set.
*/

#include <bits/std_abs.h>
#include <stdint.h>
#include <stdio.h>
#include <set>
#include <vector>
#include <utility>

int main() {
  int64_t n, k, x;
  scanf("%lld %lld %lld", &n, &k, &x);
  std::vector<int64_t> a(n);
  std::set<std::pair<int64_t, int64_t>> s;
  int64_t z(1); // Tracks the sign of the product (1 for positive, -1 for negative)
  for (int64_t p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
    if (a[p] < 0) {
      z = -z; // Flip sign of product if the current element is negative
    }
    s.insert(std::make_pair(std::abs(a[p]), p)); // Insert absolute value and index into set
  }
  for (int64_t p = 0; p < k; p++) {
    int64_t pos = s.begin()->second; // Get index of element with smallest absolute value
    s.erase(s.begin()); // Remove the element with smallest absolute value from set
    
    if (a[pos] < 0) {
      z = -z; // Update sign if the element was negative
    }
    
    // If product is positive, subtract x to make it more negative (if possible)
    // If product is negative, add x to make it more negative (if possible)
    if (z > 0) {
      a[pos] -= x;
    } else {
      a[pos] += x;
    }
    
    s.insert(std::make_pair(std::abs(a[pos]), pos)); // Reinsert updated element into set
    
    if (a[pos] < 0) {
      z = -z; // Update sign if new value is negative
    }
  }
  for (int64_t p = 0; p < n; p++) {
    printf("%lld ", a[p]); // Output the final array
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
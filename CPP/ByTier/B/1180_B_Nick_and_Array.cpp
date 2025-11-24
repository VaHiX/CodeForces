// Problem: CF 1180 B - Nick and Array
// https://codeforces.com/contest/1180/problem/B

#include <cstdio>
#include <vector>
// ========================================================================
// Problem: B. Nick and Array
// Purpose: Given an array of integers, apply the operation a[i] := -a[i] - 1
//          to maximize the product of all elements.
// Algorithm: Greedily flip negative numbers to positive (if possible), 
//            but if there are an odd number of elements, ensure that 
//            the smallest absolute value element is flipped to make the
//            overall product maximized.
// Time Complexity: O(n)
// Space Complexity: O(n)
// ========================================================================
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n); // Read input array
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  // First pass: flip all non-negative numbers to negative
  for (long p = 0; p < n; p++) {
    if (a[p] < 0) {
      continue; // Skip negative numbers
    }
    a[p] = -a[p] - 1; // Flip positive number to negative
  }
  // If n is odd, we must ensure final product is maximum
  // so flip the smallest element (in absolute value) if necessary
  if (n % 2) {
    long mn(1e9); // Initialize minimum value to a large number
    for (long p = 0; p < n; p++) {
      mn = (mn < a[p]) ? mn : a[p]; // Find minimum element in array
    }
    for (long p = 0; p < n; p++) {
      if (a[p] == mn) {
        a[p] = -a[p] - 1; // Flip the smallest element to maximize product
        break;
      }
    }
  }
  // Print result array
  for (long p = 0; p < n; p++) {
    printf("%ld ", a[p]);
  }
  puts("");
  return 0;
}

// https://github.com/VaHiX/codeForces/
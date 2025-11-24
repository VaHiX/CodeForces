// Problem: CF 2123 E - MEX Count
// https://codeforces.com/contest/2123/problem/E

/*
E. MEX Count
Algorithm: Using difference array technique to count occurrences of MEX values after removing k elements.
Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n) for storing frequency and difference arrays.

The algorithm works by:
1. Counting frequency of each element in the array.
2. Using a difference array to track how many times each MEX value can be achieved
   after removing exactly k elements for all k from 0 to n.
3. For each possible MEX value, we determine how many valid subarrays exist
   such that removing exactly k elements results in that MEX.

This approach uses the idea that MEX of an array is determined by which numbers (0 to n) 
are present. By maintaining a frequency count and difference array, we efficiently compute
the number of different MEX values possible for each k.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), ans(n + 1), diff(n + 2), freq(n + 2);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++freq[x]; // Count frequency of each number
    }
    for (long p = 0; p <= n; p++) {
      ++diff[freq[p]];         // Increment start of interval
      --diff[n - p + 1];       // Decrement end+1 of interval
      if (!freq[p]) {
        break;                 // No more elements to process
      }
    }
    long cs(0);
    for (long p = 0; p <= n; p++) {
      cs += diff[p];           // Prefix sum to get actual counts
      printf("%ld ", cs);      // Print results
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 1807 G2 - Subsequence Addition (Hard Version)
// https://codeforces.com/contest/1807/problem/G2

/*
G2. Subsequence Addition (Hard Version)
Algorithm: Greedy + Sorting
Time Complexity: O(n log n) per test case due to sorting; overall O(n log n) for all test cases
Space Complexity: O(n) for storing the array

The problem asks whether a given array can be obtained from an initial array [1] by repeatedly adding 
the sum of any subsequence to the array. 

Key idea:
- Start with array [1]. 
- If we sort the array, then for each element, it should be possible to form it using previously 
  added elements (sum of subset of previous elements).
- If at any point the current element is greater than the sum of all previously processed elements, 
  return "NO". Else keep updating the sum.
- Also, if the first element in the sorted array is not 1, we can't proceed since it starts from [1].
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n, 0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end()); // Sort the array to process elements in increasing order
    bool ans(a[0] == 1);      // First element must be 1 for valid sequence
    long long s(1);           // Sum of processed elements starting with 1
    for (long p = 1; ans && p < n; p++) {
      if (s < a[p]) {         // If sum of previous elements is less than current element, not possible
        ans = false;
      } else {
        s += a[p];            // Add current element to the running sum
      }
    }
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 2059 B - Cost of the Array
// https://codeforces.com/contest/2059/problem/B

/*
B. Cost of the Array
Algorithm: Greedy approach to minimize the cost of array b after optimal partitioning.
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array

The problem involves splitting an array into exactly k subarrays, then concatenating 
subarrays with even indices (2nd, 4th, ..., k-th) into a new array b, and appending 0 to it.
The cost is defined as the minimum index i where b[i] != i.

Key insight: To minimize cost, we want b[i] == i for as many initial indices as possible.
We analyze two cases based on the relationship between n and k:
1. When n == 2 * k: We try to make first half consistent with their expected values.
2. When n != 2 * k: We check the beginning of the array for consistency.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    k /= 2; // half of k represents number of even-indexed subarrays
    long res(k + 1); // default result is the size of even-indexed portion plus one due to appended 0
    
    if (n == 2 * k) {
      // Case 1: n equals 2*k, meaning each subarray has length 1, so even indexed 
      // elements are a[1], a[3], ..., a[n-1]
      for (int p = 1; p < n; p += 2) {
        if (a[p] == (p + 1) / 2) {
          continue; // Keep checking if values match expected index in b
        }
        res = (p + 1) / 2; // Found first mismatch, update cost
        break;
      }
    } else {
      // Case 2: n > 2*k, there's more room to play with. To minimize cost,
      // we check if early elements are all 1 (optimal for minimizing b[1])
      res = 2; 
      for (int p = 1; p <= n - 2 * k + 1; p++) {
        if (a[p] != 1) {
          res = 1; // If any element != 1, set cost to 1
          break;
        }
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/
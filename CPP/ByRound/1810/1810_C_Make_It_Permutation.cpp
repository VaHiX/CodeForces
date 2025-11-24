// Problem: CF 1810 C - Make It Permutation
// https://codeforces.com/contest/1810/problem/C

/*
Code Purpose:
This program finds the minimum cost to transform an array into a permutation of positive integers.
The allowed operations are:
1. Remove an element (cost = c)
2. Insert an element (cost = d)
The goal is to find the minimal total cost to make the array a valid permutation.

Approach:
1. Sort the array to process elements in order.
2. For each unique element, calculate the cost of keeping it and inserting missing numbers.
3. Try all possible valid permutation lengths (1 to N) by counting unique elements and calculating insertion/removal costs.
4. The cost formula for a permutation of length k:
   - Remove all elements not in the first k unique elements.
   - Insert missing numbers from 1 to k to fill the permutation.
   - Cost = (N - k) * c + (k - count_unique) * d

Time Complexity: O(N * log(N)) per test case, due to sorting.
Space Complexity: O(N) for storing the array.
*/

#include <stdio.h>
#include <algorithm>

#define int long long
using namespace std;
int all[100005];
signed main() {
  int T, N, x, y, ans = 8e18, a, b, c, i, j, k;
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld %lld %lld", &N, &x, &y); // Read N, c, d
    for (i = 0; i < N; i++)
      scanf("%lld", &all[i]); // Read array elements
    sort(all, all + N); // Sort the array to handle unique elements
    a = b = c = 0;
    ans = x * N + y; // Initial cost: remove all elements and insert one
    for (i = 0; i < N; i++) {
      // Count unique elements
      if (i == 0 || all[i] != all[i - 1]) {
        a++; // Increment unique count
        // Calculate cost for making a permutation of length a
        // Remove all remaining elements and insert missing elements
        ans = min(ans, x * (N - a) + y * (all[i] - a));
      }
    }
    printf("%lld\n", ans); // Output minimum cost
  }
}


// https://github.com/VaHiX/CodeForces/
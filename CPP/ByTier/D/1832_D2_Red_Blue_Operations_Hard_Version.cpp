// Problem: CF 1832 D2 - Red-Blue Operations (Hard Version)
// https://codeforces.com/contest/1832/problem/D2

/*
 * Problem: D2. Red-Blue Operations (Hard Version)
 *
 * Purpose:
 *   Given an array of integers, initially all elements are red. We can apply
 * operations where each operation i either increases (if red) or decreases (if
 * blue) an element by i. The goal is to maximize the minimum element in the
 * array after exactly k operations.
 *
 * Approach:
 *   - Preprocess the array to compute minimum possible values after applying
 * first n operations.
 *   - For query k:
 *     - If k <= n, use precomputed values.
 *     - Otherwise, compute based on how many operations beyond n are applied
 * and balance the gain from operations with the initial array sum.
 *
 * Time Complexity: O(n log n + q)
 *   - Sorting: O(n log n)
 *   - Preprocessing: O(n)
 *   - Each query: O(1)
 *
 * Space Complexity: O(n)
 *   - Storage for the input array and auxiliary array `mn`
 *
 * Techniques:
 *   - Sorting
 *   - Prefix minimization
 *   - Mathematical optimization for large k values
 *
 * Algorithms:
 *   - Greedy strategy with prefix minimum calculation
 *   - Arithmetic progression for sum calculation
 *   - Binary search or direct calculation for large k cases
 */

#include <algorithm>
#include <iostream>
#include <stdio.h>

#define NN 200100
#define INT long long
#define pb push_back
using namespace std;

int a[NN];  // Input array
int mn[NN]; // Precomputed minimums for first k operations

int main() {
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    scanf("%d", a + i);
  sort(a + 1, a + n + 1); // Sort to process elements in ascending order
  a[n + 1] = 2e9;         // Sentinel to prevent out-of-bounds access
  mn[0] = a[1];           // Base case: minimum after 0 operations
  for (int i = 1; i <= n; i++)
    mn[i] = min(mn[i - 1] + 1, a[i + 1]); // Precompute prefix mins
  INT sum = 0;
  for (int i = 1; i <= n; i++)
    sum += a[i]; // Sum of all elements for fast computation later
  while (q--) {
    int k;
    scanf("%d", &k);
    if (k <= n) {
      printf("%d ", mn[k]); // If k <= n, just return precomputed value
      continue;
    }
    k -= n;                    // Remaining operations after first n
    int v = mn[n - 1] + k + 1; // Estimate from prefix
    int vv = a[n];             // Last element of sorted array
    INT MN = min(v, vv);       // Minimum possible value

    if (k % 2 == 0)
      MN = mn[n] + k; // Adjust for even steps

    // Calculate total sum after applying k operations
    INT S = (2ll * k + n + 2) * (n - 1) / 2 + sum;
    if (k % 2 == 0)
      S = sum + 1ll * (2 * k + n + 1) * n / 2;

    if (k % 2)
      k++; // Make k even for even-step calculation

    // If the surplus is enough to reduce overall minimum
    if (S - MN * n >= k / 2) {
      cout << MN << " ";
      continue;
    }

    k /= 2;                // Reuse k for further calculation
    k -= (S - MN * n);     // Update based on surplus
    k = (k + n - 1) / n;   // Estimate how much to subtract
    cout << MN - k << " "; // Final result for this query
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/
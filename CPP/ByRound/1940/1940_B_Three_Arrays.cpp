// Problem: CF 1940 B - Three Arrays
// https://codeforces.com/contest/1940/problem/B

/*
Purpose: This code solves the "Three Arrays" problem where we need to maximize the sum of the final elements of two arrays A and B, constructed according to specific rules involving three input arrays D, L, and R, and initial values a and b.

Approach:
- Dynamic Programming with greedy optimization using sorting.
- The key idea is to decide at each step which operation (apply min to A or B) leads to a better final result.
- We process the input arrays in reverse order, accumulating sums in D.
- For each element, we compute adjusted values of L and R by adding the accumulated D values.
- Using a sorting technique to organize indices based on the adjusted L values.
- Then we iterate through the sorted indices to simulate choices and compute optimal sums.

Time Complexity: O(n log n) - due to the sorting step. The rest of the processing is linear.
Space Complexity: O(n) - for storing arrays and indices.

Algorithms/Techniques:
- Dynamic Programming
- Sorting with custom comparator
- Greedy choice strategy
*/

#include <stdio.h>
#define N 100000
#define INF 0x3f3f3f3f3f3f3f3fLL
long long min(long long a, long long b) { return a < b ? a : b; }
long long max(long long a, long long b) { return a > b ? a : b; }
unsigned int X = 12345;
int rand_() { return (X *= 3) >> 1; }
long long dd[N + 1], xx[N + 1], yy[N + 1];

// Custom quicksort implementation for sorting indices
void sort(int *ii, int l, int r) {
  while (l < r) {
    int i = l, j = l, k = r, i_ = ii[l + rand_() % (r - l)], tmp;
    while (j < k)
      if (xx[ii[j]] == xx[i_])
        j++;
      else if (xx[ii[j]] < xx[i_]) {
        tmp = ii[i], ii[i] = ii[j], ii[j] = tmp;
        i++, j++;
      } else {
        k--;
        tmp = ii[j], ii[j] = ii[k], ii[k] = tmp;
      }
    sort(ii, l, i);
    l = k;
  }
}

int main() {
  static int ii[N]; // array to store indices
  int n, i;
  long long x, y, ans;

  // Read input
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%lld", &dd[i]);

  // Accumulate D from right to left
  for (i = n - 1; i >= 0; i--)
    dd[i] += dd[i + 1];

  // Compute adjusted L values and store in xx
  for (i = 1; i <= n; i++) {
    scanf("%lld", &xx[i]);
    xx[i] += dd[i];  // Add accumulated sum to L
  }

  // Compute adjusted R values and store in yy
  for (i = 1; i <= n; i++) {
    scanf("%lld", &yy[i]);
    yy[i] += dd[i];  // Add accumulated sum to R
  }

  // Add the initial a and b to x and y respectively after adding accumulated sum
  scanf("%lld%lld", &x, &y), x += dd[0], y += dd[0];

  // Initialize index array
  for (i = 1; i <= n; i++)
    ii[i] = i;

  // Sort indices based on adjusted L values
  sort(ii, 1, n + 1);

  ans = 0; // Initialize answer

  // Iterate and calculate maximum value using greedy strategy
  for (i = 1; i <= n + 1; i++) {
    // At each step, try to find the best possible combination
    ans = max(ans, min(x, i <= n ? xx[ii[i]] : INF) + y);
    if (i <= n)
      y = min(y, yy[ii[i]]);  // Update y using smallest R value so far
  }

  // Output the maximum sum
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
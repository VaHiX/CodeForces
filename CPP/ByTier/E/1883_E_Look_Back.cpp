// Problem: CF 1883 E - Look Back
// https://codeforces.com/contest/1883/problem/E

/*
 * Problem: Make an array non-decreasing with minimum operations.
 * Each operation doubles an element. We use a greedy approach:
 * For each element, calculate how many doublings are needed so that
 * it becomes >= previous element.
 * 
 * Algorithm:
 * - Process elements from left to right.
 * - For each element, determine how many doublings are required to make it >= previous.
 * - Accumulate the number of operations needed.
 * 
 * Time Complexity: O(n * log(max(a[i]))) where n is the array size.
 * Space Complexity: O(n) for storing the array.
 */
#include <stdio.h>
using namespace std;
int main() {
  int k;
  scanf("%d", &k);
  while (k--) {
    int n;
    long long int sum = 0;
    scanf("%d", &n);
    int a[n + 1];
    long long int b[n + 1];
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
      int t = 0;
      if (i == 1) {
        b[i] = 0;
        continue;
      } else if (a[i] > a[i - 1]) {
        // Calculate how many doublings needed to make a[i] >= a[i-1]
        int c = a[i - 1];
        while (a[i] >= c) {
          t++;
          c *= 2;
        }
        // If we need more operations than already calculated, reset
        if (t - 1 >= b[i - 1]) {
          b[i] = 0;
        } else
          b[i] = b[i - 1] - t + 1;
      } else if (a[i] < a[i - 1]) {
        // Calculate how many doublings needed to make a[i] >= a[i-1]
        int c = a[i];
        while (c < a[i - 1]) {
          t++;
          c *= 2;
        }
        b[i] = t + b[i - 1];
      } else
        b[i] = b[i - 1];
    }
    for (int i = 1; i <= n; i++) {
      sum += b[i];
    }
    printf("%lld\n", sum);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
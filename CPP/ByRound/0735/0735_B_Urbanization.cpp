// Problem: CF 735 B - Urbanization
// https://codeforces.com/contest/735/problem/B

/*
Algorithm: Greedy approach to maximize the sum of arithmetic means.
We want to select n1 people for the first city and n2 people for the second city,
such that the sum of their average wealth is maximized.

Approach:
1. Sort the wealth array in ascending order.
2. To maximize the sum of averages:
   - For the first city (size n1), we want the highest n1 values.
   - For the second city (size n2), we want the highest n2 values from the remaining people.
3. Since we have already sorted the array, we take the last n1 elements for the first city
   and the next n2 elements for the second city (after the first n1 elements).
4. Compute the averages and sum them up.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the array.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, n1, n2;
  scanf("%ld %ld %ld", &n, &n1, &n2);
  std::vector<long> a(n, 0);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());
  if (n1 > n2) {
    long temp = n1;
    n1 = n2;
    n2 = temp;
  }
  double avg1(0), avg2(0);
  // Sum the largest n1 elements for the first city
  for (int p = n - 1; p >= n - n1; p--) {
    avg1 += a[p];
  }
  // Sum the largest n2 elements from the remaining for the second city
  for (int p = n - n1 - 1; p >= n - n1 - n2; p--) {
    avg2 += a[p];
  }
  avg1 /= n1;
  avg2 /= n2;
  double ans = avg1 + avg2;
  printf("%.8lf\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
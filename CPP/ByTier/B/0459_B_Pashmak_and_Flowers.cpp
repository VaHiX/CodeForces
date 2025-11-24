// Problem: CF 459 B - Pashmak and Flowers
// https://codeforces.com/contest/459/problem/B

#include <algorithm>
#include <cstdio>
#include <vector>

/*
Flowerbox:
Purpose: This program finds the maximum beauty difference between two flowers and counts the number of ways to achieve that difference.
Algorithm: 
1. Sort the beauty array to easily find minimum and maximum values.
2. Count how many flowers have the minimum beauty and how many have the maximum beauty.
3. If all flowers have the same beauty, the number of ways is n*(n-1)/2 (choosing 2 from n).
4. Otherwise, multiply the count of minimum beauty flowers with the count of maximum beauty flowers.
Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the beauty array.
*/
int main() {
  long long n;
  scanf("%lld\n", &n);
  std::vector<long long> beauty(n);
  for (long p = 0; p < n; p++) {
    scanf("%lld", &beauty[p]);
  }
  std::sort(beauty.begin(), beauty.end());
  long long minBeauty = beauty[0];
  long long maxBeauty = beauty[n - 1];
  long long countMin(0), countMax(0);
  long long ways(1);
  if (minBeauty == maxBeauty) {
    // All flowers have the same beauty, so number of ways to pick 2 is n*(n-1)/2
    ways *= n * (n - 1) / 2;
  } else {
    // Count flowers with minimum beauty
    for (long long p = 0; p < n; p++) {
      if (beauty[p] == minBeauty) {
        ++countMin;
      } else {
        break;
      }
    }
    // Count flowers with maximum beauty
    for (long long p = n - 1; p >= 0; p--) {
      if (beauty[p] == maxBeauty) {
        ++countMax;
      } else {
        break;
      }
    }
    // Number of ways = count of min * count of max
    ways *= countMin * countMax;
  }
  printf("%lld %lld\n", maxBeauty - minBeauty, ways);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
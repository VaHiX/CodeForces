// Problem: CF 915 A - Garden
// https://codeforces.com/contest/915/problem/A

/*
Flowerbox:
Code Purpose:
This program determines the minimum number of hours required to water a garden of length k using one of the available buckets.
Each bucket can water exactly 'a[i]' length per hour. The garden must be completely watered, and we must choose a bucket such that 
the total garden length is divisible by the bucket's watering rate (so that it can be watered in integer hours). 
We aim to minimize the time needed, so we select the bucket that takes the least time to water the entire garden.

Algorithms/Techniques:
- Iteration through all buckets to find a valid one (where k % a[i] == 0)
- Calculate time required for each valid bucket as k / a[i]
- Keep track of minimum time among all valid options

Time Complexity: O(n), where n is the number of buckets.
Space Complexity: O(1), only using a few variables regardless of input size.
*/

#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  long minTime(k); // Initialize with maximum possible time (k hours)
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    if (k % a) { // If k is not divisible by a, this bucket cannot be used
      continue;
    }
    minTime = (minTime < (k / a)) ? minTime : (k / a); // Update minimum time if current bucket is faster
  }
  printf("%ld\n", minTime);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
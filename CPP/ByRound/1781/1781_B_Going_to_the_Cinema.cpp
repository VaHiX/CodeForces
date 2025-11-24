// Problem: CF 1781 B - Going to the Cinema
// https://codeforces.com/contest/1781/problem/B

/*
B. Going to the Cinema
Algorithms/Techniques: Sorting, Greedy, Counting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the input array

The problem asks to count the number of valid subsets of people going to the cinema such that 
no one becomes sad. A person i is satisfied if:
- They go and at least a[i] others also go, or
- They don't go and fewer than a[i] others go.

This is solved by sorting the array and then counting valid thresholds where we can select 
people such that exactly p people go, satisfying everyone's condition for that threshold.
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
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read each person's required number of others
    }
    sort(a.begin(), a.end()); // Sort to process in order
    
    long cnt(0);
    for (long p = 0; p <= n; p++) {
      // Check if selecting exactly p people satisfies all constraints
      // For each position p, check if:
      // - Either it's the first element or previous person's requirement is less than p
      // - Either it's the last element or next person's requirement is greater than p
      cnt += ((p == 0 || a[p - 1] < p) && (p == n || a[p] > p));
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/
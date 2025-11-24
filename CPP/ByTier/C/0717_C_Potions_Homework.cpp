// Problem: CF 717 C - Potions Homework
// https://codeforces.com/contest/717/problem/C

/*
C. Potions Homework
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Algorithm: Sorting + Greedy
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for the vector storage

The problem asks to minimize the total time taken to complete all tasks,
where each student i has laziness level a[i] and each task j has difficulty a[j].
The time for student i doing task j is a[i] * a[j].

To minimize the sum of products, we should pair:
- The largest element with the smallest element
- The second largest with the second smallest, etc.

This is achieved by sorting the array and pairing elements from both ends.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  const long MOD = 10007;
  long n;
  scanf("%ld", &n);
  std::vector<long long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);  // Read the laziness/difficulty values
  }
  sort(a.begin(), a.end());  // Sort the array to enable greedy pairing
  long long total(0);
  for (long p = 0; p < n; p++) {
    total += (a[p] * a[n - 1 - p]) % MOD;  // Pair smallest with largest
    total %= MOD;  // Keep result within modulo
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/
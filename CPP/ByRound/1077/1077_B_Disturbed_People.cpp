// Problem: CF 1077 B - Disturbed People
// https://codeforces.com/contest/1077/problem/B

/*
B. Disturbed People
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
There is a house with n flats situated on the main street of Berlatov. Vova is watching this house every night. The house can be represented as an array of n integer numbers a_1, a_2, ..., a_n, where a_i = 1 if in the i-th flat the light is on and a_i = 0 otherwise.
Vova thinks that people in the i-th flats are disturbed and cannot sleep if and only if 1 < i < n and a_{i - 1} = a_{i + 1} = 1 and a_i = 0.
Vova is concerned by the following question: what is the minimum number k such that if people from exactly k pairwise distinct flats will turn off the lights then nobody will be disturbed? Your task is to find this number k.

Algorithm: Greedy approach
Time complexity: O(n)
Space complexity: O(n)

The algorithm scans through the array and identifies "disturbed" positions (where a[i-1] = a[i+1] = 1 and a[i] = 0).
When such a position is found, we turn off the light in the next flat (a[i+1]) to prevent disturbance,
and increment the count. This greedy choice ensures minimal number of operations.
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<int> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%d", &a[p]);  // Read the state of each flat
  }
  long cnt(0);
  for (long p = 1; p < n - 1; p++) {
    if (a[p]) {
      continue;  // Skip if current flat is already off
    }
    if (a[p - 1] && a[p + 1]) {  // Check if both neighbors are on
      a[p + 1] = 0;  // Turn off the right neighbor to prevent disturbance
      ++cnt;  // Increment operation count
    }
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/
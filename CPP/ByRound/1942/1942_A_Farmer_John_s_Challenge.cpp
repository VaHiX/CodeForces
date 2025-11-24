// Problem: CF 1942 A - Farmer John's Challenge
// https://codeforces.com/contest/1942/problem/A

#include <cstdio>
// Flower box describing the code purpose, algorithms, time and space complexity
/*
 * Problem: Farmer John's Challenge
 * 
 * Task: Given integers n and k, construct an array of length n such that exactly k of its cyclic shifts are sorted.
 * 
 * Approach:
 * - If k == 1: Create an array where elements are in ascending order (1, 2, ..., n). All cyclic shifts will be sorted except for the last one, but we only need 1 sorted shift.
 * - If k == n: Create an array with all elements equal (e.g., all 1s). All cyclic shifts will be sorted.
 * - Otherwise: It's impossible to have exactly k sorted cyclic shifts for 1 < k < n. This is because to get a sorted array, all elements must be equal or arranged in a very specific way that allows only a limited number of sorted rotations.
 * 
 * Time Complexity: O(n) per test case, as we do a linear scan to print the array.
 * Space Complexity: O(1), no extra space is used except for a few variables.
 */

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (k == 1) {
      // For k=1, create a sorted array [1, 2, ..., n]. Only the first cyclic shift will be sorted.
      for (long p = 1; p <= n; p++) {
        printf("%ld ", p);
      };
      puts(""); // Print newline after array
    } else if (k == n) {
      // For k=n, create an array of all 1s. All cyclic shifts will be sorted.
      for (long p = 1; p <= n; p++) {
        printf("1 ");
      };
      puts(""); // Print newline after array
    } else {
      // For 1 < k < n, it's impossible to have exactly k sorted cyclic shifts.
      puts("-1");
    }
  }
}

// https://github.com/VaHiX/CodeForces/
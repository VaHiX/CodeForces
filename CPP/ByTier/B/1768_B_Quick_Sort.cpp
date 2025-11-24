// Problem: CF 1768 B - Quick Sort
// https://codeforces.com/contest/1768/problem/B

/*
B. Quick Sort
Algorithm: Greedy with greedy counting of misplaced elements.
Time Complexity: O(n) per test case
Space Complexity: O(1)

Problem Description:
Given a permutation of integers from 1 to n and an integer k,
we can perform operations where we select k distinct elements,
remove them, sort them in increasing order, and append them to the end.
Goal is to find minimum number of such operations to make the array sorted.

Approach:
- Traverse the array and count how many elements are not in their correct position (i.e., not matching the sequence 1,2,3,...).
- For each group of k misplaced elements, we need one operation.
- The result is calculated as (cnt + k - 1) / k to round up to nearest integer.

Key insight:
- We only care about how many "groups" of k elements are misplaced.
- This greedy approach works because we are allowed to sort any k elements and place them at the end.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long seek(1), cnt(0);  // 'seek' tracks what value we expect next; 'cnt' counts mismatches
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == seek) {
        ++seek;  // If current element matches expected, move to next expected value
      } else {
        ++cnt;   // Otherwise, increment the count of misplaced elements
      }
    }
    printf("%ld\n", (cnt + k - 1) / k);  // Compute minimum operations needed using ceiling division
  }
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 1493 A - Anti-knapsack
// https://codeforces.com/contest/1493/problem/A

/*
Algorithm/Techniques: Greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting output)

The problem asks to select the maximum number of distinct integers from 1 to n
such that no subset of the chosen numbers sums to k.

Key insight:
- If we include numbers less than k, we need to be careful not to form a subset that sums to k.
- A greedy approach works: we can include all numbers from k+1 to n, and then include
  numbers from (k+1)/2 to k-1 (if they exist), but exclude k itself.
- The reasoning is that if we include numbers from (k+1)/2 to k-1, and all numbers from k+1 to n,
  we avoid forming a sum equal to k, since:
  1. Any number >= k+1 cannot be part of a subset that sums to k.
  2. If we include numbers from (k+1)/2 to k-1, their total sum is larger than k (since there are at least 2 such numbers if k>1), and we must avoid creating a subset sum = k.
- The count is: (n - k) + ((k - 1) - (k + 1) / 2 + 1) = n - (k + 1) / 2.

The solution prints all numbers from (k+1)/2 to k-1, and then from k+1 to n.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    printf("%ld\n", n - (k + 1) / 2);
    for (long p = (k + 1) / 2; p < k; p++) {
      printf("%ld ", p);
    }
    for (long p = k + 1; p <= n; p++) {
      printf("%ld ", p);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/
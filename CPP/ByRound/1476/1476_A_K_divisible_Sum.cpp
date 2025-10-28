// Problem: CF 1476 A - K-divisible Sum
// https://codeforces.com/contest/1476/problem/A

/*
Problem: A. K-divisible Sum
Purpose: For given n and k, find the minimum possible maximum element in an array of n positive integers such that their sum is divisible by k.

Algorithm:
- If n <= k: The optimal strategy is to distribute the sum evenly, and the answer is ceil(k/n).
- If n > k: The best approach is to use 1s as much as possible, and adjust with a single larger number if necessary.
  - If n % k == 0: All elements can be 1, so max = 1.
  - Otherwise, we need one element larger than 1 to make the sum divisible by k, so max = 2.

Time Complexity: O(1) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (n <= k) {
      // When n <= k, we can distribute the required sum among n elements
      // The minimum maximum is ceil(k/n), which equals (k + n - 1) / n
      printf("%ld\n", (k + n - 1) / n);
    } else {
      // When n > k, we use as many 1s as possible to minimize max element
      // If n % k == 0, all elements can be 1
      // Otherwise, we need one element equal to 2 to balance the sum
      printf("%d\n", 1 + (n % k > 0));
    }
  }
}


// https://github.com/VaHiX/codeForces/
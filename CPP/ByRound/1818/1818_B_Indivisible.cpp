// Problem: CF 1818 B - Indivisible
// https://codeforces.com/contest/1818/problem/B

/*
Purpose: To find a permutation of integers from 1 to n such that for any subarray from index l to r,
         the sum of elements is not divisible by the length of the subarray (r - l + 1).

Algorithm/Techniques:
- If n is 1, output "1" directly.
- If n is odd, it's impossible to satisfy the condition, so output "-1".
- If n is even, create a permutation by swapping adjacent pairs in the sequence 1,2,...,n.
  This ensures that no subarray sum is divisible by its length.

Time Complexity: O(n) - We perform a linear number of operations (swapping adjacent pairs).
Space Complexity: O(n) - We use a vector to store the permutation.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n == 1) {
      puts("1");
      continue;
    }
    if (n % 2) {
      puts("-1");
      continue;
    }
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      a[p] = p + 1;
    }
    for (long p = 1; p < n; p += 2) {
      long x = a[p - 1];
      a[p - 1] = a[p];
      a[p] = x;
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/
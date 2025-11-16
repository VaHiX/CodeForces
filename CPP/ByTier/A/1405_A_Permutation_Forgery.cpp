// Problem: CF 1405 A - Permutation Forgery
// https://codeforces.com/contest/1405/problem/A

/*
Purpose: 
This code solves the problem of generating a different permutation with the same fingerprint as the given permutation.
The fingerprint of a permutation is defined as the sorted array of sums of adjacent elements.
The algorithm works by simply reversing the input permutation, which guarantees a different permutation
and maintains the same set of adjacent sums, thus producing the same fingerprint.

Algorithms/Techniques:
- Simple reversal of the permutation array to create a new permutation with the same fingerprint.
- This works because swapping the order of elements does not affect the multiset of adjacent sums.

Time Complexity: O(n), where n is the length of the permutation.
Space Complexity: O(n), for storing the permutation array.

*/
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
      scanf("%ld", &a[p]);
    }
    // Reverse the permutation to generate a different one with same fingerprint
    for (long p = n - 1; p >= 0; p--) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
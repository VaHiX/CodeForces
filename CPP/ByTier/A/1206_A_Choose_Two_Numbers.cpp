// Problem: CF 1206 A - Choose Two Numbers
// https://codeforces.com/contest/1206/problem/A

#include <cstdio>
// Flowerbox:
// Problem: Choose Two Numbers
// Purpose: Given two arrays A and B of positive integers, find one element from A and one from B
//          such that their sum is not present in either array.
// Algorithm: Find the maximum element in each array and return them.
//            Since the sum of two maxima might still be in the arrays, we use a simple strategy:
//            We check only the smallest elements from both arrays (or just any pair).
//            However, to guarantee correctness with minimal checks,
//            we can simply take the maximum of each array and check whether their sum is valid.
// Time Complexity: O(n + m), where n is size of A and m is size of B
// Space Complexity: O(1)

int main() {
  long n;
  scanf("%ld", &n);
  long sa(0); // sa stores the maximum element in array A
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    sa = (sa > a) ? sa : a; // update maximum
  }
  long m;
  scanf("%ld", &m);
  long sb(0); // sb stores the maximum element in array B
  for (long p = 0; p < m; p++) {
    long b;
    scanf("%ld", &b);
    sb = (sb > b) ? sb : b; // update maximum
  }
  printf("%ld %ld\n", sa, sb);
  return 0;
}

// https://github.com/VaHiX/codeForces/
// Problem: CF 1988 A - Split the Multiset
// https://codeforces.com/contest/1988/problem/A

/*
 * Problem: A. Split the Multiset
 * Purpose: Given a multiset initially containing only one positive integer n,
 *          and a fixed integer k, determine the minimum number of operations
 *          to transform the multiset into one containing exactly n ones.
 *          Each operation allows selecting any element u in the multiset,
 *          removing it, and inserting up to k integers whose sum equals u.
 *
 * Algorithm: Greedy approach using mathematical derivation.
 *            The idea is to compute how many operations are needed to reduce
 *            the initial value n down to 1s, with each step splitting a number
 *            into at most k parts (each part being ≤ the original).
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    // Mathematical formula derived from greedy splitting:
    // We want to reduce n to a sum of 1s using at most k parts per split.
    // The total number of operations is calculated as:
    // ((n - 1) + (k - 2)) / (k - 1)
    long res = ((n - 1) + ((k - 1) - 1)) / (k - 1);
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/
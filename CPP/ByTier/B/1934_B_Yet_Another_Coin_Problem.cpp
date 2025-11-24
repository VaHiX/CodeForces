// Problem: CF 1934 B - Yet Another Coin Problem
// https://codeforces.com/contest/1934/problem/B

/*
B. Yet Another Coin Problem

Algorithm:
This problem is a variant of the coin change problem where we are given 5 types of coins: 1, 3, 6, 10, and 15 (first five triangular numbers). 
We need to find the minimum number of coins to sum up to a target value n.

Approach:
1. The function `f(n)` computes the minimum number of coins using a greedy approach for the given coin denominations.
   - It uses a greedy strategy: always take as many coins of the largest denomination possible, then proceed to the next smaller one.
2. For each query n:
   - Compute the result by trying three cases:
     1. Using 0 tens (i.e., use coins from 1, 3, 6, 10, 15 directly),
     2. Using 1 ten (subtracting 10 and computing the rest),
     3. Using 2 tens (subtracting 20 and computing the rest).
   - Take the minimum among these three.

Time Complexity: O(1) per test case
Space Complexity: O(1)

*/

#include <cstdio>

long f(long n) {
  if (n < 0) {
    return 1e9; // Return large value for invalid input
  }
  long cnt(0);
  cnt += (n / 15);   // Use as many 15-denomination coins as possible
  n %= 15;
  cnt += (n / 6);    // Use as many 6-denomination coins as possible
  n %= 6;
  cnt += (n / 3);    // Use as many 3-denomination coins as possible
  n %= 3;
  cnt += n;          // Remaining value must be filled with 1-denomination coins
  return cnt;
}

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long zero_tens = f(n);                   // Case: no tens used
    long one_tens = 1 + f(n - 10);           // Case: 1 ten used (i.e., subtract 10)
    long two_tens = 2 + f(n - 20);           // Case: 2 tens used (i.e., subtract 20)
    long ans = (zero_tens < one_tens ? zero_tens : one_tens);
    ans = (ans < two_tens ? ans : two_tens); // Find the minimum among all cases
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/
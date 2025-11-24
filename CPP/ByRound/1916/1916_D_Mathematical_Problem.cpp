// Problem: CF 1916 D - Mathematical Problem
// https://codeforces.com/contest/1916/problem/D

/*
Code Purpose:
This program solves a mathematical problem where given an odd number n, 
it finds n different numbers of length n such that each number is a perfect square, 
and all numbers have the same multiset of digits.

Algorithm:
The solution uses a constructive approach:
1. For n = 1, it directly outputs "1"
2. For n > 1, it starts by generating three base numbers: 169, 196, 961
   (which are squares of 13, 14, 31 respectively)
3. Then it generates additional numbers using a pattern that maintains 
   the same multiset of digits across all numbers
4. The pattern builds numbers using '1', '6', '9' with zeros in between
   to ensure each generated number has length n and all share same digits

Time Complexity: O(n^2) - The loops generate numbers and print them, 
                     with nested loops running up to n/2 times.
Space Complexity: O(1) - Only a constant amount of extra space is used, 
                        regardless of input size.

*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;
char s[109][109][109];
int main() {
  int t, n, i, j, k;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    if (n == 1)
      printf("1\n");
    else {
      printf("169");
      for (i = 4; i <= n; i++)
        printf("0");
      printf("\n");
      printf("196");
      for (i = 4; i <= n; i++)
        printf("0");
      printf("\n");
      printf("961");
      for (i = 4; i <= n; i++)
        printf("0");
      printf("\n");
      for (i = 1; i <= (n - 3) / 2; i++) {
        printf("1");
        for (j = 1; j <= i; j++)
          printf("0");
        printf("6");
        for (j = 1; j <= i; j++)
          printf("0");
        printf("9");
        for (j = 1; j <= n - 2 * i - 3; j++)
          printf("0");
        printf("\n");
      }
      for (i = 1; i <= (n - 3) / 2; i++) {
        printf("9");
        for (j = 1; j <= i; j++)
          printf("0");
        printf("6");
        for (j = 1; j <= i; j++)
          printf("0");
        printf("1");
        for (j = 1; j <= n - 2 * i - 3; j++)
          printf("0");
        printf("\n");
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 1047 A - Little C Loves 3 I
// https://codeforces.com/contest/1047/problem/A

#include <stdio.h>

int n, a;
int main() {
  scanf("%d", &n);
  ++a += n % 3 == 2; // If n mod 3 equals 2, set a to 2, otherwise 1
  printf("1 %d %d", a, n - 1 - a); // Print 1, a, and (n-1-a) as the three numbers
}

/*
Problem: A. Little C Loves 3 I
Purpose: Split a positive integer n into 3 positive integers a, b, c such that a+b+c=n and none of them is divisible by 3.
Algorithm: 
  - If n % 3 == 2, set a = 2, b = 1, c = n-3. This ensures none are divisible by 3.
  - Otherwise, set a = 1, b = 1, c = n-2. This also ensures none are divisible by 3.
Time Complexity: O(1)
Space Complexity: O(1)
*/

// https://github.com/VaHiX/codeForces/
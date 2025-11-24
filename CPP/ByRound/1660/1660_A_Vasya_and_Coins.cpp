// Problem: CF 1660 A - Vasya and Coins
// https://codeforces.com/contest/1660/problem/A

/*
A. Vasya and Coins

Purpose:
This program determines the minimum positive integer amount of money that Vasya cannot pay using only his 1-burle and 2-burle coins.

Algorithms/Techniques:
- Mathematical analysis of coin combinations
- Greedy approach to determine reachable amounts
- Special case handling for edge conditions

Time Complexity: O(1) - Each test case is processed in constant time.
Space Complexity: O(1) - Only a constant amount of extra space is used.

Input Format:
- First line contains number of test cases t (1 <= t <= 10^4)
- For each test case, two integers a and b (0 <= a, b <= 10^8) representing 
  number of 1-burle and 2-burle coins respectively

Output Format:
- For each test case, print the minimum positive integer amount that cannot be paid
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    // If a is 0, we can't make any odd amount, so answer is 1
    // Otherwise, we can make all even amounts up to 2*b and all odd amounts 
    // up to 2*b+1, then the next unattainable is 2*b+2 if a >= 1 or 2*b+1 if a = 0.
    // But since we check for a=0 first, when a > 0, the result is (a + 2 * b) + 1.
    printf("%ld\n", (a ? (a + 2 * b) : 0) + 1);
  }
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 2041 B - Bowling Frame
// https://codeforces.com/contest/2041/problem/B

#include <cmath>
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long long w, b;
    scanf("%lld %lld", &w, &b);
    long double t = w + b; // Total number of pins
    // Solve for the largest k such that k(k+1)/2 <= total pins
    // Using quadratic formula: k = (-1 + sqrt(1 + 8 * total)) / 2
    long res = (sqrt(1 + 8 * t) - 1) / 2.0;
    printf("%ld\n", res);
  }
}
/*
B. Bowling Frame

Purpose:
This program calculates the maximum side length of a triangular bowling frame that can be constructed using a given number of white and black pins, under the constraint that all pins in any row must be the same color.

The triangular frame follows the pattern where a frame of side length k uses exactly k(k+1)/2 pins. The solution involves solving a quadratic inequality to find the largest valid k such that k(k+1)/2 ≤ w + b.

Algorithms/Techniques:
- Mathematical optimization using quadratic formula
- Binary search (implicit in the derived closed-form solution)

Time Complexity: O(t), where t is the number of test cases. Each case processes in constant time after calculating the square root.

Space Complexity: O(1). Only a constant amount of extra space is used regardless of input size.

Input Format:
- First line contains integer t (number of test cases)
- For each test case, two integers w and b representing white and black pins respectively

Output Format:
- For each test case, output the maximum side length k of the triangular frame
*/

// https://github.com/VaHiX/codeForces/
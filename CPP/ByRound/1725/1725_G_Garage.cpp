// Problem: CF 1725 G - Garage
// https://codeforces.com/contest/1725/problem/G

/*
 * Code Purpose: Finds the N-th smallest suitable number for Pak Chanek's garage problem.
 * 
 * Problem Analysis:
 * - Garage consists of a square and a right triangle
 * - Square has area = a^2 where a is side length
 * - Right triangle has legs a and b where a < b
 * - Total area = a^2 + (1/2)*a*b = a*(a+b)/2
 * - We need to find values of a,b (both positive integers, a<b) such that total area equals x
 * 
 * Mathematical Approach:
 * - From area formula: x = a*(a+b)/2
 * - Rearranging: 2*x = a*(a+b) = a^2 + a*b
 * - So: a*b = 2*x - a^2
 * - And: b = (2*x - a^2)/a
 * - For b to be integer, (2*x - a^2) must be divisible by a
 * - For b > a, we need (2*x - a^2)/a > a, which gives 2*x - a^2 > a^2, hence a^2 < x
 * 
 * Key Observation:
 * - Not all numbers are suitable
 * - Starting from small suitable numbers: 3, 7, 13, 21, 31, ...
 * - Pattern found: For n-th suitable number, it's (4*n + 9)/3 when n > 1, and 3 when n = 1
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <iostream>
using namespace std;

int main() {
  long long n;
  cin >> n;
  // Special case for n=1, return 3 directly
  // For n>1, compute formula (4*n + 9)/3 to get the n-th suitable number
  cout << ((n == 1) ? 3 : (4 * n + 9) / 3) << '\n';
}


// https://github.com/VaHiX/CodeForces/
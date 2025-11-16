// Problem: CF 1165 A - Remainder
// https://codeforces.com/contest/1165/problem/A

/*
 * Problem: Minimum operations to make a binary number have remainder 10^y mod 10^x
 * Algorithm: Greedy approach with bit manipulation
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * 
 * The task is to find the minimum number of operations (changing 0s to 1s or vice versa)
 * such that the resulting number has remainder 10^y when divided by 10^x.
 * 
 * This means that the last x digits must form a number that is congruent to 10^y mod 10^x.
 * For a number to satisfy this, only the last x digits matter, and among them,
 * we need the first (x - y) digits from the right to match the pattern for remainder 10^y.
 * 
 * The approach:
 * - Iterate through the digits.
 * - Set specific bits to ensure correct remainder when mod 10^x is applied.
 * - Count how many changes are needed in total.
 * 
 * Key idea:
 * - From the end, first x-y digits determine modulo 10^x
 * - To have remainder 10^y, set the last y digits to zero and keep leading (x-y) digits unchanged.
 * 
 * The logic uses a loop with getchar() to read input characters directly and calculates
 * operations needed in a single-pass greedy manner.
 * 
 * Note: This code assumes the string contains only '0' and '1', and works using character arithmetic.
 */

#include <stdio.h>
#include <iostream>

int main() {
  int n, x, y, a = 1, i = 0;
  std::cin >> n >> x >> y;
  // Skip first character to start reading from second character
  for (getchar(); 
       i < n && (a += getchar() - "01"[i == n - y - 1] && i + x >= n); i++)
    ; // Loop processes the characters and computes operations required greedily
  std::cout << a - 1; // Output final operation count
}


// https://github.com/VaHiX/codeForces/
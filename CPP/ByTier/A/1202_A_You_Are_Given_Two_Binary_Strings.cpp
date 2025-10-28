// Problem: CF 1202 A - You Are Given Two Binary Strings...
// https://codeforces.com/contest/1202/problem/A

/*
 * Problem: You are given two binary strings x and y, which represent integers f(x) and f(y).
 * Task: Choose k >= 0 such that rev_k (binary representation of s_k = f(x) + f(y) * 2^k reversed) is lexicographically minimal.
 * 
 * Algorithm:
 * - The key idea is to find the minimal number of trailing zeros in the sum after multiplying y by 2^k and adding x.
 * - To avoid overflow and simplify comparison, we count trailing zeros efficiently.
 * 
 * Time Complexity: O(n + m) where n = len(x), m = len(y)
 * Space Complexity: O(1) excluding input storage
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string x, y;
    std::cin >> x >> y;
    long a;
    // Count trailing zeros in y from the end
    for (a = 0; a < y.size() && y[y.size() - 1 - a] == '0'; a++)
      ;
    long b;
    // Count trailing zeros in x after subtracting the effect of y's trailing zeros
    for (b = 0; b < x.size() && x[x.size() - 1 - a - b] == '0'; b++)
      ;
    std::cout << b << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/
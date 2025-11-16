// Problem: CF 764 A - Taymyr is calling you
// https://codeforces.com/contest/764/problem/A

/*
 * Purpose: Calculate the minimum number of artists to kill so that no artist is present when Ilia calls.
 * 
 * Algorithm: 
 * - Ilia calls every 'n' minutes (n, 2n, 3n, ...)
 * - Artists arrive every 'm' minutes (m, 2m, 3m, ...)
 * - We need to find how many times both events coincide in the first 'z' minutes.
 * - This is equivalent to finding the number of multiples of LCM(n, m) that are <= z.
 * 
 * Time Complexity: O(log(min(n, m))) due to computing LCM using std::lcm
 * Space Complexity: O(1) - only using a few integer variables
 */

#include <iostream>
#include <numeric>

int a, b, c;
int main() {
  std::cin >> a >> b >> c;
  std::cout << c / std::lcm(a, b);  // Count of coinciding events (multiples of LCM)
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 1141 A - Game 23
// https://codeforces.com/contest/1141/problem/A

/*
 * Problem: Game 23
 * Purpose: Transform number n to m by multiplying by 2 or 3.
 *          Return minimum moves or -1 if impossible.
 * 
 * Algorithm: 
 *   - Check if m is divisible by n. If not, return -1.
 *   - Divide m by n to get target ratio.
 *   - While the ratio is greater than 1:
 *     - If divisible by 2, divide by 2
 *     - Else if divisible by 3, divide by 3
 *     - If neither, return -1
 *     - Increment step counter
 *   - If final ratio is 1, return steps; otherwise -1
 * 
 * Time Complexity: O(log(m/n))
 * Space Complexity: O(1)
 */

#include <iostream>
int m, n, s;
int main() {
  std::cin >> n >> m;
  if (m % n) // Check if m is divisible by n
    return std::cout << -1, 0; // If not, impossible transformation
  for (m /= n; ~m % 2 || m % 3 < 1; s++) // While m is divisible by 2 or 3
    m % 2 ? m % 3 ?: m /= 3 : m /= 2; // If m is odd, divide by 3 else divide by 2
  std::cout << (m > 1 ? -1 : s); // If m > 1 then impossible, else output steps
}


// https://github.com/VaHiX/codeForces/
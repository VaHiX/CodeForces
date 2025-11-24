// Problem: CF 628 A - Tennis Tournament
// https://codeforces.com/contest/628/problem/A

/* 
 * Problem: Tennis Tournament
 * 
 * Algorithm/Techniques: Simulation with bitwise operations
 * 
 * Time Complexity: O(log n) - The loop runs approximately log n times as n is halved in each iteration.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 * 
 * The solution simulates the tournament rounds, calculating the number of bottles needed
 * based on the number of matches in each round, and towels are simply n * p because
 * each participant gets p towels for the entire tournament.
 */

#include <iostream>
long getLargestPower(long x) {
  if (x <= 0) {
    return 0;
  }
  long a = 1;
  while (2 * a <= x) {
    a *= 2;
  }
  return a;
}
int main() {
  long n, b, p;
  std::cin >> n >> b >> p;
  long bottles(0), towels(p * n); // towels = p * n since each participant gets p towels
  while (n > 1) {
    long m = getLargestPower(n); // Find the largest power of 2 less than or equal to n
    bottles += b * m + (m / 2);  // Each match needs b * 2 participants + 1 judge, and m/2 matches happen
    n -= m / 2;                  // Remove half of the participants who advanced
  }
  std::cout << bottles << " " << towels << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
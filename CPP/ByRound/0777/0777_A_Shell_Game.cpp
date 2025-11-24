// Problem: CF 777 A - Shell Game
// https://codeforces.com/contest/777/problem/A

/*
 * Code Purpose: Solves the Shell Game problem where the operator performs a sequence of swaps
 *               on three shells (0, 1, 2) and the ball ends up at position x after n moves.
 *               The pattern of swaps repeats every 6 steps, allowing us to compute the result
 *               using modular arithmetic.
 *
 * Algorithms/Techniques: Pattern recognition, modular arithmetic
 *
 * Time Complexity: O(1) - The solution uses a precomputed lookup table and constant time operations.
 * Space Complexity: O(1) - The vector stores only 6 fixed strings, independent of input size.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  const long N = 6; // The pattern of swaps repeats every 6 steps
  std::vector<std::string> a; // Precomputed sequence of shell positions after each step
  a.push_back("012"); // Initial state
  a.push_back("102"); // After 1st swap (0 <-> 1)
  a.push_back("120"); // After 2nd swap (1 <-> 2)
  a.push_back("210"); // After 3rd swap (0 <-> 1)
  a.push_back("201"); // After 4th swap (1 <-> 2)
  a.push_back("021"); // After 5th swap (0 <-> 1)
  long n, f; // n: number of moves, f: final position of the ball
  std::cin >> n >> f;
  int res = a[n % N][f] - '0'; // Use mod to find the correct step in the pattern, then index into that step
  std::cout << res << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
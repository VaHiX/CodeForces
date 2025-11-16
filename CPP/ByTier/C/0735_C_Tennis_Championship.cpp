// Problem: CF 735 C - Tennis Championship
// https://codeforces.com/contest/735/problem/C

#include <iostream>
#include <vector>
/*
 * Problem: Tennis Championship
 * Purpose: Find the maximum number of games the winner of a knockout tournament can play,
 *          given that two players can only compete if their number of games played differs by at most one.
 * 
 * Algorithm: The solution uses a Fibonacci-like sequence where:
 *            - f(0) = 2 (base case for 2 players)
 *            - f(1) = 3 (base case for 3 players)
 *            - f(n) = f(n-1) + f(n-2) (recursive relation)
 *            The sequence represents minimum number of players required for the winner to play n games.
 *            We find the smallest index such that f(index) > n, then return index - 1.
 *            Special cases for n = 2 and n = 3 are handled directly.
 * 
 * Time Complexity: O(1) - Since N is fixed at 100, the loop runs a constant number of times.
 * Space Complexity: O(1) - Fixed size vector of size 100, regardless of input n.
 */
int main() {
  const int N = 100;
  unsigned long long n;
  std::cin >> n;
  std::vector<unsigned long long> fib(N, 0);
  fib[0] = 2;
  fib[1] = 3;
  int num(0);
  for (int p = 2; p < N; p++) {
    fib[p] = fib[p - 1] + fib[p - 2]; // Compute next Fibonacci-like number
    if (fib[p] > n) {
      num = p;
      break;
    }
  }
  if (n == 2) {
    num = 1;
  } else if (n == 3) {
    num = 2;
  }
  std::cout << num << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
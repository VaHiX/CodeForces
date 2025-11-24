// Problem: CF 638 A - Home Numbers
// https://codeforces.com/contest/638/problem/A

#include <iostream>
// Purpose: Calculate the minimum time to reach a house 'a' from the beginning of the street
//          in a two-sided street with 'n' houses (n is even).
//          Houses are numbered such that odd numbers are on one side (1 to n-1,
//          left to right) and even numbers on the other side (n to 2, right to left).
//          Each move between adjacent houses takes 1 second, and moving to/from the
//          beginning to house 1 or n takes 1 second.
//
// Algorithm: The solution uses a mathematical approach to determine the minimum time:
//            - If 'a' is odd, the path is from start to house 'a' on the left side.
//              The number of moves needed is (a - 1) / 2.
//            - If 'a' is even, the path is from start to house 'a' on the right side.
//              The number of moves needed is (n - a) / 2.
//            - Add 1 second for the initial move from the start to the first house.
//
// Time Complexity: O(1) - constant time computation
// Space Complexity: O(1) - only using a constant amount of extra space
int main() {
  long n, a;
  std::cin >> n >> a;
  long ans = 1 + ((a % 2) ? ((a - 1) / 2) : ((n - a) / 2));
  std::cout << ans << std::endl;
  return 0;
}

// https://github.com/VaHiX/CodeForces/
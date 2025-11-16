// Problem: CF 1285 A - Mezo Playing Zoma
// https://codeforces.com/contest/1285/problem/A

/*
Code Purpose:
This program determines the number of distinct positions Zoma can end up at after executing a sequence of commands 'L' and 'R', where some commands may be ignored due to a malfunctioning controller. The key insight is that regardless of which commands are ignored, the range of possible final positions is bounded by how many steps left and right the player could theoretically take if all commands were executed in the worst-case scenario.

Algorithm:
- Count total number of 'L' and 'R' commands.
- The furthest left Zoma can go is the count of 'L' commands if all are executed.
- The furthest right Zoma can go is the count of 'R' commands if all are executed.
- So the range of positions spans from negative (number of Ls) to positive (number of Rs), and the number of distinct positions is (L + R + 1).
- Since we do not know which commands will be sent successfully, the worst-case number of unique positions is just the number of commands plus one (including the starting position).

Time Complexity: O(n) - We scan the input string once.
Space Complexity: O(1) - Only using a few variables regardless of input size.

*/

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::cout << (n + 1) << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
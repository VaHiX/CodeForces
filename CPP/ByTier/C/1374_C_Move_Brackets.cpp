// Problem: CF 1374 C - Move Brackets
// https://codeforces.com/contest/1374/problem/C

/*
C. Move Brackets
Algorithm: Greedy + Prefix Sum
Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(1)

The problem asks to find the minimum number of moves to make a bracket sequence regular.
A key insight is that we need to track the balance of brackets as we go through the string.
If at any point the running balance goes negative, it means we have more closing brackets
than opening ones so far. The minimum number of moves needed corresponds to the minimum
balance encountered (made positive by adding opening brackets from outside).

For example:
- In ")(", when processing from left to right:
  - At index 0: '(' -> balance = 1
  - At index 1: ')' -> balance = 0
  - Minimum balance = 0, so we need 0 moves — but this is not quite right.
  
Actually, the approach is:
We keep a running count `cur` which increases by 1 for each '(' and decreases by 1 for each ')'.
We track the minimum value that `cur` reaches during traversal. The number of moves needed
is the absolute value of this minimum (i.e., how many opening brackets we need to prepend).
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long cur(0), mn(0); // cur tracks current balance, mn tracks minimum balance
    for (long p = 0; p < s.size(); p++) {
      cur += (s[p] == '(') - (s[p] == ')'); // update balance
      mn = mn < cur ? mn : cur; // keep track of minimum balance so far
    }
    std::cout << (-mn) << std::endl; // output number of moves needed
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
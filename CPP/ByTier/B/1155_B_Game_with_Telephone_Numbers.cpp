// Problem: CF 1155 B - Game with Telephone Numbers
// https://codeforces.com/contest/1155/problem/B

/*
B. Game with Telephone Numbers
Algorithm: Game Theory, Greedy Approach
Time Complexity: O(n)
Space Complexity: O(1)

A telephone number is a sequence of exactly 11 digits such that its first digit is 8.
Vasya and Petya are playing a game where they erase digits from a string until its length becomes 11.
The player who makes the final string a valid telephone number (starts with '8') wins.
We are given the initial string of odd length n >= 13. Vasya starts first, and both players play optimally.

Key idea:
- Vasya needs to ensure that among the remaining characters after all operations,
  there is at least one '8' in the prefix of length 11.
- Since Vasya plays first, he can remove up to (n - 11) / 2 characters.
- Petya will try to prevent Vasya from having a winning strategy.
- If we count how many '8's are present in the string, and compare it to how many '8's Vasya can afford
  to keep in place while ensuring at least one remains for position 0 (the first digit of a valid phone number),
  then the condition becomes:
    if number of 8s >= ceil((n - 11) / 2 + 1), Vasya wins.
- However, the simpler logic used here:
  - Count '8's from index 0 to n - 11 (because last 10 can't be part of valid phone number).
  - Calculate how many moves Petya could make: (n - 11) / 2
  - If Vasya can keep more than `moves` number of '8's, he wins.
*/

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long cnt(0);
  // Count how many '8' characters are available in the initial string
  for (long p = 0; p < s.size() - 10; p++) {
    cnt += (s[p] == '8'); // Only check positions where an 8 can still be used in the final result
  }
  long trn = (s.size() - 11) / 2;
  // If Vasya can save more than trn 8's, he wins.
  std::cout << (trn < cnt ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/
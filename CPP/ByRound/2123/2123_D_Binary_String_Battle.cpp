// Problem: CF 2123 D - Binary String Battle
// https://codeforces.com/contest/2123/problem/D

/*
D. Binary String Battle
Algorithms/Techniques: Greedy, Game Theory

Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting input)

This problem involves a game between Alice and Bob on a binary string.
Alice can choose any subsequence of length k and set all characters in it to '0'.
Bob can choose any substring of length k and set all characters in it to '1'.
Alice wins if the string becomes all zeros at any point.
We analyze whether Alice can win by counting the number of '1's in the string.

Key insight:
- Alice can only reduce '1's to '0's by choosing subsequences.
- If the total number of '1's is <= k, then Alice can win in one move.
- However, if there are more than 2*k '1's, Bob can always block Alice by converting
  a substring of length k to '1', which prevents Alice from reducing all '1's to zero.
- If the total number of '1's is <= k, or if n < 2*k (i.e., not enough space for both players to interfere),
  then Alice can win.

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    long cnt(0);
    for (long p = 0; p < s.size(); p++) {
      cnt += (s[p] == '1'); // Count total number of '1's
    }
    // Alice wins if:
    // 1. There are at most k '1's (can eliminate all in one move), OR
    // 2. The string is too short to allow Bob to block effectively (n < 2*k)
    std::cout << (cnt <= k || n < 2 * k ? "Alice" : "Bob") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/
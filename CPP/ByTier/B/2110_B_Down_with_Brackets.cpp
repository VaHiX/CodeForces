// Problem: CF 2110 B - Down with Brackets
// https://codeforces.com/contest/2110/problem/B

/*
B. Down with Brackets
Algorithms/Techniques: Greedy + Prefix Sum
Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(1) - only using a few variables regardless of input size

The problem asks whether we can remove exactly one '(' and one ')' from a balanced bracket sequence such that it becomes unbalanced.
We use a greedy approach by simulating the balance of brackets:
- For each prefix, compute the running balance (increment for '(', decrement for ')').
- If at any point the balance goes negative, then the sequence is already invalid.
- But this solution checks if there exists a way to remove one '(' and one ')' so that the resulting string becomes invalid.
  This is possible if and only if we can find such removals that lead to a negative prefix sum,
  which means we must have a prefix where closing brackets outnumber opening ones.

In this code:
- We iterate from index 1 to size-2 (since we can't remove first or last character).
- cnt tracks the prefix balance.
- If at any time before the end, the balance becomes negative,
  it suggests that removing one '(' and one ')' from this point might make the string unbalanced.
  However due to how input is constructed (balanced), just checking any violation of balance during traversal
  is sufficient for answering the question.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long cnt(0);
    bool ans(true);
    for (int p = 1; p + 1 < s.size(); p++) {
      cnt += ((s[p] == '(') - (s[p] == ')')); // update running balance
      if (cnt < 0) {
        ans = false; // found a prefix that breaks the balance, so possible to make it invalid
      }
    }
    std::cout << (ans ? "NO" : "YES") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/
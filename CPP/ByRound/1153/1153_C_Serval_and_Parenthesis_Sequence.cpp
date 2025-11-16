// Problem: CF 1153 C - Serval and Parenthesis Sequence
// https://codeforces.com/contest/1153/problem/C

/*
 * Problem: Serval and Parenthesis Sequence
 * 
 * Purpose: Given a string with '(', ')', and '?', replace '?' to make a valid
 *          parenthesis sequence where no strict prefix is a valid parenthesis
 *          sequence. If impossible, output ":(".
 * 
 * Algorithm/Techniques:
 * - Greedy approach: First count the number of '(' and ')', then greedily assign
 *   '(' or ')' to '?' such that the prefix remains invalid until the end.
 * - Check validity by ensuring at no point the balance becomes zero or negative
 *   for strict prefixes, and the total balance is zero at the end.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long cnt(0), par(0);
  // Count the number of '(' and ')' and '?' to evaluate balance
  for (long p = 0; p < n; p++) {
    if (s[p] == '(') {
      ++par;
    } else if (s[p] == ')') {
      --par;
    } else if (s[p] == '?') {
      ++cnt;
    }
  }
  // If length is odd, impossible to form a valid parenthesis sequence
  if (s.size() % 2) {
    std::cout << ":(" << std::endl;
    return 0;
  }
  // Assign '(' or ')' to '?' such that the prefix remains invalid
  for (long p = 0; (p < n) && cnt; p++) {
    if (s[p] != '?') {
      continue;
    }
    // If we still have more '?' than unmatched '(', use '(' to maintain imbalance
    if (cnt > par) {
      s[p] = '(';
      ++par;
    } else {
      s[p] = ')';
      --par;
    }
    --cnt;
  }
  bool possible(true);
  par = 0;
  // Validate final sequence: no strict prefix should be valid
  for (long p = 0; p < n; p++) {
    if (s[p] == '(') {
      ++par;
    } else if (s[p] == ')') {
      --par;
    }
    // If balance becomes non-positive before the end, prefix is valid -> invalid
    if (p + 1 < n && par <= 0) {
      possible = false;
    }
  }
  // Final check: total balance should be zero
  if (par != 0) {
    possible = false;
  }
  std::cout << (possible ? s : ":(") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 1993 A - Question Marks
// https://codeforces.com/contest/1993/problem/A

/*
 * Problem: A. Question Marks
 *
 * Purpose:
 *   Given a string of 4n characters consisting of 'A', 'B', 'C', 'D', and '?',
 *   determine the maximum number of correct answers Tim can achieve.
 *   Each character in the string represents one question, and there are exactly n
 *   questions for each of the four options. '?' denotes unanswered questions.
 *
 * Algorithm:
 *   - For each test case, count occurrences of 'A', 'B', 'C', 'D' and '?'
 *   - Use up to n occurrences of each answer type (limited by availability in input)
 *   - Distribute question marks optimally among options to maximize score
 *   - Specifically, allocate at most n correct answers per letter ('A','B','C','D')
 *
 * Time Complexity: O(4n) = O(n) per test case, where n is the number of questions per answer type.
 * Space Complexity: O(1), constant extra space (only using fixed-size counters).
 */

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Disable synchronization with C stdio for faster I/O
  long t;
  std::cin >> t;  // Read number of test cases
  while (t--) {   // Process each test case
    long n;
    std::cin >> n;  // Read number of correct answers per option
    std::string s;
    std::cin >> s;  // Read the answer string
    long a(0), b(0), c(0), d(0);  // Counters for each letter 'A', 'B', 'C', 'D'
    for (long p = 0; p < s.size(); p++) {  // Loop through all characters in the string
      a += (s[p] == 'A');  // Increment if character is 'A'
      b += (s[p] == 'B');  // Increment if character is 'B'
      c += (s[p] == 'C');  // Increment if character is 'C'
      d += (s[p] == 'D');  // Increment if character is 'D'
    }
    // For each option, take minimum of available count and n (maximum allowed)
    long cnt =
        (a < n ? a : n) + (b < n ? b : n) + (c < n ? c : n) + (d < n ? d : n);
    printf("%ld\n", cnt);  // Print the maximum possible score
  }
}


// https://github.com/VaHiX/codeForces/
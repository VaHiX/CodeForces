// Problem: CF 1935 A - Entertainment in MAC
// https://codeforces.com/contest/1935/problem/A

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::string rev(s);
    std::reverse(rev.begin(), rev.end()); // Reverse the string s and store in rev
    std::string a(s), b(rev + s);         // a is original string, b is reversed + original
    std::cout << (a < b ? a : b) << std::endl; // Compare a and b lexicographically and print smaller
  }
}
/*
 * Problem: Entertainment in MAC
 * 
 * Algorithm:
 *   - For each test case, we are given a string s of length m and an even number n.
 *   - We can perform two types of operations exactly n times:
 *     1) Append the reverse of s to s.
 *     2) Reverse s itself.
 *   - Goal: Find the lexicographically smallest string possible after exactly n operations.
 *
 * Key Insight:
 *   - If we reverse the string once and then append it, we get `rev + s`.
 *   - If we keep reversing (even number of times), the string becomes original again.
 *   - If we keep appending reverses (i.e., operations of type 1), after 2 operations we reach a state
 *     that is always longer.
 *   - So, we only need to consider two states:
 *     1) Original string s.
 *     2) Reverse of s appended to s -> rev + s.
 *
 * Time Complexity: O(m) per test case where m = length of the string s, due to reversal and comparison.
 * Space Complexity: O(m) for storing reversed string and concatenated string.
 */

// https://github.com/VaHiX/codeForces/
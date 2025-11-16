// Problem: CF 1151 A - Maxim and Biology
// https://codeforces.com/contest/1151/problem/A

/*
Problem: A. Maxim and Biology
Purpose: Find the minimum number of operations to transform a given string so that "ACTG" appears as a substring.
         Each operation allows replacing a character with the previous or next character in the alphabet (with wrapping).
Algorithms/Techniques: Sliding window approach over all substrings of length 4, calculating minimal cost to convert each
                       character to match 'A', 'C', 'T', 'G' respectively using circular distance.
Time Complexity: O(n), where n is the length of the input string.
Space Complexity: O(1), only using a constant amount of extra space.
*/

#include <iostream>
#include <string>

int main() {
  const int N = 26;
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long mn(27 * 5); // Initialize with a large value to track minimum cost
  for (long p = 0; p + 3 < s.size(); p++) {
    // Calculate distance from 'A' for the first character of current window
    long sa = s[p + 0] - 'A';
    sa = (sa > 0) ? sa : -sa; // Make sure sa is positive
    if (2 * sa > N) {         // If distance is more than half the alphabet, use circular distance
      sa = N - sa;
    }
    // Calculate distance from 'C' for the second character of current window
    long sb = s[p + 1] - 'C';
    sb = (sb > 0) ? sb : -sb;
    if (2 * sb > N) {
      sb = N - sb;
    }
    // Calculate distance from 'T' for the third character of current window
    long sc = s[p + 2] - 'T';
    sc = (sc > 0) ? sc : -sc;
    if (2 * sc > N) {
      sc = N - sc;
    }
    // Calculate distance from 'G' for the fourth character of current window
    long sd = s[p + 3] - 'G';
    sd = (sd > 0) ? sd : -sd;
    if (2 * sd > N) {
      sd = N - sd;
    }
    long total = sa + sb + sc + sd; // Total operations needed for current window
    mn = (mn < total) ? mn : total; // Update minimum if current window is better
  }
  std::cout << mn << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/
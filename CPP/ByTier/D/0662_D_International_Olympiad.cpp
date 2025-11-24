// Problem: CF 662 D - International Olympiad
// https://codeforces.com/contest/662/problem/D

/*
 * Problem: Determine the year corresponding to each given abbreviation of the International Olympiad.
 * The abbreviations follow the pattern "IAO'y", where 'y' represents the last digits of the year.
 * Years start from 1989 and abbreviations are chosen to be the shortest unused substring of the year's digits.
 *
 * Algorithm:
 * - For each input abbreviation, extract the numeric part (the digits after IAO').
 * - Starting from year 1989, systematically generate valid abbreviated forms.
 * - For each digit length (from 1 up to number of digits in the input), compute possible years,
 *   and identify which ones have not been used yet.
 * - Match against input to return correct full year.
 *
 * Time Complexity: O(n * d) where n is number of inputs and d is average length of input digits.
 * Space Complexity: O(1)
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  const long START = 1989;
  long n;
  std::cin >> n;
  while (n--) {
    std::string s;
    std::cin >> s;
    long year(0);
    // Extract numeric part of the abbreviation starting from index 4
    for (long p = 4; p < s.size(); p++) {
      year = 10 * year + (s[p] - '0');
    }
    long t(10), now(1989);
    // Build up the base value (t) and the current year to match the input length
    for (long p = 4; p < s.size() - 1; p++) {
      now += t;
      t *= 10;
    }
    // Adjust year so that it's at least as large as 'now' (the previous valid year)
    while (year < now) {
      year += t;
    }
    std::cout << year << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
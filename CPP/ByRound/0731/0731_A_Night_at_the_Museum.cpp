// Problem: CF 731 A - Night at the Museum
// https://codeforces.com/contest/731/problem/A

/*
 * Problem: Night at the Museum
 * Description: Calculate the minimum number of wheel rotations to spell a word
 *                on a circular alphabet wheel starting from 'a'.
 *
 * Algorithm:
 *   - For each character in the input string:
 *     * Compute the distance between current character and previous character
 *     * Handle wraparound by adding 26 if distance is negative
 *     * Choose the shorter path (clockwise or counter-clockwise)
 *     * Accumulate the minimal distance
 *
 * Time Complexity: O(n), where n is the length of the input string
 * Space Complexity: O(1), only using a constant amount of extra space
 */

#include <iostream>
#include <string>

int main() {
  const int N = 26;  // Number of letters in the English alphabet
  std::string s;
  std::cin >> s;
  char prev('a');  // Start at 'a'
  long count(0);   // Total rotations
  for (int p = 0; p < s.size(); p++) {
    char c = s[p];
    int dist = c - prev;  // Distance between characters
    if (dist < 0) {
      dist += N;  // Handle wraparound for counterclockwise
    }
    if (dist > N / 2) {
      dist = N - dist;  // Choose shorter path
    }
    count += dist;
    prev = c;  // Update previous character
  }
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
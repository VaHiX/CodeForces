// Problem: CF 816 A - Karen and Morning
// https://codeforces.com/contest/816/problem/A

/*
 * Problem: Karen and Morning
 * Purpose: Find the minimum minutes to sleep until the time becomes a palindrome.
 * Algorithm: Brute force simulation of time incrementing until a palindromic time is found.
 * Time Complexity: O(1) - Since there are at most 24 * 60 = 1440 possible times to check,
 *                      and checking a palindrome takes constant time.
 * Space Complexity: O(1) - Only using a fixed amount of variables regardless of input size.
 *
 * Techniques:
 *   - Simulation of time progression
 *   - Palindrome check using digit manipulation
 */

#include <iostream>
#include <string>

int main() {
  const int H = 24;  // Number of hours in a day
  const int M = 60;  // Number of minutes in an hour
  std::string s;
  std::cin >> s;
  int hour = 10 * (s[0] - '0') + (s[1] - '0');  // Extract hour from input string
  int minute = 10 * (s[3] - '0') + (s[4] - '0');  // Extract minute from input string
  long dur(0);  // Duration in minutes to sleep

  // Loop until current time is a palindrome
  while (!( (hour % 10 == minute / 10) && (hour / 10 == minute % 10) )) {
    ++dur;  // Increment sleep duration
    ++minute;  // Move to next minute
    if (minute >= M) {  // If minute exceeds 59
      minute = 0;  // Reset minute to 0
      ++hour;  // Increment hour
    }
    if (hour >= H) {  // If hour exceeds 23
      hour = 0;  // Reset hour to 0 (next day)
    }
  }

  std::cout << dur << std::endl;  // Output minimum minutes to sleep
  return 0;
}


// https://github.com/VaHiX/CodeForces/
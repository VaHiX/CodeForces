// Problem: CF 1950 C - Clock Conversion
// https://codeforces.com/contest/1950/problem/C

/*
C. Clock Conversion
time limit per test1 second
memory limit per test256 megabytes

Given the time in 24-hour format, output the equivalent time in 12-hour format.
24-hour format divides the day into 24 hours from 00 to 23, each of which has 60 minutes from 00 to 59.
12-hour format divides the day into two halves: the first half is AM, and the second half is PM. 
In each half, the hours are numbered in the order 12,01,02,03,…,11. Each hour has 60 minutes numbered from 00 to 59.

Algorithms/Techniques:
- String manipulation using substr() and to_string()
- Conditional logic for converting 24-hour to 12-hour format
- Special handling of midnight (00:xx) -> 12:xx AM
- Special handling of noon (12:xx) -> 12:xx PM

Time Complexity: O(t * n), where t is the number of test cases and n is the length of input string (constant 5)
Space Complexity: O(n), where n is the length of output string (constant 5)

*/
#include <iostream>
#include <string>
int main() {
  std::ios_base::sync_with_stdio(false); // Disable synchronization with C stdio for faster input/output
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s; // Read the time string in 24-hour format
    int h = std::stoi(s.substr(0, 2)); // Extract hour part and convert to integer
    bool pm(false); // Flag to indicate if it's PM
    pm = (h >= 12); // Set PM flag if hour >= 12
    if (h == 0) {
      h = 12; // Midnight 00:xx becomes 12:xx AM
    } else if (h > 12) {
      h -= 12; // Convert hours > 12 to 12-hour format
    }
    std::string t(""); // Create result string
    if (h < 10) {
      t = "0"; // Add leading zero for single digit hours
    }
    t += std::to_string(h); // Append converted hour
    t += s.substr(2); // Append minutes part (colon and minutes)
    t += pm ? " PM" : " AM"; // Append AM/PM suffix
    std::cout << t << std::endl; // Output result
  }
}


// https://github.com/VaHiX/codeForces/
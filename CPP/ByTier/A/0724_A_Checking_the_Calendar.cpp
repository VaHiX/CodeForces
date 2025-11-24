// Problem: CF 724 A - Checking the Calendar
// https://codeforces.com/contest/724/problem/A

/*
 * Problem: Checking the Calendar
 * 
 * Purpose: Determine if two given weekdays can be the first days of consecutive months 
 *          in a non-leap year, based on the number of days between those months.
 * 
 * Algorithm:
 * - Map each weekday to an integer (0-6) for easier computation.
 * - Calculate the difference in days between the two given weekdays.
 * - Check if that difference corresponds to the number of days in a month that 
 *   can occur between two consecutive months in a non-leap year.
 * - The valid differences are 0, 2, or 3, because:
 *   - 0 if both are the same day (e.g., Sunday, Sunday)
 *   - 2 if the transition is from a month with 31 days to one with 28 (e.g., Jan 1 to Feb 1)
 *   - 3 if the transition is from a month with 31 days to one with 30, or from 30 to 28 (e.g., July 1 to Aug 1)
 * 
 * Time Complexity: O(1) - Fixed number of operations, constant time mapping and computation.
 * Space Complexity: O(1) - Fixed size map and variables, constant space usage.
 */

#include <iostream>
#include <map>
#include <string>

int main() {
  const int W = 7;
  std::map<std::string, int> weekday;
  weekday["monday"] = 0;
  weekday["tuesday"] = 1;
  weekday["wednesday"] = 2;
  weekday["thursday"] = 3;
  weekday["friday"] = 4;
  weekday["saturday"] = 5;
  weekday["sunday"] = 6;
  std::string a, b;
  std::cin >> a >> b;
  int x = weekday[a];  // Convert first day to number
  int y = weekday[b];  // Convert second day to number
  int diff = y - x;    // Calculate difference in weekdays
  if (diff < 0) {
    diff += 7;         // Adjust for wrapping around the week
  }
  if (diff == 0 || diff == 2 || diff == 3) {  // Valid differences for consecutive months
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
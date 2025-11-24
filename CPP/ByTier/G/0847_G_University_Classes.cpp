// Problem: CF 847 G - University Classes
// https://codeforces.com/contest/847/problem/G

/*
Purpose: Determine the minimum number of rooms required to hold all student group classes on Monday.
         Each room can hold at most one group class in any time slot.
         The input is a list of group schedules, each represented as a 7-character string of 0s and 1s.
         A 1 means the group has a class at that time slot.

Algorithms/Techniques: 
    - Greedy approach: For each time slot, count how many groups have classes.
      The maximum count across all time slots gives the minimum number of rooms needed.

Time Complexity: O(n * G) where n is number of groups and G is number of time slots (7)
Space Complexity: O(n * G) for storing the group schedules

*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  const long G = 7;  // Number of time slots
  long n;            // Number of groups
  std::cin >> n;
  std::vector<std::string> a(n);  // Store schedules of all groups
  for (long p = 0; p < n; p++) {
    std::cin >> a[p];  // Read each group's schedule
  }
  long m(0);  // Maximum number of classes in any time slot
  for (long col = 0; col < G; col++) {  // Iterate over each time slot
    long count(0);  // Count of groups with class in current time slot
    for (long row = 0; row < n; row++) {
      count += a[row][col] - '0';  // Convert char '0'/'1' to int 0/1 and add to count
    }
    m = (m > count) ? m : count;  // Update maximum count
  }
  std::cout << m << std::endl;  // Output the minimum number of rooms needed
  return 0;
}


// https://github.com/VaHiX/CodeForces/
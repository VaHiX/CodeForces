// Problem: CF 681 A - A Good Contest
// https://codeforces.com/contest/681/problem/A

/*
Purpose: Determine if Anton has performed a "good" contest based on the defined criteria.
         A good performance is when Anton outperforms at least one user whose handle was red (rating >= 2400)
         and whose rating increased after the contest.

Algorithms/Techniques: Single pass through input, conditional checks.

Time Complexity: O(n), where n is the number of participants Anton outscored.
Space Complexity: O(1), only using a constant amount of extra space (variables and string of fixed size).

*/
#include <iostream>
#include <string>

int main() {
  int n;
  std::cin >> n;
  std::string ans("NO");  // Initialize answer to "NO"
  const int MIN = 2400;   // Define minimum rating for red handle color
  while (n--) {
    std::string name;
    std::cin >> name;
    int before, after;
    std::cin >> before >> after;
    if (before >= MIN && after > before) {  // Check if user had red handle and rating increased
      ans = "YES";
      break;  // Early exit since we only need one such user
    }
  }
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/
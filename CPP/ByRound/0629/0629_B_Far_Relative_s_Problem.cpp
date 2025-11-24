// Problem: CF 629 B - Far Relative’s Problem
// https://codeforces.com/contest/629/problem/B

/*
B. Far Relative’s Problem
Time Complexity: O(D * n) where D = 367 is the number of days in a year, n is the number of friends
Space Complexity: O(D * 2) = O(D) for the count vector

Algorithm:
- For each friend, we increment the count of males and females available on each day in their range [a, b].
- Then we iterate through all possible days and for each day calculate the maximum number of pairs (male, female) that can be invited.
- Since only one male and one female can attend together, the maximum number of people at the party is 2 * min(male_count, female_count) for that day.

Techniques:
- Range update using difference array concept (implemented via incrementing count for each day in range)
- Greedy approach to find maximum matching pairs

*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int D = 367; // Number of days in a year + 1 to handle 1-based indexing
  std::vector<std::vector<int>> count(D, std::vector<int>(2, 0)); // count[p][0] = male count, count[p][1] = female count for day p
  int n;
  std::cin >> n;
  while (n--) {
    std::string s; // gender of friend
    int a;         // start day
    int b;         // end day
    std::cin >> s >> a >> b;
    int x = (s[0] == 'M') ? 0 : 1; // 0 for male, 1 for female
    for (int p = a; p <= b; p++) {
      ++count[p][x]; // increment count of gender x for all days in range [a, b]
    }
  }
  int ans(0);
  for (int p = 1; p < D; p++) {
    int m = count[p][0];  // number of males available on day p
    int f = count[p][1];  // number of females available on day p
    int a = 2 * ((m < f) ? m : f); // maximum pairs = 2 * min(male, female)
    if (a > ans) {
      ans = a; // update maximum pairs
    }
  }
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/
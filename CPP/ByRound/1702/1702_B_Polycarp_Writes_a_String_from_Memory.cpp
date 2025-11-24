// Problem: CF 1702 B - Polycarp Writes a String from Memory
// https://codeforces.com/contest/1702/problem/B

/*
B. Polycarp Writes a String from Memory
Algorithm: Greedy with sliding window using set to track unique characters.
Time Complexity: O(n), where n is the total length of all strings in the input.
Space Complexity: O(1), since the set size is bounded by 3 (maximum unique characters stored at any time).

Each day, Polycarp can remember at most 3 different letters. The goal is to minimize
the number of days needed to write the entire string. We process the string from left to right,
and whenever we encounter a new character that would exceed the 3-character limit,
we increment the day counter and restart the memory set with the current character.
*/

#include <iostream>
#include <set>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long cnt(0); // Count of days needed
    std::set<long> w; // Set to store unique characters remembered on current day
    for (long p = 0; p < s.size(); p++) {
      w.insert(s[p]); // Insert current character into set
      if (w.size() > 3) { // If we exceed memory limit of 3 chars
        ++cnt; // Start a new day
        w.clear(); // Clear the set for next day
        w.insert(s[p]); // Add current character to new day's set
      }
    }
    cnt += (w.size() > 0); // Account for the last day if it has any characters
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/
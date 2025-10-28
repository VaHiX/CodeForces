// Problem: CF 1692 D - The Clock
// https://codeforces.com/contest/1692/problem/D

/*
Problem: D. The Clock
Purpose: Given a starting time and interval, count how many unique palindromic times are seen on a 24-hour clock when advancing by the interval each step.

Algorithms/Techniques:
- Precompute all palindromic times in a 24-hour period (00:00 to 23:59).
- For each query, simulate walking through the clock cycle with the given interval.
- Use modular arithmetic to wrap around the 24-hour clock (1440 minutes total).
- Use a set to store palindromic time values for fast lookup.

Time Complexity:
- Preprocessing: O(1440) = O(1) since there are at most 1440 possible times.
- Per query: O(1440 * x / gcd(x, 1440)) which simplifies to O(1440) since we traverse at most a full cycle.
- Overall: O(t * 1440), where t is number of test cases.

Space Complexity:
- O(1440) for storing palindromic times in a set.
*/

#include <iostream>
#include <set>
#include <string>

const long B = 24 * 60; // Total minutes in a day (1440)
bool isPalin(long x) {
  const long h = x / 60;   // Extract hour from total minutes
  const long m = x % 60;   // Extract minute from total minutes
  return ((h / 10) == (m % 10)) && ((h % 10) == (m / 10)); // Check if time is palindrome (e.g., 12:21)
}
long convert(std::string x) {
  return (10 * 60 * (x[0] - '0') + 60 * (x[1] - '0') + 10 * (x[3] - '0') +
          (x[4] - '0')); // Convert "HH:MM" string to total minutes
}
int main() {
  std::set<long> palins; // Set to store all palindromic times in minutes
  for (long min = 0; min < B; min++) { // Iterate over all possible minutes in a day
    if (isPalin(min)) { // If current time is palindrome
      palins.insert(min); // Insert it into set
    }
  }
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string s;
    long interval;
    std::cin >> s >> interval; // Read start time and interval
    long start = convert(s); // Convert start time to minutes
    long cur(start), cnt(palins.count(start)); // Initialize current time and count with start time
    for (long p = 1; p < B; p++) { // Loop through at most one full day (B steps)
      cur += interval; // Advance by the interval
      cur %= B; // Wrap around using modulo
      if (cur == start) { // If we've returned to the start, break
        break;
      }
      cnt += palins.count(cur); // Add 1 if current time is a palindrome, 0 otherwise
    }
    std::cout << cnt << std::endl; // Output total palindrome count seen
  }
}


// https://github.com/VaHiX/codeForces/
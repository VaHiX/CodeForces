// Problem: CF 2098 C - Sports Betting
// https://codeforces.com/contest/2098/problem/C

/*
C. Sports Betting
Algorithm: Greedy approach with map to count occurrences of each day.
Time Complexity: O(n log n) due to map operations (insertion and iteration)
Space Complexity: O(n) for storing the map

The problem asks whether Vadim can guarantee at least one correct prediction 
for consecutive days (a_i+1, a_i+2) across all bets he made.

Key idea:
- Count how many times each day appears in the input.
- For each unique day:
  - If a day appears >= 4 times: we can always make two correct predictions
    (e.g., for days d, d+1, d+2 we just need to say d=d, d+1=d+1, d+2=d+2)
  - If a day appears >= 2 times AND it's consecutive to previous day with at least
    2 occurrences: then we can make two correct predictions in sequence
  - Otherwise keep track of last day with 2 or more occurrences

We are essentially looking for a way to assign predictions such that 
at least one student gets both days correct.
*/

#include <cstdio>
#include <map>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m; // Count frequency of each day
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++m[x]; // Increment count for day x
    }
    long prev(-1); // Keep track of the previous day with at least 2 occurrences
    bool ans(false); // Flag to indicate if a valid strategy exists
    
    for (std::map<long, long>::iterator it = m.begin(); !ans && it != m.end();
         it++) {
      const long day = it->first;
      const long num = it->second; // Number of students betting on this day
      
      if (num >= 4) {
        ans = true; // Can always make two correct predictions
      } else if (num >= 2) {
        if (day == prev + 1) {
          // If current day is consecutive to previous day with at least 2 occurrences,
          // we can make both predictions correct for one student.
          ans = true;
        } else {
          prev = day; // Update previous day to current
        }
      } else if (day == prev + 1) {
        // Current day is just consecutive to the last checked day with >=2 occurrences,
        // but the current day itself has less than 2 occurrences.
        // Only update prev if we didn't find a matching pair already.
        prev = day;
      }
    }
    puts(ans ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/
// Problem: CF 1999 C - Showering
// https://codeforces.com/contest/1999/problem/C

/*
C. Showering
Algorithm: Greedily check for available time slots to fit a shower of length s.
We iterate through the tasks and see if there's a gap between the end of one task 
and the start of the next that is at least s. We also check the gap from the end of 
the last task to the end of the day.

Time Complexity: O(n) per test case, where n is the number of tasks.
Space Complexity: O(1), only using constant extra space.

Input:
- t: number of test cases
- For each test case:
  - n: number of tasks, s: shower duration, m: total minutes in day
  - n lines of tasks with interval [l_i, r_i]

Output:
- "YES" if a gap of at least s exists, "NO" otherwise
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s, m;
    scanf("%ld %ld %ld", &n, &s, &m);
    long prev(0); // Tracks the end time of the previous task
    bool res(false); // Flag to indicate if a valid gap was found
    for (long p = 0; p < n; p++) {
      long left, right;
      scanf("%ld %ld", &left, &right);
      if (prev + s <= left) { // Check if there's a gap of at least s minutes before this task
        res = true;
      }
      prev = right; // Update the end time of the last processed task
    }
    if (prev + s <= m) { // Check if there's a gap from the end of the last task to the end of the day
      res = true;
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/
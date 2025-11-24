// Problem: CF 499 A - Watching a movie
// https://codeforces.com/contest/499/problem/A

/*
Purpose: This code solves the problem of determining the minimum number of minutes to watch a movie 
to catch all specified "best moments", using two possible actions: watching the current minute or 
skipping exactly x minutes.

Algorithm: 
- Iterate through each best moment interval
- For each interval, calculate how many minutes we need to watch
- If we're not already at the start of the interval, we may need to skip some minutes
- The logic handles overlapping or adjacent intervals to minimize watched time

Time Complexity: O(n) where n is the number of best moments
Space Complexity: O(1) - only using a constant amount of extra space
*/

#include <cstdio>
int main() {
  long n, x; // n: number of best moments, x: skip interval
  scanf("%ld %ld\n", &n, &x);
  long current(0), total(0); // current: current position in movie, total: total minutes watched
  while (n--) {
    long l, r; // l: start of best moment, r: end of best moment
    scanf("%ld %ld\n", &l, &r);
    // Total minutes = (minutes in moment) + (extra minutes due to skipping)
    total += (r - l + 1) + ((l - current - 1) % x);
    current = r; // Move to end of current best moment
  }
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
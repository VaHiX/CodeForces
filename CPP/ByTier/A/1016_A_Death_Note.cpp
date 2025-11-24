// Problem: CF 1016 A - Death Note
// https://codeforces.com/contest/1016/problem/A

#include <cstdio>
int main() {
  long n, m;                          // n: number of days, m: names per page
  scanf("%ld %ld", &n, &m);           // Read n and m
  long s(0);                          // s: total names written so far
  for (long p = 0; p < n; p++) {      // For each day
    long x;                           // x: names to write on day p
    scanf("%ld", &x);                 // Read number of names for current day
    s += x;                           // Add to total names
    printf("%ld ", s / m);            // Print number of full pages turned (s divided by m)
    s %= m;                           // Keep only remaining names on current page (mod m)
  }
  puts("");                           // Newline at end
  return 0;
}
/*
Flowerbox:
Purpose: This code simulates writing names in a Death Note, calculating how many times pages are turned each day.
Algorithm: Greedy simulation where we track cumulative names and compute full pages turned per day.
Time Complexity: O(n), where n is the number of days.
Space Complexity: O(1), only using a constant amount of extra space.
*/

// https://github.com/VaHiX/codeForces/
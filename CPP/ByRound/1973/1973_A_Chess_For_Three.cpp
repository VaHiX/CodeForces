// Problem: CF 1973 A - Chess For Three
// https://codeforces.com/contest/1973/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    if ((a + b + c) % 2) { // If total points is odd, impossible to distribute evenly in valid games
      puts("-1");
      continue;
    }
    long x = (a + b + c) / 2; // Maximum possible draws: total points divided by 2 (since each draw gives 2 points total)
    long y = a + b;          // Sum of two smallest scores (maximum possible points from games between these players)
    printf("%ld\n", (x < y ? x : y)); // Take minimum to ensure valid number of draws
  }
}

// https://github.com/VaHiX/codeForces/
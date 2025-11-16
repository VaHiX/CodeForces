// Problem: CF 1039 A - Timetable
// https://codeforces.com/contest/1039/problem/A

/*
Algorithm/Technique: 
This problem involves constructing a valid timetable for bus arrivals given departure times and constraints on arrival order. 
The approach uses a difference array technique to track how many buses can arrive at each position, and then assigns arrival times accordingly.
The key idea is to ensure that each bus arrives at least 't' units of time after departure and that the maximum arrival position for each bus is respected.

Time Complexity: O(n)
Space Complexity: O(n)

*/
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <algorithm>

using namespace std;
typedef long long LL;
const int RLEN = 1 << 18 | 1;
inline char nc() {
  static char ibuf[RLEN], *ib, *ob;
  (ib == ob) && (ob = (ib = ibuf) + fread(ibuf, 1, RLEN, stdin));
  return (ib == ob) ? -1 : *ib++;
}
inline LL rd() {
  char ch = nc();
  LL i = 0, f = 1;
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = nc();
  }
  while (isdigit(ch)) {
    i = (i << 1) + (i << 3) + ch - '0';
    ch = nc();
  }
  return i * f;
}
const int N = 2e5 + 50;
int n, c[N], d[N];
LL t, a[N], x[N];
int main() {
  n = rd(), t = rd();
  for (int i = 1; i <= n; i++)
    a[i] = rd();
  for (int i = 1; i <= n; i++)
    if ((x[i] = rd()) < x[i - 1] || x[i] < i) {
      puts("No");
      return 0;
    }
  // Difference array technique to count how many buses can arrive at each position
  for (int i = 1; i <= n; i++)
    ++c[i], --c[x[i]], d[x[i]] = 1;
  d[n] = 0;
  for (int i = 1; i <= n; i++) {
    c[i] += c[i - 1];
    if (c[i] && d[i]) {
      puts("No");
      return 0;
    }
    // Set minimum valid arrival time based on next departure
    if (c[i])
      x[i] = a[i + 1] + t;
    // Ensure strictly increasing order of arrival times
    x[i] = max(x[i - 1] + 1, x[i]);
    // Ensure time constraint (each bus arrives at least t time units after departure)
    x[i] = max(x[i], a[i] + t);
    // Check if arrival time conflicts with previous constraints
    if (d[i] && x[i] >= a[i + 1] + t) {
      puts("No");
      return 0;
    }
  }
  puts("Yes");
  for (int i = 1; i <= n; i++)
    printf("%I64d ", x[i]);
}


// https://github.com/VaHiX/CodeForces/
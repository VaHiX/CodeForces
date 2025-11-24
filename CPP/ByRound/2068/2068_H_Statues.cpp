// Problem: CF 2068 H - Statues
// https://codeforces.com/contest/2068/problem/H

/*
H. Statues
Problem: Place n statues at integer coordinates forming a path with given distances.

Algorithms/Techniques:
- Greedy approach to assign coordinates
- Validation checks on total distance and feasibility

Time Complexity: O(n)
Space Complexity: O(n)

The first statue is placed at (0,0) and the last at (a,b).
Each consecutive pair of statues must be exactly d[i] Manhattan distance apart.
We simulate assigning coordinates greedily while ensuring constraints are satisfied.

*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define int long long
using namespace std;
int n, a, b, d[51];
signed main() {
  cin >> n >> a >> b;
  int sum = a + b; // total Manhattan distance from (0,0) to (a,b)
  for (int i = 1; i < n; i++)
    cin >> d[i], sum += d[i]; // accumulate total path length
  if (sum & 1) // if odd, impossible to split evenly
    puts("NO"), exit(0);
  if (sum - a - b < a + b) // check if remaining distance can be distributed
    puts("NO"), exit(0);
  for (int i = 1; i < n; i++)
    if (sum - d[i] < d[i]) // check if current segment is too large
      puts("NO"), exit(0);
  puts("YES");
  cout << 0 << " " << 0 << endl; // first statue at origin
  int tot = sum / 2 - a - b, x = 0, y = 0; // total remaining shift for balancing
  for (int i = 1; i < n; i++) {
    if (d[i] <= tot) { // if segment fits within allowed shift
      tot -= d[i];
      y -= d[i]; // move down (negative y)
    } else if (tot) { // partial fit
      if (d[i] - tot > a) { // not enough x to cover the rest
        x = tot + a;
        y += d[i] - tot - a;
      } else {
        x += d[i] - tot;
        y -= tot;
      }
      tot = 0;
    } else { // no more shift allowed
      if (x > a) { // already shifted too far right
        if (x - d[i] < a) { // can reduce shift
          y += d[i] - (x - a);
          x = a;
        } else {
          x -= d[i];
        }
      } else if (x < a) { // can shift more right
        if (x + d[i] > a) { // overshoots
          y += d[i] - (a - x);
          x = a;
        } else {
          x += d[i];
        }
      } else
        y += d[i]; // no x shift, increase y
    }
    cout << x << " " << y << endl; // output current statue's position
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
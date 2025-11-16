// Problem: CF 1840 G1 - In Search of Truth (Easy Version)
// https://codeforces.com/contest/1840/problem/G1

/*
Purpose:
This code solves an interactive problem where the goal is to determine the number of sectors 'n' in a circle, 
given that the sectors are numbered from 1 to n and an arrow initially points to some sector. 
The user can query moving the arrow clockwise or counterclockwise and observe the new sector number.
The approach uses random sampling to collect sector numbers and leverages their frequencies to deduce n.

Algorithms/Techniques:
- Randomized sampling using uniform distribution
- Tracking of sector numbers encountered via a map
- Using patterns in repeated sector numbers to estimate n

Time Complexity: O(1) average case for the number of operations due to random sampling and early termination.
Space Complexity: O(1) as the map stores at most a few hundred entries during the process.

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <map>
#include <random>

#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
int query(int x) {
  printf("+ %d\n", x);
  fflush(stdout);
  int t;
  scanf("%d", &t);
  return t;
}
mt19937 rnd(time(NULL));
map<int, int> val;
int main() {
  int T = 1;
  while (T--) {
    int x, now, mx;
    scanf("%d", &x), now = mx = x;
    // First phase: gather max sector value by querying random moves
    for (int i = 1; i <= 400; i++) {
      now = query(rnd() % 1000000000 + 1);
      mx = max(mx, now);
    }
    val[now] = 0;
    // Second phase: move 1 step each time and check for repeated values
    for (int i = 1; i <= 300; i++) {
      now = query(1);
      if (val.count(now)) {
        printf("! %d\n", i);
        exit(0);
      }
      val[now] = i;
    }
    // Third phase: use a sequence of moves to detect the cycle length
    for (int i = 0; i <= 300; i++) {
      now = query(i ? 300 : mx);
      if (val.count(now)) {
        printf("! %d\n", i * 300 + mx + 300 - val[now]);
        exit(0);
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
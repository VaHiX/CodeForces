// Problem: CF 2110 C - Racing
// https://codeforces.com/contest/2110/problem/C

/*
C. Racing
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm: Greedy with Stack
Approach:
- Process obstacles sequentially maintaining current height `h` and a stack of indices where `d[i] = -1`
- When encountering a `-1`, push index to stack (unknown step)
- When encountering a positive `d[i]`, increase height by that amount
- When insufficient height, greedily assign 1s to previous unknowns in the stack to make up the difference
- Ensure height stays within bounds [bl[p], bh[p]] at all times
- After processing, pop remaining stack elements and assign them 0
Time Complexity: O(n) - each element is pushed/poppped from stack at most once
Space Complexity: O(n) - for storing input data, stack

*/

#include <cstdio>
#include <stack>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> dv(n), bl(n), bh(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &dv[p]);
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld %ld", &bl[p], &bh[p]);
    }
    bool possible(true);
    std::stack<long> s;
    long h(0);
    for (long p = 0; possible && p < n; p++) {
      if (dv[p] < 0) { // If unknown step, push index to stack
        s.push(p);
      } else {
        h += dv[p]; // Add known height change to current height
      }
      while (!s.empty() && h < bl[p]) { // Not enough height to pass obstacle
        dv[s.top()] = 1; // Assign upward step to make up for deficit
        ++h;
        s.pop();
      }
      if (h < bl[p] || h > bh[p]) { // Height out of valid range
        possible = false;
        break;
      }
      while (h + s.size() > bh[p]) { // Too much potential height increase from stack
        dv[s.top()] = 0; // Assign no step to prevent overflow
        s.pop();
      }
    }
    if (!possible) {
      puts("-1");
      continue;
    }
    while (!s.empty()) { // Assign remaining unknowns as 0 (no steps)
      dv[s.top()] = 0;
      s.pop();
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", dv[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/
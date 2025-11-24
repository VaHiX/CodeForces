// Problem: CF 1253 B - Silly Mistake
// https://codeforces.com/contest/1253/problem/B

/*
B. Silly Mistake
Algorithm: This code uses a greedy approach with a set to track active employees and partitions the input into valid days.

Time Complexity: O(n log n) due to operations on std::set which are logarithmic.
Space Complexity: O(n) for storing the input events, the set, and the result vector.

The program processes events sequentially:
- Positive numbers represent entering employees
- Negative numbers represent leaving employees
- The program ensures each employee enters at most once per day, and leaves only if they entered
- When a complete valid day is formed (all employees who entered leave), it's recorded as a partition

*/
#include <cstdio>
#include <set>
#include <vector>
int main() {
  std::set<long> a, b;  // 'a' tracks currently present employees; 'b' tracks all employees seen in current day
  std::vector<long> d;  // Stores number of events per valid day
  long n;
  scanf("%ld", &n);
  bool res(true);       // Flag to track if partition is valid
  long cnt(0);          // Counter for events in current day
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    ++cnt;              // Increment event count for current day
    if (x > 0) {        // Employee enters
      if (b.count(x)) { // If already entered today, invalid
        res = false;
        break;
      }
      a.insert(x);      // Add to active employees
      b.insert(x);      // Mark as seen in current day
    } else {            // Employee leaves
      if (!(a.count(-x))) { // If not present, invalid
        res = false;
        break;
      }
      a.erase(-x);      // Remove from active employees
      if (a.size() == 0) { // If no one left, current day is complete
        d.push_back(cnt);
        cnt = 0;
        b.clear();      // Reset for next day
      }
    }
  }
  if (cnt > 0) {        // If current day incomplete at end, invalid
    res = false;
  }
  if (res) {
    printf("%ld\n", d.size());
    for (long p = 0; p < d.size(); p++) {
      printf("%ld ", d[p]);
    }
  } else {
    puts("-1");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
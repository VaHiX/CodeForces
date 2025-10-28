// Problem: CF 1690 C - Restoring the Duration of Tasks
// https://codeforces.com/contest/1690/problem/C

/*
C. Restoring the Duration of Tasks
Algorithm: Simulation of task queue processing with timing.
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing input and output vectors

The problem simulates a single-threaded scheduler where tasks are processed in order.
Each task has a start time (when it was given) and finish time (when it was completed).
We calculate the actual duration of each task based on when it started execution.

Key points:
- Tasks are executed sequentially
- If a new task arrives while another is running, it's queued
- When current task finishes, next in queue starts immediately
- Duration = finish_time - start_time_of_execution
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> s(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &s[p]);
    }
    std::vector<long> f(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &f[p]);
    }
    for (long p = 0; p < n; p++) {
      // Get the finish time of the previous task, or start time of first task
      long prev = (p > 0) ? f[p - 1] : s[0];
      // Start time of current task is max of previous finish time and current start time
      long start = (prev > s[p]) ? prev : s[p];
      // Duration is difference between finish time and computed start time
      printf("%ld ", f[p] - start);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/
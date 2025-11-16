// Problem: CF 1578 E - Easy Scheduling
// https://codeforces.com/contest/1578/problem/E

/*
E. Easy Scheduling
Purpose: Calculate the minimum number of time moments required to process all tasks in a full binary tree of height h with p processes available per moment.

Algorithms/Techniques:
- Simulate task scheduling on a full binary tree.
- Use a vector to store the number of ready tasks at each level.
- At each time step, determine how many tasks can be scheduled and update the count accordingly.

Time Complexity: O(h) per test case
Space Complexity: O(h) for storing node counts at each level

Input Format:
- t: number of test cases
- For each test case: h (height of binary tree), p (number of processes)

Output Format:
- Minimum time moments needed to schedule all tasks.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll h, r;
    scanf("%lld %lld", &h, &r);
    std::vector<ll> v(h);
    v[0] = 1; // Root has 1 task initially
    for (ll p = 1; p < h; p++) {
      v[p] = 2 * v[p - 1]; // Each level doubles the number of tasks from the previous level
    }
    ll total(0), prev(0);
    for (ll p = 0; p < h; p++) {
      v[p] -= prev; // Subtract previously scheduled tasks to get actual ready tasks at this level
      if (v[p] < r) {
        ++total; // If less than processes, only one time step needed
        continue;
      }
      total += (v[p] + r - 1) / r; // Calculate number of time steps needed for current level
      prev = (r - (v[p] % r)) % r; // Update remaining tasks that will be ready next step
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/
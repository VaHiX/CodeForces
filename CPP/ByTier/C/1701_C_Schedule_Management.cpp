// Problem: CF 1701 C - Schedule Management
// https://codeforces.com/contest/1701/problem/C

/*
Purpose: This program solves the task scheduling problem where each task must be assigned to a worker, and the goal is to minimize the total time to complete all tasks. 
         Each worker can only work on one task at a time, and a worker takes 1 hour if they are proficient in the task, otherwise 2 hours.

Algorithm:
- For each worker, count how many tasks they are proficient in (this helps in calculating how effectively they can work).
- Binary search on the minimum time to complete all tasks.
- For a given time 't', calculate how many tasks can be completed:
    - If a worker is proficient in a task, they take 1 hour.
    - If not proficient, they take 2 hours.
    - For a time limit 't', each worker can do at most 't' hours of work.
    - For a worker with 'k' proficient tasks, they can complete 'min(k, t)' proficient tasks in 't' time.
    - Remaining time can be used to do non-proficient tasks, which take 2 hours each.
    - So, total tasks that worker can handle = min(k, t) + (t - min(k, t)) / 2

Time Complexity: O(n * log(2*m)) where n is number of workers and m is number of tasks
Space Complexity: O(n + m) for storing the input and auxiliary arrays
*/

#include <algorithm>
#include <iostream>
#include <vector>

typedef long long ll;
using namespace std;

int main() {
  int m;
  cin >> m;
  while (m--) {
    ll n, t;
    cin >> n >> t;
    vector<int> v(t);
    vector<ll> v1(n, 0);  // Count of tasks each worker is proficient in
    
    // Read tasks and update proficiency count
    for (int &x : v) {
      cin >> x;
      x--;  // Convert to 0-based indexing
      v1[x]++;
    }
    
    // Binary search on the answer
    ll s = 0, e = 2 * t;  // Lower and upper bounds for time
    
    while (s + 1 < e) {
      ll m = (s + e) / 2;  // Midpoint of the search range
      ll k = 0;  // Total tasks that can be completed in time 'm'
      
      // For each worker, calculate how many tasks can be done in 'm' time
      for (int i = 0; i < n; i++) {
        ll eff = min(v1[i], m);  // Number of proficient tasks this worker can do
        k += eff;
        k += (m - eff) / 2;  // Remaining time can be used to do non-proficient tasks (each takes 2 hours)
      }
      
      // If we can complete all tasks in 'm' time
      if (k >= t) {
        e = m;
      } else {
        s = m;
      }
    }
    
    cout << e << '\n';  // Minimum time required
  }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 644 B - Processing Queries
// https://codeforces.com/contest/644/problem/B

/*
B. Processing Queries
time limit per test
5 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
In this problem you have to simulate the workflow of one-thread server. There are 
n
 queries to process, the 
i
-th will be received at moment 
t
i
 and needs to be processed for 
d
i
 units of time. All 
t
i
 are guaranteed to be distinct.
When a query appears server may react in three possible ways: 
 
 If server is free and query queue is empty, then server immediately starts to process this query. 
 If server is busy and there are less than 
b
 queries in the queue, then new query is added to the end of the queue. 
 If server is busy and there are already 
b
 queries pending in the queue, then new query is just rejected and will never be processed. 
As soon as server finished to process some query, it picks new one from the queue (if it's not empty, of course). If a new query comes at some moment 
x
, and the server finishes to process another query at exactly the same moment, we consider that first query is picked from the queue and only then new query appears.
For each query find the moment when the server will finish to process it or print 
-1
 if this query will be rejected.

Algorithm: Simulation using a queue to manage tasks and track execution times.
Time Complexity: O(n)
Space Complexity: O(n + b) where n is number of queries and b is queue capacity.
*/

#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

typedef long long ll;
int main() {
  ll n, b;
  scanf("%lld %lld", &n, &b);
  std::queue<std::pair<ll, ll>> q; // Queue stores {query_index, duration}
  std::vector<ll> f(n);            // Array to store finish times
  ll t(0);                         // Current time
  for (ll p = 0; p < n; p++) {
    ll arr, dur;
    scanf("%lld %lld", &arr, &dur);
    // Process all tasks that can be completed before or at arrival time of current task
    while (!q.empty() && t <= arr) {
      std::pair<ll, ll> task = q.front();
      q.pop();
      t += task.second;         // Update current time by task duration
      f[task.first] = t;        // Store finish time for this task
    }
    t = (t > arr) ? t : arr;    // Ensure t is at least the arrival time of current task
    if (q.size() < b) {         // If queue has space, add current task
      q.push(std::make_pair(p, dur));
    } else {
      f[p] = -1;                // Reject task due to full queue
    }
  }
  // Process remaining tasks in the queue
  while (!q.empty()) {
    std::pair<ll, ll> task = q.front();
    q.pop();
    t += task.second;
    f[task.first] = t;
  }
  for (ll p = 0; p < n; p++) {
    printf("%lld ", f[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/
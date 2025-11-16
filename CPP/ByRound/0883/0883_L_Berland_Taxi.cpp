// Problem: CF 883 L - Berland.Taxi
// https://codeforces.com/contest/883/problem/L

/*
 * Problem: Berland.Taxi - Assign taxis to passengers according to specific rules
 * 
 * Algorithms/Techniques:
 * - Segment Tree with Binary Indexed Tree (BIT) for efficient range queries and updates
 * - Priority Queues for managing car availability and ride scheduling
 * - Two-pointer technique with binary search for finding closest available cars
 * 
 * Time Complexity: O(m * log(n) * log(n)) where m is number of requests and n is number of houses
 * Space Complexity: O(n + m) for BIT storage and priority queues
 * 
 * Key Implementation Details:
 * - Cars are tracked using a segment tree (BIT) to efficiently query available positions
 * - Priority queues manage car availability based on time and car number
 * - Binary search is used to find closest available car to pickup location
 * - The solution handles multiple concurrent requests and delayed assignments
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>

using namespace std;
int n, k, m;
inline int lowbit(int x) { return x & (-x); }
class C1 {
public:
  int id;
  long long tim;
  bool operator<(const C1 &c) const {
    if (tim != c.tim)
      return tim > c.tim;
    return id > c.id;
  }
};
class C2 {
public:
  int id, des;
  long long tim;
  bool operator<(const C2 &c) const { return tim > c.tim; }
};
priority_queue<C1> q[200010]; // Priority queue for available cars at each house
priority_queue<C2> run; // Priority queue for cars currently on rides
class tree {
public:
  int dat[200010];
  inline void modify(int p, int v) {
    // Update BIT at position p by adding value v
    for (; p <= n; p += lowbit(p))
      dat[p] += v;
  }
  inline int query(int r) {
    // Query prefix sum from 1 to r
    int out = 0;
    for (; r; r -= lowbit(r))
      out += dat[r];
    return out;
  }
  inline int query(int l, int r) { return query(r) - query(l - 1); } // Range query
} T;
inline int getlft(int pos) {
  // Find leftmost available position to the left of pos
  int L = 1, R = pos, out = 0;
  while (L <= R) {
    int mid = (L + R) >> 1;
    if (T.query(mid, pos))
      out = mid, L = mid + 1;
    else
      R = mid - 1;
  }
  return out;
}
inline int getrgt(int pos) {
  // Find rightmost available position to the right of pos
  int L = pos, R = n, out = 0;
  while (L <= R) {
    int mid = (L + R) >> 1;
    if (T.query(pos, mid))
      out = mid, R = mid - 1;
    else
      L = mid + 1;
  }
  return out;
}
long long tim;
int a, b;
int main() {
  long long now = 0;
  scanf("%d%d%d", &n, &k, &m);
  for (int i = 1, ti; i <= k; i++) {
    scanf("%d", &ti);
    T.modify(ti, 1); // Mark initial car positions as available
    q[ti].push((C1){i, 0}); // Push car to its initial position priority queue
  }
  while (m--) {
    scanf("%lld%d%d", &tim, &a, &b);
    now = max(now, tim); // Current time is max of now and request time
    // Update all cars that have finished their rides by current time
    while (!run.empty() && run.top().tim <= now) {
      C2 tmp = run.top();
      run.pop();
      T.modify(tmp.des, 1); // Mark destination as available
      q[tmp.des].push((C1){tmp.id, tmp.tim}); // Add car to available queue at destination
    }
    // Check if we need to advance time due to queue being full (for tie-breaking)
    if (run.size() == k) {
      now = max(now, run.top().tim);
      while (!run.empty() && run.top().tim <= now) {
        C2 tmp = run.top();
        run.pop();
        T.modify(tmp.des, 1);
        q[tmp.des].push((C1){tmp.id, tmp.tim});
      }
    }
    // Find closest available cars to pickup location a
    int L = getlft(a), R = getrgt(a);
    C1 tmp;
    if (L) { // There are available cars to the left
      if (R) { // There are available cars to the right too
        // Choose car based on distance and tie-breaking rules
        if (a - L < R - a || (a - L == R - a && q[R].top() < q[L].top())) {
          T.modify(L, -1); // Remove car from left position
          tmp = q[L].top();
          q[L].pop();
          printf("%d %lld\n", tmp.id, now + a - L - tim); // Output car id and wait time
          run.push((C2){tmp.id, b, now + a - L + abs(b - a)}); // Schedule ride completion
        } else {
          T.modify(R, -1); // Remove car from right position
          tmp = q[R].top();
          q[R].pop();
          printf("%d %lld\n", tmp.id, now + R - a - tim);
          run.push((C2){tmp.id, b, now + R - a + abs(b - a)});
        }
      } else {
        T.modify(L, -1); // Only left cars available
        tmp = q[L].top();
        q[L].pop();
        printf("%d %lld\n", tmp.id, now + a - L - tim);
        run.push((C2){tmp.id, b, now + a - L + abs(b - a)});
      }
    } else {
      T.modify(R, -1); // Only right cars available
      tmp = q[R].top();
      q[R].pop();
      printf("%d %lld\n", tmp.id, now + R - a - tim);
      run.push((C2){tmp.id, b, now + R - a + abs(b - a)});
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/
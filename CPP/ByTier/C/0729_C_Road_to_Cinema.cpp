// Problem: CF 729 C - Road to Cinema
// https://codeforces.com/contest/729/problem/C

/*
 * Problem: Road to Cinema
 * Algorithm: Binary search on tank capacity + greedy validation
 * Time Complexity: O(n * log(max_capacity) + k * log(k))
 * Space Complexity: O(k)
 * 
 * Approach:
 * 1. Sort gas station positions.
 * 2. Binary search on the minimum required fuel tank capacity.
 * 3. For each capacity, validate if it's possible to reach cinema in time using greedy strategy:
 *    - If tank capacity is >= 2*distance, use normal mode (1 min/km, 1 liter/km).
 *    - Else, use a combination of accelerated and normal modes.
 * 4. Among all cars that satisfy the minimum required capacity, pick the one with minimum price.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

// Function to check if a car with given tank capacity can reach cinema in time
bool check(const std::vector<long> pos, long t, long cap) {
  long totalTime(0);
  for (long p = 1; p < pos.size(); p++) {
    long dist = pos[p] - pos[p - 1];
    if (cap < dist) {
      return false;  // Not enough capacity to cover the distance
    } else if (cap >= 2 * dist) {
      // If we can cover entire distance in normal mode
      totalTime += dist;
    } else {
      // We must use a mix of modes:
      // Use accelerated mode for (2*dist - cap) km (2 minutes/km, 2 liters/km)
      // Use normal mode for (cap - dist) km (1 minute/km, 1 liter/km)
      totalTime += 2 * (2 * dist - cap) + (cap - dist);
    }
    if (totalTime > t) {
      return false;  // Exceeds time limit
    }
  }
  return (totalTime <= t);
}

int main() {
  long n, k, s, t;
  scanf("%ld %ld %ld %ld", &n, &k, &s, &t);
  std::vector<std::pair<long, long>> cars(n);
  for (long p = 0; p < n; p++) {
    long c, v;
    scanf("%ld %ld", &c, &v);
    cars[p] = std::make_pair(c, v);  // Store price and capacity
  }
  std::vector<long> pos(k + 2);
  pos[0] = 0;
  for (long p = 1; p <= k; p++) {
    long x;
    scanf("%ld", &x);
    pos[p] = x;
  }
  pos[k + 1] = s;
  sort(pos.begin(), pos.end());  // Sort gas stations by position

  long cap(1e9 + 10), m(0), M(1e9 + 10);
  while (m <= M) {
    long test = (m + M) / 2;
    if (check(pos, t, test)) {
      cap = test;
      M = test - 1;
    } else {
      m = test + 1;
    }
  }
  
  long minPrice(-1);
  for (long p = 0; p < n; p++) {
    if (cars[p].second < cap) {
      continue;  // Skip cars with insufficient capacity
    }
    if ((minPrice < 0) || cars[p].first < minPrice) {
      minPrice = cars[p].first;  // Found a cheaper suitable car
    }
  }
  printf("%ld\n", minPrice);
  return 0;
}


// https://github.com/VaHiX/CodeForces/
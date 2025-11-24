// Problem: CF 1148 B - Born This Way
// https://codeforces.com/contest/1148/problem/B

/*
B. Born This Way
Algorithm: Two-pointer technique with greedy approach
Time Complexity: O(n + m)
Space Complexity: O(n + m)

Arkady bought an air ticket from a city A to a city C. Unfortunately, there are no direct flights,
but there are a lot of flights from A to a city B, and from B to C.
There are n flights from A to B, they depart at time moments a_1, a_2, ..., a_n and arrive at B t_a moments later.
There are m flights from B to C, they depart at time moments b_1, b_2, ..., b_m and arrive at C t_b moments later.
The connection time is negligible, so one can use the i-th flight from A to B and the j-th flight from B to C 
if and only if b_j >= a_i + t_a.

You can cancel at most k flights. If you cancel a flight, Arkady can not use it.
Arkady wants to be in C as early as possible, while you want him to be in C as late as possible.
Find the earliest time Arkady can arrive at C, if you optimally cancel k flights. 
If you can cancel k or less flights in such a way that it is not possible to reach C at all, print -1.

Input:
The first line contains five integers n, m, t_a, t_b and k (1 <= n, m <= 2*10^5, 1 <= k <= n + m, 1 <= t_a, t_b <= 10^9)
The second line contains n distinct integers in increasing order a_1, a_2, ..., a_n (1 <= a_1 < a_2 < ... < a_n <= 10^9) 
The third line contains m distinct integers in increasing order b_1, b_2, ..., b_m (1 <= b_1 < b_2 < ... < b_m <= 10^9)
Output:
If you can cancel k or less flights in such a way that it is not possible to reach C at all, print -1.
Otherwise print the earliest time Arkady can arrive at C if you cancel k flights in such a way that maximizes this time.
*/

#include <cstdio>
#include <vector>
int main() {
  long n, m, ta, tb, k;
  scanf("%ld %ld %ld %ld %ld", &n, &m, &ta, &tb, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b(m);
  for (long p = 0; p < m; p++) {
    scanf("%ld", &b[p]);
  }
  long idx(0), mxt(0); // idx: current index in array b; mxt: maximum arrival time
  if (k >= n || k >= m) { // If we can cancel more flights than available, impossible to reach
    mxt = -1;
  }
  for (long p = 0; p < n && p <= k && mxt >= 0; p++) { // Try all valid combinations of cancelling at most k flights
    const long arv = a[p] + ta; // Time when we arrive at B after taking p-th flight from A
    const long rem = k - p; // Remaining number of flights we can cancel
    while ((idx + 1 < m) && b[idx] < arv) { // Find the first flight in B that departs after arv
      ++idx;
    }
    if (arv <= b[idx] && (idx + rem < m)) { // Check if valid connection with remaining flights
      const long tmp = b[idx + rem] + tb; // Arrival time at C using the flight from B to C
      mxt = (mxt > tmp) ? mxt : tmp; // Update maximum arrival time
    } else {
      mxt = -1; // No valid connection, impossible to reach C
      break;
    }
  }
  printf("%ld\n", mxt);
  return 0;
}


// https://github.com/VaHiX/codeForces/
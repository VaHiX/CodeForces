// Problem: CF 1059 A - Cashier
// https://codeforces.com/contest/1059/problem/A

/*
Algorithm: Greedy
  - We iterate through each customer and calculate the time slots available between customers,
    where Vasya can take breaks.
  - For each gap between two consecutive customers (or from start to first customer, or from last customer to end),
    we compute how many breaks of duration 'a' fit in that interval.
  - The final gap (from last customer to end of workday) is also considered.

Time Complexity: O(n)
Space Complexity: O(1)

Problem Description:
Vasya works L minutes a day and serves n customers. Each customer arrives at time t_i and takes l_i minutes.
He can take smoke breaks of exactly a minutes each, but must not be absent during any customer service times.
Goal: Maximize the number of smoke breaks he can take.

Input Format:
- First line: n L a (number of customers, workday length, break duration)
- Next n lines: t_i l_i (customer arrival time and service duration)

Output Format:
Maximum number of breaks Vasya can take.
*/

#include <cstdio>
int main() {
  long n, L, a;
  scanf("%ld %ld %ld", &n, &L, &a);
  long cur(0), cnt(0); // cur tracks current time, cnt counts breaks
  while (n--) {
    long t, l;
    scanf("%ld %ld", &t, &l);
    cnt += (t - cur) / a; // Count breaks in the gap before this customer
    cur = t + l; // Update current time to end of this customer's service
  }
  cnt += (L - cur) / a; // Count breaks in final gap from last customer to end of day
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/
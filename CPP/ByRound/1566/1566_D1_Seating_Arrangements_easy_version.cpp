// Problem: CF 1566 D1 - Seating Arrangements (easy version) 
// https://codeforces.com/contest/1566/problem/D1

/*
D1. Seating Arrangements (easy version) 
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

This problem involves assigning seats to people in a cinema such that:
- Seats are arranged in n rows and m columns
- Lower sight level person gets a better (lower) seat index
- Each person's inconvenience is the number of occupied seats they pass through while walking to their seat
- Goal: minimize total inconvenience

Algorithm:
The key idea is to assign seats based on the order of sight levels. Since n=1, we only have one row.
We use a greedy approach where we process people in increasing order of their sight levels.
For each person, when they are assigned a seat, we count how many previously seated people
have lower seat indices than the current one (i.e., how many occupied seats they will pass through).
This is done by iterating over all existing seats and counting those less than current seat.

Time Complexity: O(m^2) per test case, since for each of m people we might scan all previously placed seats.
Space Complexity: O(m), for storing the vector of already assigned seats.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> v; // Vector to store assigned seat indices in order
    long cnt(0);         // Total inconvenience counter
    while (m--) {
      long x;
      scanf("%ld", &x);
      // For each previously assigned seat, if it's less than current seat index,
      // it contributes 1 to the inconvenience of the current person
      for (long p = 0; p < v.size(); p++) {
        cnt += (v[p] < x);
      }
      v.push_back(x); // Add current seat index to list of assigned seats
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/
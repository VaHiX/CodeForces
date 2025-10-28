// Problem: CF 1462 D - Add to Neighbour and Remove
// https://codeforces.com/contest/1462/problem/D

/*
 * Problem: D. Add to Neighbour and Remove
 *
 * Purpose: Given an array of integers, determine the minimum number of operations
 *          required to make all elements equal by selecting an element and adding
 *          it to one of its neighbors, then removing the selected element.
 *
 * Algorithm:
 * - For each test case, compute prefix sums and store them in a set for fast lookup.
 * - Try all possible final values (divisors of total sum) that could make all elements equal.
 * - For each candidate value, use the prefix sums to validate if it's possible to split
 *   array into equal parts with that value.
 * - Return the minimum number of operations needed across all valid candidates.
 *
 * Time Complexity: O(n^2) per test case in worst case due to checking divisors and prefix sums.
 * Space Complexity: O(n) for storing arrays and sets.
 */

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1, 0), b(n + 1, 0); // a: input array, b: prefix sums
    std::set<long> cs; // stores all prefix sums for quick lookup
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
      b[p] = b[p - 1] + a[p]; // compute prefix sum
      cs.insert(b[p]);
    }
    long total = b.back(); // total sum of the array
    long res(n - 1);       // initialize result to maximum possible operations (n-1)
    for (long p = 1; p <= n; p++) {
      if (total % b[p]) { // if total is not divisible by prefix sum, skip
        continue;
      }
      long cnt = total / b[p]; // number of equal parts we want to form
      bool possible(true);
      for (long mult = 2; mult < cnt; mult++) {
        if (cs.count(mult * b[p]) == 0) { // check whether all needed prefix sums exist
          possible = false;
          break;
        }
      }
      if (possible) {
        res = n - cnt; // minimum operations = original length - number of parts
        break;
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/
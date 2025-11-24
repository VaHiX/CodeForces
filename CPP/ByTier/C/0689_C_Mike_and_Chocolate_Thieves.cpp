// Problem: CF 689 C - Mike and Chocolate Thieves
// https://codeforces.com/contest/689/problem/C

/*
C. Mike and Chocolate Thieves
Algorithm: Binary search on answer
Time Complexity: O(log^2(max_n) * log(max_n)) where max_n is ~1e18
Space Complexity: O(1)

The problem involves finding the smallest possible value of n such that there are exactly m ways 
to distribute chocolates among 4 thieves where each thief takes k times more than the previous one,
and each thief's bag holds at most n chocolates.

Key idea:
- For a fixed n, we count how many valid sequences (a, ka, k^2*a, k^3*a) exist such that all terms are <= n.
- This is done by iterating over possible values of k (starting from 2) and counting valid sequences.
- We use binary search on the answer to find the smallest n with exactly m ways.

The function 'check' counts how many valid triples (with corresponding fourth term) can fit under a given number,
and compares it to the target number of ways m.
Then we do another binary search on n to find correct value.
*/

#include <stdint.h>
#include <iostream>

int sgn(int64_t x) {
  if (x == 0) {
    return 0;
  } else if (x < 0) {
    return -1;
  } else {
    return 1;
  }
}

// Function to count valid ways for a given max value 'num'
int check(int64_t ways, int64_t num) {
  int64_t total(0);
  for (int64_t p = 2; p * p * p <= num; p++) { // Iterate through possible base k values
    total += (num / (p * p * p)); // Count number of valid sequences with base k
  }
  return sgn(total - ways); // Return sign of difference between count and target
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t m;
  std::cin >> m;
  int64_t left(0), right(1e18); // Binary search range over possible n values

  while (left <= right) {
    int64_t mid = (left + right) / 2; // Midpoint in binary search
    if (check(m, mid) >= 0) { // If count of valid sequences is >= target m
      right = mid - 1; // Try smaller n
    } else {
      left = mid + 1; // Try larger n
    }
  }

  std::cout << ((check(m, left) == 0) ? left : -1) << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/
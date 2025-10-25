// Problem: CF 1277 B - Make Them Odd
// https://codeforces.com/contest/1277/problem/B

/*
B. Make Them Odd
Problem Description:
Given an array of positive integers, we want to make all elements odd by performing operations.
Each operation allows us to choose any even number c and divide all occurrences of c by 2.
We need to find the minimum number of such operations.

Algorithm:
- For each test case, process only even numbers and use a greedy approach with a set.
- Use a set to maintain current even numbers in descending order (rbegin() gives largest).
- In each step, take the largest even number, reduce it by half, and insert back if still even.
- Count total moves needed.

Time Complexity: O(n * log(max(a_i))) where n is the total number of elements across all test cases,
                 and max(a_i) is the maximum value in input.

Space Complexity: O(n), for storing the set of even numbers.

*/
#include <cstdio>
#include <set>
#include <iterator>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> s; // Store even numbers in descending order
    long cnt(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2 == 0) { // Only consider even numbers
        s.insert(x);
      }
    }
    while (s.size()) {
      long x = *(s.rbegin()); // Get the largest element in set
      s.erase(x); // Remove it from set
      ++cnt; // Increment move count
      x /= 2; // Divide by 2
      if (x % 2 == 0) { // If result is still even, insert back into set
        s.insert(x);
      }
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
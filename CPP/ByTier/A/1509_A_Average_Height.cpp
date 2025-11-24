// Problem: CF 1509 A - Average Height
// https://codeforces.com/contest/1509/problem/A

/*
Algorithm: Greedy arrangement of heights to maximize photogenic pairs
Approach:
- For a pair of heights to be photogenic, their average must be an integer.
- This happens when the sum of the two heights is even.
- The sum of two numbers is even if and only if both are even or both are odd.
- To maximize photogenic pairs, we can arrange all odd numbers first, then all even numbers.
  This maximizes the number of adjacent pairs that are both odd (since odd + odd = even),
  and minimizes the number of adjacent pairs that are odd and even (which are not photogenic).

Time Complexity: O(n) per test case, where n is the number of members.
Space Complexity: O(n) for storing even numbers in a vector.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> evens;  // Vector to store even numbers
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2) {  // If x is odd
        printf("%ld ", x);  // Print odd number immediately
      } else {  // If x is even
        evens.push_back(x);  // Store even number in vector
      }
    }
    for (long p = 0; p < evens.size(); p++) {
      printf("%ld ", evens[p]);  // Print all even numbers
    }
    puts("");  // Print newline at end of test case
  }
}


// https://github.com/VaHiX/CodeForces/
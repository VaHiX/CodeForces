// Problem: CF 1933 C - Turtle Fingers: Count the Values of k
// https://codeforces.com/contest/1933/problem/C

/*
C. Turtle Fingers: Count the Values of k
Algorithms/Techniques: Factorization, Set-based Unique Value Tracking

Time Complexity: O(log_a(l) * log_b(l) * log(l))
Space Complexity: O(log_a(l) * log_b(l))

The problem asks to count distinct values of k such that l = k * a^x * b^y for non-negative integers x and y.
The approach is to iterate over all possible powers of b that divide g (where g = l), then for each such power,
we compute the remaining quotient and repeatedly divide it by a to get all possible values of k.
We use a set to store unique k values.

Key steps:
1. For each power of b that divides g, compute g / b^i
2. From this quotient, keep dividing by a to find all divisors in form of k * a^x
3. Store these final k values in a set to count unique ones

*/
#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, g;
    scanf("%ld %ld %ld", &a, &b, &g);
    long div(1); // Start with b^0 = 1
    std::set<long> s; // Set to store unique k values
    while (g % div == 0) { // While div divides g
      long cur = g / div; // Current quotient after dividing by b^i
      s.insert(cur); // Insert this quotient (potential k)
      while (cur % a == 0) { // Keep dividing by a as long as possible
        s.insert(cur / a); // Add next possible k value
        cur /= a;
      }
      div *= b; // Move to next power of b
    }
    printf("%ld\n", s.size()); // Print number of unique k values
  }
}


// https://github.com/VaHiX/codeForces/
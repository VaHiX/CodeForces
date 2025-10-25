// Problem: CF 1656 B - Subtract Operation
// https://codeforces.com/contest/1656/problem/B

/*
B. Subtract Operation
Algorithms/Techniques: Set usage, Iteration
Time Complexity: O(n log n) per test case
Space Complexity: O(n) per test case

Given a list of integers and a target value k, determine if there exists a sequence of 
n-1 operations such that the final remaining element is exactly k. Each operation involves
removing an element x and subtracting x from all other elements.

The key insight is to check whether there exists a pair of elements (a, b) in the set
such that a - b = k. This corresponds to removing one element, then another, resulting 
in a difference equal to k.

We use a set to store unique elements for efficient lookup.
*/
#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::set<long> s;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s.insert(x); // Insert elements into set to get unique values
    }
    bool res(false);
    for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {
      if (s.count(k + *it)) { // Check if there exists an element such that current - element = k
        res = true;
        break;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/
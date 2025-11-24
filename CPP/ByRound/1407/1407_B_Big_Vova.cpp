// Problem: CF 1407 B - Big Vova
// https://codeforces.com/contest/1407/problem/B

#include <cstdio>
#include <set>
#include <vector>
// Purpose: This code solves the problem of arranging a sequence of integers to maximize
//          the lexicographically maximal GCD sequence formed by taking GCD of prefixes.
// Algorithm: Greedily select the next element that maximizes the GCD of the prefix.
//            We maintain a multiset of available numbers and at each step, we pick
//            the number which gives the highest GCD with the last added number.
// Time Complexity: O(n^2 * log n) in the worst case due to nested loops and multiset operations.
// Space Complexity: O(n) for storing the input and output sequences.

long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::multiset<long> a; // Store all numbers in a multiset for efficient lookup and removal
    std::vector<long> b;   // Store the resulting permutation
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      a.insert(x); // Insert all numbers into the multiset
    }
    long last(0); // Keep track of the GCD of the prefix built so far
    while (!a.empty()) {
      long best(0), argbest(0);
      // Iterate through all remaining elements to find the one which maximizes GCD
      for (std::multiset<long>::iterator it = a.begin(); it != a.end(); it++) {
        long test = gcd(last, *it);
        if (test >= best) {
          best = test;
          argbest = *it;
        }
      }
      b.push_back(argbest);       // Add the best number to the result
      a.erase(a.find(argbest));   // Remove it from available numbers
      last = gcd(last, argbest);  // Update the prefix GCD
    }
    for (long p = 0; p < b.size(); p++) {
      printf("%ld ", b[p]);   // Print the final permutation
    }
    puts("");
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/
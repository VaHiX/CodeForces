// Problem: CF 1348 B - Phoenix and Beauty
// https://codeforces.com/contest/1348/problem/B

/*
Code Purpose:
This code solves the problem of making an array "beautiful" by inserting integers such that all subarrays of length k have the same sum.
The approach uses a set to determine unique elements and checks if it's possible to build a beautiful array.
If possible:
- It constructs a beautiful array by repeating the unique elements and padding with 1s to make each subarray of length k have equal sum.
- The result is a concatenation of multiple repetitions of the set elements, followed by padding 1s.

Algorithms/Techniques:
- Set usage to find unique elements.
- Greedy repetition and padding strategy.
- Simulation of array construction.

Time Complexity: O(n * k * log(n)) 
  - The outer loop runs n times, and the inner loop (iterating through the set) takes O(log(n)) time.
  - For each element in the array, the nested loops and printing take O(k) time.
Space Complexity: O(n) 
  - The set stores at most n unique elements.
*/
#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::set<long> s; // Set to store unique elements in the array
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s.insert(x); // Insert elements into the set to get unique values
    }
    if (s.size() > k) { // If number of unique elements exceeds k, impossible to make beautiful
      puts("-1");
      continue;
    }
    printf("%ld\n", n * k); // Length of the new beautiful array
    for (long p = 0; p < n; p++) {
      for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {
        printf("%ld ", *it); // Print each unique element from the set
      }
      for (long q = 0; q + s.size() < k; q++) {
        printf("1 "); // Pad with 1s to make subarrays of length k
      }
    }
    puts(""); // Print newline at the end of the array
  }
}


// https://github.com/VaHiX/CodeForces/
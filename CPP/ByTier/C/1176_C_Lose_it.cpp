// Problem: CF 1176 C - Lose it!
// https://codeforces.com/contest/1176/problem/C

/*
C. Lose it!
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
You are given an array a consisting of n integers. Each a_i is one of the six following numbers: 4, 8, 15, 16, 23, 42.
Your task is to remove the minimum number of elements to make this array good.
An array of length k is called good if k is divisible by 6 and it is possible to split it into k/6 subsequences 4, 8, 15, 16, 23, 42.

Algorithms/Techniques: Greedy approach with tracking counts of each element in sequence order.
Time Complexity: O(n), where n is the number of elements in input array.
Space Complexity: O(1), since we use fixed-size vectors of size 6 and 7 regardless of input size.

*/
#include <cstdio>
#include <vector>
int main() {
  std::vector<long> a(6); // Vector to store the required sequence: 4, 8, 15, 16, 23, 42
  a[0] = 4;
  a[1] = 8;
  a[2] = 15;
  a[3] = 16;
  a[4] = 23;
  a[5] = 42;
  long n;
  scanf("%ld", &n); // Read number of elements in input array
  std::vector<long> s(7); // Vector to track how many of each element we need to complete sequences; s[6] is for counting completed sequences.
  s[0] = n; // Initially, n elements are "available" to start forming a sequence (this count will decrease)
  for (long p = 0; p < n; p++) { // Process each input element
    long x;
    scanf("%ld", &x); // Read current element from input
    for (long u = 0; u < 6; u++) { // Iterate through the required sequence to check matching element
      if (x == a[u] && s[u] > 0) { // If current element matches and we still need this element to form a subsequence
        --s[u]; // Decrement the count of the element we used
        ++s[u + 1]; // Increment the count for the next element in sequence (since we are forming one more part of the subsequence)
        break; // Break after matching once to avoid redundant checks
      }
    }
  }
  printf("%ld\n", n - 6 * s.back()); // Output number of elements to remove: total minus 6 times number of completed subsequences
  return 0;
}


// https://github.com/VaHiX/codeForces/
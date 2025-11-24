// Problem: CF 1692 B - All Distinct
// https://codeforces.com/contest/1692/problem/B

/*
B. All Distinct
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Algorithm: 
- Count frequency of each element in the array.
- For each unique element, track how many times it appears (frequency).
- The number of elements with odd frequency contributes 1 to the result,
  and elements with even frequency contribute 0 if we pair them all up;
  but if there are an odd number of such elements, one additional element remains unpaired.
- In the end, the maximum possible length of array with all distinct elements is:
  total unique elements - (number of even-frequency groups % 2)

Time Complexity: O(n log n) due to map operations (insertion and traversal)
Space Complexity: O(n) for storing frequency counts in map

Sho has an array a consisting of n integers. An operation consists of choosing two distinct indices i and j and removing a_i and a_j from the array.
After he made some operations, Sho has an array that has only distinct elements. In addition, he made operations such that the resulting array is the longest possible.
More formally, the array after Sho has made his operations respects these criteria:
No pairs such that (i < j) and a_i = a_j exist.
The length of a is maximized.
Output the length of the final array.

Input:
The first line contains a single integer t (1 <= t <= 10^3) — the number of test cases.
The first line of each test case contains a single integer n (1 <= n <= 50) — the length of the array.
The second line of each test case contains n integers a_i (1 <= a_i <= 10^4) — the elements of the array.

Output:
For each test case, output a single integer — the length of the final array.
Remember that in the final array, all elements are different, and its length is maximum.
*/
#include <cstdio>
#include <map>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> cnt; // Count frequency of each element
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++cnt[x]; // Increment count for element x
    }
    long odds(0), evens(0); // Count how many elements have odd/even frequencies
    for (std::map<long, long>::iterator it = cnt.begin(); it != cnt.end();
         it++) {
      long u = it->second; // Get frequency of current element
      if (u % 2) { // If frequency is odd
        ++odds;
      } else { // If frequency is even
        ++evens;
      }
    }
    // Final answer: total unique elements minus parity of even-frequency groups
    printf("%ld\n", odds + evens - (evens % 2));
  }
}


// https://github.com/VaHiX/codeForces/
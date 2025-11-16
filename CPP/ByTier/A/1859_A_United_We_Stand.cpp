// Problem: CF 1859 A - United We Stand
// https://codeforces.com/contest/1859/problem/A

/*
Purpose: This code solves the problem of partitioning an array into two non-empty subsets such that no element in subset b divides any element in subset c, and vice versa.

Algorithm:
- For each test case, we read the array of integers.
- We find the maximum element in the array.
- We partition the array into two subsets:
  - Subset b: contains all elements less than the maximum.
  - Subset c: contains all elements equal to the maximum.
- If subset b is not empty, we output the sizes and elements of both subsets.
  Otherwise, we output -1, indicating no valid partition exists.

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) for storing the input array and the two result arrays.

Techniques:
- Single pass through the array to find max and partition elements.
- Simple greedy partitioning based on comparison with maximum element.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    long mx(0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      mx = (mx > a[p]) ? mx : a[p]; // Find the maximum element
    }
    std::vector<long> b, c;
    for (long p = 0; p < n; p++) {
      if (a[p] < mx) {
        b.push_back(a[p]); // Add elements less than max to b
      } else {
        c.push_back(a[p]); // Add elements equal to max to c
      }
    }
    if (b.size()) { // If b is not empty, output the solution
      printf("%ld %ld\n", b.size(), c.size());
      for (long p = 0; p < b.size(); p++) {
        printf("%ld ", b[p]);
      };
      puts(""); // Print newline after b's elements
      for (long p = 0; p < c.size(); p++) {
        printf("%ld ", c[p]);
      };
      puts(""); // Print newline after c's elements
    } else {
      puts("-1"); // No valid partition exists if b is empty
    }
  }
}


// https://github.com/VaHiX/CodeForces/
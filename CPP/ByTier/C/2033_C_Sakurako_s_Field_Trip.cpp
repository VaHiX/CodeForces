// Problem: CF 2033 C - Sakurako's Field Trip
// https://codeforces.com/contest/2033/problem/C

/*
C. Sakurako's Field Trip

Purpose:
This program aims to minimize the "disturbance" in a line of students, where disturbance is defined as the number of adjacent students with the same topic of interest. 
The allowed operation is to swap students at positions i and (n - i + 1) any number of times.

Algorithm:
- For each test case, we process the array and try to perform swaps that reduce adjacent duplicates.
- We iterate through indices from 1 to n-2 (middle part of array), checking if current element is equal to its neighbor on the left or right side.
- When such condition is met, we swap the current element with its corresponding mirrored element.

Time Complexity:
O(n) for each test case, since we perform a linear scan for swaps and another for counting disturbances. 

Space Complexity:
O(n) due to storing the vector of size n.

Techniques:
- Two-pointer approach (mirrored indices)
- Greedy swapping for adjacent duplicate reduction
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    // Iterate through the middle part of array to try swapping
    for (long p = 1; p < n - 1 - p; p++) {
      // Check if adjacent elements are equal or mirrored counterparts are equal
      if (v[p] == v[p - 1] || v[n - 1 - p] == v[n - p]) {
        long x = v[p];
        v[p] = v[n - 1 - p];
        v[n - 1 - p] = x;
      }
    }
    long cnt(0);
    // Count disturbances (adjacent equal elements)
    for (long p = 1; p < n; p++) {
      cnt += (v[p] == v[p - 1]);
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/
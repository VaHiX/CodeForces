// Problem: CF 2075 B - Array Recoloring
// https://codeforces.com/contest/2075/problem/B

/*
B. Array Recoloring
Algorithms/Techniques: Sorting, Greedy, Simulation
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the vector storage

You are given an integer array a of size n. Initially, all elements of the array are colored red.
You have to choose exactly k elements of the array and paint them blue. Then, while there is at least one red element, 
you have to select any red element with a blue neighbor and make it blue.
The cost of painting the array is defined as the sum of the first k chosen elements and the last painted element.
Your task is to calculate the maximum possible cost of painting for the given array.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    long mxmid(-1); // Track maximum middle element for special case when k == 1
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      if (k > 1) {
        continue;
      }
      if (p > 0 && p + 1 < n) {
        mxmid = (mxmid > a[p] ? mxmid : a[p]); // Keep track of max middle value
      }
    }
    if (k == 1 && n > 2) {
      long left = a[0] + mxmid;       // Sum of first and max middle element
      long right = mxmid + a.back();  // Sum of max middle and last element
      long both = a[0] + a.back();    // Sum of first and last elements
      long res = (left > right ? left : right);  // Find the maximum among three options
      res = (res > both ? res : both);
      printf("%ld\n", res);
      continue;
    }
    sort(a.rbegin(), a.rend()); // Sort in descending order to get largest elements first
    long long total(0);
    for (long p = 0; p < n && p < k + 1; p++) {
      total += a[p]; // Add top k+1 elements to maximize the cost
    }
    printf("%lld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/
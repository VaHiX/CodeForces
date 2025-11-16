// Problem: CF 1197 C - Array Splitting
// https://codeforces.com/contest/1197/problem/C

/*
C. Array Splitting
Algorithm: Greedy with Priority Queue
Time Complexity: O(n log n)
Space Complexity: O(n)

The problem is to split a sorted array into k consecutive subarrays such that the sum of (max - min) for each subarray is minimized.

Since the array is sorted, for any subarray, min = first element and max = last element.
To minimize the total cost, we want to minimize the sum of differences between adjacent elements.
We calculate all differences between consecutive elements and use a max heap to greedily remove 
the largest differences (i.e., choose to make fewer cuts where the difference is biggest).
The idea is that we want to avoid making cuts at positions with large gaps.
*/

#include <queue>
#include <stdio.h>
int a, b, c, n, k;
std::priority_queue<int> Q; // Max heap to store differences between consecutive elements
int main() {
  scanf("%d%d%d", &n, &k, &b); // Read n (array size), k (number of subarrays), unused variable b
  a = c = b; // Initialize variables
  for (int i = 2; i <= n; i++, b = a) { // Start from 2nd element, compare with previous
    scanf("%d", &a); // Read next element
    Q.push(a - b); // Push difference between current and previous element into max heap
  }
  c = a - c; // Final difference to be added
  while (--k && !Q.empty()) { // While we still need to make cuts and heap is not empty
    c -= Q.top(); // Subtract the largest difference (remove it from cost)
    Q.pop(); // Remove the top element
  }
  printf("%d", c); // Print final minimum cost
}


// https://github.com/VaHiX/codeForces/
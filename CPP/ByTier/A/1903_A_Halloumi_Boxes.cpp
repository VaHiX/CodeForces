// Problem: CF 1903 A - Halloumi Boxes
// https://codeforces.com/contest/1903/problem/A

/*
A. Halloumi Boxes
time limit per test1 second
memory limit per test256 megabytes

Theofanis is busy after his last contest, as now, he has to deliver many halloumis all over the world. He stored them inside
n
boxes and each of which has some number
a
i
written on it.
He wants to sort them in non-decreasing order based on their number, however, his machine works in a strange way. It can only reverse any subarray
†
†
of boxes with length at most
k
.
Find if it's possible to sort the boxes using any number of reverses.
†
†
Reversing a subarray means choosing two indices
i
and
j
(where
1≤i≤j≤n
) and changing the array
a
1
,
a
2
,…,
a
n
to
a
1
,
a
2
,…,
a
i−1
,
a
j
,
a
j−1
,…,
a
i
,
a
j+1
,…,
a
n−1
,
a
n
. The length of the subarray is then
j−i+1
.

Algorithm:
- For each test case, check if the array is already sorted.
- If it's not sorted, we can still sort it if k > 1 because with any subarray length up to k > 1, 
  we can perform swaps or reordering to achieve sorting.
- If k == 1, then we can only reverse subarrays of size 1, which means no change is possible,
  so the array must be sorted initially.

Time Complexity: O(n) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long prev(0);
    bool sorted(true);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (prev > x) {           // Check if array is not sorted in non-decreasing order
        sorted = false;
      }
      prev = x;
    }
    bool res = sorted || k > 1;   // If already sorted OR k > 1, then sorting is possible
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/
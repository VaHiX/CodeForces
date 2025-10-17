// Problem: CF 2027 B - Stalin Sort
// https://codeforces.com/contest/2027/problem/B

/*
B. Stalin Sort
time limit per test1 second
memory limit per test256 megabytes

Stalin Sort is a humorous sorting algorithm designed to eliminate elements which are out of place instead of bothering to sort them properly, lending itself to an
O(n)
time complexity.
It goes as follows: starting from the second element in the array, if it is strictly smaller than the previous element (ignoring those which have already been deleted), then delete it. Continue iterating through the array until it is sorted in non-decreasing order. For example, the array
[1,4,2,3,6,5,5,7,7]
becomes
[1,4,6,7,7]
after a Stalin Sort.
We define an array as vulnerable if you can sort it in non-increasing order by repeatedly applying a Stalin Sort to any of its subarrays
∗
∗
, as many times as is needed.
Given an array
a
of
n
integers, determine the minimum number of integers which must be removed from the array to make it vulnerable.
∗
∗
An array
a
is a subarray of an array
b
if
a
can be obtained from
b
by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

Algorithm:
The code computes for each starting position p, the maximum length of a non-decreasing subsequence starting at p.
This is done by counting how many elements after p are less than or equal to v[p].
The maximum such count gives the longest non-decreasing subsequence that can be formed beginning at some index.
We subtract this from n to get the minimum number of elements to remove.
Time Complexity: O(n^2) - For each element, we scan the rest of the array.
Space Complexity: O(n) - For storing the vector of size n.

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
      scanf("%ld", &v[p]); // Read array elements
    }
    long mxlen(0); // Maximum length of valid non-decreasing sequence starting from some index
    for (long p = 0; p < n; p++) {
      long cnt(1); // Start with 1 since we must include the element at position p
      for (long q = p + 1; q < n; q++) {
        cnt += (v[q] <= v[p]); // Count elements <= current element
      }
      mxlen = (mxlen > cnt ? mxlen : cnt); // Update maximum
    }
    printf("%ld\n", n - mxlen); // Minimum removals needed
  }
}


// https://github.com/VaHiX/codeForces/
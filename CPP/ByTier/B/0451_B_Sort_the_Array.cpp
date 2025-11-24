// Problem: CF 451 B - Sort the Array
// https://codeforces.com/contest/451/problem/B

/*
B. Sort the Array
time limit per test
1 second
memory limit per test
256 megabytes
input
stdin
output
stdout
Being a programmer, you like arrays a lot. For your birthday, your friends have given you an array 
a
 consisting of 
n
 
distinct
 integers.
Unfortunately, the size of 
a
 is too small. You want a bigger array! Your friends agree to give you a bigger array, but only if you are able to answer the following question correctly: is it possible to sort the array 
a
 (in increasing order) by reversing 
exactly one
 segment of 
a
? See definitions of segment and reversing in the notes.
Input
The first line of the input contains an integer 
n
 (
1 ≤ 
n
 ≤ 10
5
) — the size of array 
a
.
The second line contains 
n
 distinct space-separated integers: 
a
[1], 
a
[2], ..., 
a
[
n
]
 (
1 ≤ 
a
[
i
] ≤ 10
9
).
Output
Print "
yes
" or "
no
" (without quotes), depending on the answer.
If your answer is "
yes
", then also print two space-separated integers denoting start and end (start must not be greater than end) indices of the segment to be reversed. If there are multiple ways of selecting these indices, print any of them.
Examples
Input
3
3 2 1
Output
yes
1 3
Input
4
2 1 3 4
Output
yes
1 2
Input
4
3 1 2 4
Output
no
Input
2
1 2
Output
yes
1 1
Note
Sample 1. You can reverse the entire array to get 
[1, 2, 3]
, which is sorted.
Sample 3. No segment can be reversed such that the array will be sorted.
Definitions
A segment 
[
l
, 
r
]
 of array 
a
 is the sequence 
a
[
l
], 
a
[
l
 + 1], ..., 
a
[
r
]
.
If you have an array 
a
 of size 
n
 and you reverse its segment 
[
l
, 
r
]
, the array will become:
a
[1], 
a
[2], ..., 
a
[
l
 - 2], 
a
[
l
 - 1], 
a
[
r
], 
a
[
r
 - 1], ..., 
a
[
l
 + 1], 
a
[
l
], 
a
[
r
 + 1], 
a
[
r
 + 2], ..., 
a
[
n
 - 1], 
a
[
n
].
Algorithm: Linear scan to detect a single decreasing segment and verify that reversing it results in a sorted array.
Time Complexity: O(n)
Space Complexity: O(n)
*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<long> data(n, 0);
  for (int p = 0; p < n; p++) {
    scanf("%ld ", &data[p]); // Read input array elements
  }
  bool started(0), done(0), possible(1); // Flags to track state of segment detection
  long start(1), end(1); // Stores indices of the potential segment to reverse
  for (int p = 1; p < n; p++) {
    if (data[p - 1] > data[p] && !started) {
      started = 1;
      start = p; // Mark beginning of the decreasing sequence
    }
    if (data[p - 1] < data[p] && started && !done) {
      done = 1;
      end = p; // Mark end of the decreasing sequence
    }
    if (data[p - 1] > data[p] && done) {
      possible = 0;
      break; // If another decreasing segment is seen after we've already seen an increasing point, impossible to sort with one reverse
    }
  }
  if (possible && started && !done) {
    end = n; // If we have a start but no end, set end to last element
  }
  if ((start > 1 && data[start - 2] > data[end - 1]) ||
      (end < n && data[start - 1] > data[end])) {
    possible = 0; // Check if swapping boundaries with neighbor elements would break sorted order
  }
  if (!possible) {
    puts("no");
  } else {
    puts("yes");
    printf("%ld %ld\n", start, end); // Output the valid segment indices to reverse
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/
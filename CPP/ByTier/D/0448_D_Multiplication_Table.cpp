// Problem: CF 448 D - Multiplication Table
// https://codeforces.com/contest/448/problem/D

/*
D. Multiplication Table
Algorithm: Binary search on the answer combined with counting elements smaller than or equal to a value in an n x m multiplication table.
Time Complexity: O(n * log(n*m))
Space Complexity: O(1)

Bizon the Champion isn't just charming, he also is very smart.
While some of us were learning the multiplication table, Bizon the Champion had fun in his own manner. Bizon the Champion painted an 
n
 × 
m
 multiplication table, where the element on the intersection of the 
i
-th row and 
j
-th column equals 
i
·
j
 (the rows and columns of the table are numbered starting from 1). Then he was asked: what number in the table is the 
k
-th largest number? Bizon the Champion always answered correctly and immediately. Can you repeat his success?
Consider the given multiplication table. If you write out all 
n
·
m
 numbers from the table in the non-decreasing order, then the 
k
-th number you write out is called the 
k
-th largest number.
Input
The single line contains integers 
n
, 
m
 and 
k
 
(1 ≤ 
n
, 
m
 ≤ 5·10
5
; 1 ≤ 
k
 ≤ 
n
·
m
)
.
Output
Print the 
k
-th largest number in a 
n
 × 
m
 multiplication table.
Examples
Input
2 2 2
Output
2
Input
2 3 4
Output
3
Input
1 10 5
Output
5
Note
A 
2 × 3
 multiplication table looks like this:
1 2 3
2 4 6
*/

#include <stdint.h>
#include <iostream>

int main() {
  int64_t n, m, k;
  std::cin >> n >> m >> k;
  int64_t left(1), right(n * m + 1); // Binary search bounds: [1, n*m]
  while (left < right) {
    int64_t mid = (left + right) / 2; // Midpoint of the current range
    int64_t countSmaller(0); // Count of numbers <= mid in the table
    for (int64_t row = 1; row <= n; row++) {
      // For each row, count how many elements are smaller than or equal to mid
      // In row i, elements are: i*1, i*2, ..., i*m
      // We want number of values i*j <= mid => j <= mid/i
      int64_t smallerInRow = (m < (mid - 1) / row) ? m : (mid - 1) / row;
      countSmaller += smallerInRow; // Add to total count
    }
    if (countSmaller < k) {
      left = mid + 1; // Need to search higher
    } else if (countSmaller >= k) {
      right = mid; // This could be our answer, keep searching lower
    }
  }
  std::cout << (left - 1) << std::endl; // Adjust back to actual number
  return 0;
}


// https://github.com/VaHiX/codeForces/
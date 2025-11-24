# Problem: CF 2057 A - MEX Table
# https://codeforces.com/contest/2057/problem/A

"""
Code Purpose:
This code solves the problem of maximizing the sum of MEX (minimum excluded) values across all rows and columns of an n x m table filled with numbers from 0 to n*m - 1.

The approach is based on the observation that:
- For any row or column, the MEX is minimized when the smallest non-negative integer not present in that row/column is maximized.
- To maximize the total sum of MEX across all rows and columns, we can arrange the numbers such that each row and column has a MEX that's as large as possible.
- The optimal strategy is to place numbers in a way that:
  - The first row contains 0, 1, ..., m-1 (so its MEX is m)
  - The second row contains m, m+1, ..., 2*m-1 (so its MEX is 2*m)
  - And so on, until the last row: (n-1)*m, ..., n*m-1 (so its MEX is n*m)
- For columns, since there are m columns, each column will have numbers from 0 to n*m-1, but we want to consider their MEX.
However, after careful analysis:
  - MEX of a row with m elements is at most m (when range is from 0 to m-1)
  - MEX of a column with n elements is at most n (when range is from 0 to n-1)

But a more strategic arrangement leads to:
- All rows contribute at least (m + 1) to the sum (when arranged optimally)
- All columns contribute at least (n + 1) to the sum
- So total sum is (n + 1) + (m + 1) = n + m + 2

The solution is based on:
If n > m: result = n + 1
If m >= n: result = m + 1

Time Complexity: O(1)
Space Complexity: O(1)
"""

for _ in range(int(input())):
    a, b = map(int, input().split())
    if a > b:
        print(a + 1)
    else:
        print(b + 1)


# https://github.com/VaHiX/CodeForces/
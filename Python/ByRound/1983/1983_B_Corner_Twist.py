# Problem: CF 1983 B - Corner Twist
# https://codeforces.com/contest/1983/problem/B

"""
Algorithm: Corner Twist
Purpose: Determine if grid 'a' can be transformed into grid 'b' using specified operations on subrectangles.
Technique: 
- For each row and column, compute the sum of elements modulo 3.
- The key insight is that the operation affects only 4 corners of a subrectangle, thus the total sum of each row/column in the grid remains consistent modulo 3.
- If the sums of rows and columns of 'a' and 'b' match modulo 3, transformation is possible.

Time Complexity: O(n * m) per test case
Space Complexity: O(n + m) per test case

This solution is based on the idea that any operation changes the values of four corners of a subrectangle,
so the overall "balance" (sum modulo 3) of rows and columns must stay the same.
"""

import sys

input = sys.stdin.read


def solve():
    data = input().split()
    t = int(data[0])
    index = 1
    results = []

    for _ in range(t):
        n = int(data[index])
        m = int(data[index + 1])
        index += 2

        a = []
        b = []

        for i in range(n):
            a.append(data[index + i])
        index += n

        for i in range(n):
            b.append(data[index + i])
        index += n

        if n < 2 or m < 2:
            results.append("NO")
            continue

        # Initialize arrays to store row and column sums modulo 3
        sum_a_row = [0] * n
        sum_a_col = [0] * m
        sum_b_row = [0] * n
        sum_b_col = [0] * m

        # Compute row and column sums for grids a and b
        for i in range(n):
            for j in range(m):
                sum_a_row[i] += int(a[i][j])
                sum_a_col[j] += int(a[i][j])
                sum_b_row[i] += int(b[i][j])
                sum_b_col[j] += int(b[i][j])

        # Take modulo 3 of the sums
        for i in range(n):
            sum_a_row[i] %= 3
            sum_b_row[i] %= 3

        for j in range(m):
            sum_a_col[j] %= 3
            sum_b_col[j] %= 3

        # Check if the sums of rows and columns match
        if sum_a_row == sum_b_row and sum_a_col == sum_b_col:
            results.append("YES")
        else:
            results.append("NO")

    print("\n".join(results))


solve()


# https://github.com/VaHiX/CodeForces/
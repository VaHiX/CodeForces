# Problem: CF 1920 A - Satisfying Constraints
# https://codeforces.com/contest/1920/problem/A

"""
Algorithm: 
- For each constraint, we categorize them into three types:
  1. k >= x (lower bound)
  2. k <= x (upper bound)
  3. k != x (exclusion)

- We track the maximum of all lower bounds (m) and the minimum of all upper bounds (M).
- For each excluded value (type 3), we check if it falls within the range [m, M].
- The total count is (M - m + 1) minus the number of excluded values within that range.

Time Complexity: O(n), where n is the number of constraints
Space Complexity: O(n), due to storing the excluded values in a list
"""

import sys


def solve():
    inp = sys.stdin.readline
    n = int(inp())
    m = None  # maximum lower bound
    M = None  # minimum upper bound
    other = []  # list to store excluded values
    for i in range(n):
        a, x = map(int, inp().split())
        if a == 1:
            # Update the maximum lower bound
            if m is None or m < x:
                m = x
        if a == 2:
            # Update the minimum upper bound
            if M is None or M > x:
                M = x
        if a == 3:
            # Store excluded values for later checking
            other.append(x)
    
    # Count how many excluded values fall in the valid range [m, M]
    c = sum(m <= i <= M for i in other)
    
    # If the valid range is valid (m <= M), calculate the count of valid integers
    # Otherwise, return 0
    if m <= M:
        print(M - m + 1 - c)
    else:
        print(0)


def main():
    for i in range(int(sys.stdin.readline())):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
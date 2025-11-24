# Problem: CF 1672 H - Zigu Zagu
# https://codeforces.com/contest/1672/problem/H

"""
Algorithm: Preprocessing with prefix sums to count consecutive same digits
Time Complexity: O(n + q) where n is length of string, q is number of queries
Space Complexity: O(n) for prefix sum arrays

The problem asks to find minimum operations to make a substring empty, where each operation
removes a contiguous subsegment that has no two adjacent equal characters.

Key insight:
- For each position, we track how many times "00" or "11" appear up to that point
- The answer for a query [l, r] is the maximum of:
  - Number of "00" patterns in the substring + 1
  - Number of "11" patterns in the substring + 1
"""

from sys import gettrace, stdin

if gettrace():

    def inputi():
        return input()

else:

    def input():
        return next(stdin)[:-1]

    def inputi():
        return stdin.buffer.readline()


def main():
    n, q = map(int, input().split())
    s = input()
    # zp[i] represents number of "00" patterns from index 0 to i
    zp = [0] * n
    # op[i] represents number of "11" patterns from index 0 to i
    op = [0] * n
    
    # Preprocessing: compute prefix sums for consecutive "00" and "11" patterns
    for i, (c1, c2) in enumerate(zip(s, s[1:]), 1):
        zp[i] = zp[i - 1]
        op[i] = op[i - 1]
        if c1 == c2 == "0":
            zp[i] += 1
        elif c1 == c2 == "1":
            op[i] += 1
    
    # Process queries
    for _ in range(q):
        l, r = map(int, input().split())
        # Calculate number of operations needed for substring [l, r]
        # Subtract prefix sums to get count within the range
        print(max(zp[r - 1] - zp[l - 1], op[r - 1] - op[l - 1]) + 1)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
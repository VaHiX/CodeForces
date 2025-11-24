# Problem: CF 1864 D - Matrix Cascade
# https://codeforces.com/contest/1864/problem/D

"""
Algorithm: Matrix Cascade
Techniques: Bit manipulation, simulation with prefix/suffix masks

Time Complexity: O(n^2)
Space Complexity: O(n)

The problem involves transforming a binary matrix to all zeros using specific operations.
Each operation on cell (i,j) inverts that cell and all cells in a triangular region below and including it.
The approach uses a greedy method with prefix/suffix masks to efficiently track the state of the matrix.
"""

import sys


def input():
    return sys.stdin.buffer.readline().rstrip(b"\r\n")


def dbp(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def a_str():
    return input().decode("ascii")


def get_int_list():
    return [int(x) for x in input().split()]


def minus_one():
    return [int(x) - 1 for x in input().split()]


def join_str(l, sep=" "):
    return sep.join([str(x) for x in l])


def binfmt(x, w=8):
    return "{:0{w}b}".format(x, w=w)


def disp(x):
    for i in range(len(x)):
        dbp(binfmt(x[i], w=len(x)))


def do_thing():
    n = int(input())
    gin = [input() for _ in range(n)]

    def loopy():
        g = gin
        ops = 0
        left = [0] * (n * 2)  # Left shift mask for operation effect
        right = [0] * (n * 2)  # Right shift mask for operation effect  
        res = [0] * n  # Current state of each column
        for r in range(n):
            # Apply accumulated effects of previous operations to current row
            for i in range(n):
                res[i] ^= left[i + r] ^ right[i + n - r]
            # Check each cell in current row
            for c in range(n):
                # If current cell doesn't match expected result (0)
                if (g[r][c] == 49) ^ res[c]:  # 49 is ASCII for '1'
                    ops += 1
                    # Toggle result at current column
                    res[c] ^= 1
                    # Update left and right masks for future rows
                    left[c + r] ^= 1
                    right[c + n - r] ^= 1
        return ops

    r = loopy()

    return r


if __name__ == "__main__":
    maxcc = 1
    maxcc = int(input())
    for cc in range(maxcc):
        print(do_thing())


# https://github.com/VaHiX/CodeForces/
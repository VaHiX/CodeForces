# Problem: CF 1810 H - Last Number
# https://codeforces.com/contest/1810/problem/H

"""
Code Purpose:
This code solves the problem of finding the last remaining number in a multiset after a series of operations. 
Each operation removes the maximum and minimum elements and adds their difference back into the multiset.
The solution uses a recursive structure with precomputed segment information to determine the result efficiently.

Algorithms/Techniques:
- Precomputation of segment information using dynamic programming
- Binary search-like approach to find specific positions
- Mathematical manipulation to compute final result based on pattern recognition

Time Complexity: O(log n) per query after O(K^2) preprocessing where K is a constant (23)
Space Complexity: O(K^2) where K is a constant (23)
"""

class SegInfo:
    def __init__(self, len=0, odd=0, even=0, sum=0):
        self.len = len
        self.odd = odd
        self.even = even
        self.sum = sum

    def __add__(self, other):
        if self.len % 2 == 0:
            return SegInfo(
                self.len + other.len,
                self.odd + other.odd,
                self.even + other.even,
                self.sum + other.sum,
            )
        else:
            return SegInfo(
                self.len + other.len,
                self.odd + other.even,
                self.even + other.odd,
                self.sum + other.sum,
            )


K = 23
f = [[SegInfo() for _ in range(K)] for _ in range(2)]


def init():
    # Initialize base cases for recurrence relation
    f[0][0] = SegInfo(1, 0, 0, 0)
    f[1][0] = SegInfo(1, 1, 0, 1)
    # Fill the dp table using recurrence relations
    for i in range(1, K):
        f[0][i] = f[1][i - 1] + f[0][i - 1]
        f[1][i] = f[1][i - 1] + f[1][i - 1] + f[0][i - 1]
    total_sum = 0
    for i in range(K):
        total_sum += f[0][i].len


def find_p(n):
    # Binary search approach to find position 'p'
    all_info = SegInfo()
    for i in range(K):
        nw = all_info + f[0][i]
        if n - nw.sum <= 2 * nw.len:
            t = 0
            for j in range(i - 1, -1, -1):
                if t == 0:
                    nw = all_info + f[1][j]
                    if n - nw.sum <= 2 * nw.len:
                        t = 1
                    else:
                        t = 0
                        all_info = nw
                else:
                    nw = all_info + f[1][j]
                    if n - nw.sum <= 2 * nw.len:
                        t = 1
                    else:
                        all_info = nw
                        nw = all_info + f[1][j]
                        if n - nw.sum <= 2 * nw.len:
                            t = 1
                        else:
                            t = 0
                            all_info = nw
            return all_info.len + 1
        all_info = nw
    assert False, "Unreachable"


def getinfo(m):
    # Get information about segment at position m
    all_info = SegInfo()
    for i in range(K):
        if all_info.len + f[0][i].len < m:
            all_info = all_info + f[0][i]
            continue
        t = 0
        for j in range(i - 1, -1, -1):
            if t == 0:
                if all_info.len + f[1][j].len >= m:
                    t = 1
                else:
                    t = 0
                    all_info = all_info + f[1][j]
            else:
                if all_info.len + f[1][j].len >= m:
                    t = 1
                else:
                    all_info = all_info + f[1][j]
                    if all_info.len + f[1][j].len >= m:
                        t = 1
                    else:
                        t = 0
                        all_info = all_info + f[1][j]
        return all_info + f[t][0]
    assert False, "Unreachable"


def work():
    n = int(input())
    if n == 1:
        print(1)
        return
    if n == 2:
        print(1)
        return
    p = find_p(n)
    xp = getinfo(p)
    xn = getinfo(n - 1)
    # Compute final result based on parity conditions
    if (n - p) % 2 == 0:
        if p % 2 == 0:
            print(p - xn.odd + xp.odd)
        else:
            print(p - xn.even + xp.even)
    else:
        if p % 2 == 0:
            print(n - xp.sum - p - xn.even + xp.even)
        else:
            print(n - xp.sum - p - xn.odd + xp.odd)


def main():
    init()
    _ = int(input())
    for __ in range(_):
        work()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
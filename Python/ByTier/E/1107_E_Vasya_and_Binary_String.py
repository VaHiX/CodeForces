# Problem: CF 1107 E - Vasya and Binary String
# https://codeforces.com/contest/1107/problem/E

"""
E. Vasya and Binary String

Purpose:
This solution solves the problem of maximizing points when erasing consecutive equal substrings from a binary string.
The approach uses dynamic programming with interval DP to compute the maximum score possible for each substring.

Algorithms/Techniques:
- Interval Dynamic Programming (DP)
- Memoization for overlapping subproblems
- Preprocessing of prefix sums for efficiency

Time Complexity: O(n^3), where n is the length of the string.
Space Complexity: O(n^3), for the 3D DP table and auxiliary arrays.

The recurrence relation considers all possible ways to split an interval [i, j] and 
tries to maximize points by choosing optimal lengths of substrings to erase.

"""

ImportType = InputType = ConstType = 1
DecoratorType = FunctinoType = 1
if ImportType:
    import random
    import sys
    from types import GeneratorType
    from typing import List

if InputType:
    input = lambda: sys.stdin.readline().rstrip("\r\n")
    I = lambda: input()
    II = lambda: int(input())
    MII = lambda: map(int, input().split())
    LI = lambda: list(input())
    LII = lambda: list(map(int, input().split()))
    GMI = lambda: map(lambda x: int(x) - 1, input().split())
    LGMI = lambda: list(map(lambda x: int(x) - 1, input().split()))

if DecoratorType:

    def bootstrap(f, stack=[]):
        def wrappedfunc(*args, **kwargs):
            if stack:
                return f(*args, **kwargs)
            else:
                to = f(*args, **kwargs)
                while True:
                    if type(to) is GeneratorType:
                        stack.append(to)
                        to = next(to)
                    else:
                        stack.pop()
                        if not stack:
                            break
                        to = stack[-1].send(to)
                return to

        return wrappedfunc


if FunctinoType:

    class Math:
        __slots__ = ["mod", "l", "fact", "inv"]

        def __init__(self):
            self.mod = mod = 10**9 + 7
            self.l = l = 3 * 10**5 + 5
            self.fact = fact = [1] * (l + 1)
            self.inv = inv = [1] * (l + 1)
            for i in range(1, l + 1):
                fact[i] = fact[i - 1] * i % mod
            inv[l] = pow(fact[l], mod - 2, mod)
            for i in range(l - 1, -1, -1):
                inv[i] = inv[i + 1] * (i + 1) % mod

        def comb(self, n, r):
            return (
                self.fact[n] * self.inv[r] % self.mod * self.inv[n - r] % self.mod
                if n >= r >= 0
                else 0
            )

        def perm(self, n, r):
            return self.fact[n] * self.inv[n - r] % self.mod if n >= r >= 0 else 0

    class PrefixSum2D:
        __slots__ = ["pre"]

        def __init__(self, mat: List[List[int]]):
            n, m = len(mat), len(mat[0])
            self.pre = pre = [[0] * (m + 1) for _ in range(n + 1)]
            for i, row in enumerate(mat):
                for j, v in enumerate(row):
                    pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + v

        def find(self, r1: int, c1: int, r2: int, c2: int) -> int:
            """查询以(r1,c1)为左上角，(r2,c2)为右下角的矩形区间内所有值的和"""
            return (
                self.pre[r2 + 1][c2 + 1]
                - self.pre[r2 + 1][c1]
                - self.pre[r1][c2 + 1]
                + self.pre[r1][c1]
            )

    class Difference2D:
        __slots__ = ["m", "n", "diff"]

        def __init__(self, m, n):
            self.m = m
            self.n = n
            self.diff = [[0] * (n + 2) for _ in range(m + 2)]

        def add(self, r1, c1, r2, c2, delta):
            """下标从0开始，区间变化delta"""
            diff = self.diff
            diff[r1 + 1][c1 + 1] += delta
            diff[r1 + 1][c2 + 2] -= delta
            diff[r2 + 2][c1 + 1] -= delta
            diff[r2 + 2][c2 + 2] += delta

        def get(self):
            diff = self.diff
            for i in range(1, self.m + 1):
                for j in range(1, self.n + 1):
                    diff[i][j] += diff[i][j - 1] + diff[i - 1][j] - diff[i - 1][j - 1]
            diff = diff[1:-1]
            for i, row in enumerate(diff):
                diff[i] = row[1:-1]
            return diff

    class BinaryIndexedTree:
        __slots__ = ["n", "c"]

        def __init__(self, n):
            self.n = n
            self.c = [0] * (n + 1)

        def update(self, x: int, delta: int):
            while x <= self.n:
                self.c[x] += delta
                x += x & -x

        def query(self, x: int) -> int:
            s = 0
            while x > 0:
                s += self.c[x]
                x -= x & -x
            return s


if ConstType:
    MOD1, MOD9 = 10**9 + 7, 998244353
    RD = random.randint(MOD1, MOD1 << 1)
    Direction4 = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    Direction8 = [
        (0, 1),
        (0, -1),
        (1, 0),
        (-1, 0),
        (1, 1),
        (1, -1),
        (-1, 1),
        (-1, -1),
    ]
    Y, N = "Yes", "No"
    A, B = "Alice", "Bob"


def helltractor():
    n = II()
    li = list(map(int, I()))  # Convert string into list of integers
    a = LII()  # Points for each length of substring
    
    # f[i][j][k] represents the maximum score for interval [i, j] with k consecutive same characters at end
    f = [[[0] * n for _ in range(n)] for _ in range(n)]
    
    for i in range(n - 1, -1, -1):  # iterate backwards over start index
        for j in range(i, n):  # iterate forward over end index
            length = n - j - 1  # Length of remaining interval after j-th character
            for k in range(length + 1):  # iterate over number of ending same characters (k)
                # Initial maximum considering removing prefix substring of k chars + point a[k]
                mx = f[i][j - 1][0] + a[k]
                
                # Try all possible splits to maximize score
                for m in range(i, j):  # split at position m
                    if li[m] == li[j]:  # If current character equals last one, we can concatenate
                        # Combine score of two parts: left part [i,m] with k+1 chars at end,
                        # right part [m+1,j-1] starting from 0 count, and add point
                        mx = max(mx, f[i][m][k + 1] + f[m + 1][j - 1][0])
                
                # Store the computed maximum score in DP table
                f[i][j][k] = mx

    print(f[0][n - 1][0])  # Final answer is the whole string from 0 to n-1


if __name__ == "__main__":
    helltractor()



# https://github.com/VaHiX/codeForces/
# Problem: CF 1672 G - Cross Xor
# https://codeforces.com/contest/1672/problem/G

"""
Code Purpose:
This code solves the "Cross Xor" problem where we need to determine how many ways
we can fill in '?' characters in a grid such that the resulting grid can be
achieved by performing XOR operations on rows/columns. The solution uses Union-Find
to group connected components and check constraints for valid fillings.

Algorithms/Techniques:
1. Union-Find data structure for grouping connected components
2. Modular arithmetic for large computations
3. Dynamic programming concepts with bit manipulation
4. Graph theory for component connectivity

Time Complexity: O(r * c * α(r + c)) where α is the inverse Ackermann function
Space Complexity: O(r + c)

The solution handles different cases based on whether dimensions are even or odd,
and uses a Union-Find structure to group cells and validate constraints.
"""

import sys

sys.setrecursionlimit(10**4)

MOD = 998244353


def add(x, y):
    """Returns the sum of x and y modulo MOD."""
    return x + y - MOD if x + y >= MOD else x + y


def sub(x, y):
    """Returns the difference of x and y modulo MOD."""
    return x - y if x >= y else x + MOD - y


pw2 = [0] * 5000000


def init_pw2(n):
    """Initializes the power of 2 modulo MOD array up to n."""
    pw2[0] = 1
    for i in range(1, n + 1):
        pw2[i] = add(pw2[i - 1], pw2[i - 1])


class UnionFind:
    """Union-Find structure to handle disjoint set operations."""

    def __init__(self, size):
        self.fa = list(range(size))

    def find(self, x):
        """Finds the root of the element x."""
        if x == self.fa[x]:
            return x
        self.fa[x] = self.find(self.fa[x])
        return self.fa[x]

    def union(self, x, y):
        """Unites the sets containing elements x and y."""
        self.fa[self.find(x)] = self.find(y)


def main():
    init_pw2(4000000)

    r, c = map(int, input().split())
    cnt_q = 0
    b = []
    cnt_r = [0] * (r + 1)
    cnt_c = [0] * (c + 1)

    for i in range(1, r + 1):
        row = input().strip()
        b.append(row)
        for j in range(1, c + 1):
            if row[j - 1] == "?":
                cnt_q += 1
            elif row[j - 1] == "1":
                cnt_r[i] ^= 1
                cnt_c[j] ^= 1

    # If both dimensions are even, any valid assignment is possible
    if r % 2 == 0 and c % 2 == 0:
        print(pw2[cnt_q])
        return

    # If column count is even
    if c % 2 == 0:
        ans, flag = cnt_q, True
        # Check for constraints on columns
        for j in range(1, c + 1):
            x = any(b[i - 1][j - 1] == "?" for i in range(1, r + 1))
            if x:
                ans -= 1
            elif cnt_c[j]:
                flag = False
                break
        sum_res = pw2[ans] if flag else 0

        ans, flag = cnt_q, True
        # Check for constraints (flipped logic)
        for j in range(1, c + 1):
            x = any(b[i - 1][j - 1] == "?" for i in range(1, r + 1))
            if x:
                ans -= 1
            elif not cnt_c[j]:
                flag = False
                break
        if flag:
            sum_res = add(sum_res, pw2[ans])

        print(sum_res)
        return

    # If row count is even
    if r % 2 == 0:
        ans, flag = cnt_q, True
        # Check for constraints on rows
        for i in range(1, r + 1):
            x = any(b[i - 1][j - 1] == "?" for j in range(1, c + 1))
            if x:
                ans -= 1
            elif cnt_r[i]:
                flag = False
                break
        sum_res = pw2[ans] if flag else 0

        ans, flag = cnt_q, True
        # Check for constraints (flipped logic)
        for i in range(1, r + 1):
            x = any(b[i - 1][j - 1] == "?" for j in range(1, c + 1))
            if x:
                ans -= 1
            elif not cnt_r[i]:
                flag = False
                break
        if flag:
            sum_res = add(sum_res, pw2[ans])

        print(sum_res)
        return

    # General case for odd dimensions
    ans, flag = cnt_q, True
    uf = UnionFind(r + c + 1)
    V = [[] for _ in range(r + c + 1)]

    # Group connected components using Union-Find
    for i in range(1, r + 1):
        for j in range(1, c + 1):
            if b[i - 1][j - 1] == "?":
                uf.union(i, j + r)

    # Build component groups
    for i in range(1, r + c + 1):
        V[uf.find(i)].append(i)

    # Validate each group based on existing constraints
    for i in range(1, r + c + 1):
        if V[i]:
            x = 0
            for v in V[i]:
                if v > r:
                    x ^= cnt_c[v - r]
                else:
                    x ^= cnt_r[v]
            if x:
                flag = False
                break
            else:
                ans -= len(V[i]) - 1

    sum_res = pw2[ans] if flag else 0

    # Check with flipped constraints
    ans, flag = cnt_q, True
    for i in range(1, r + c + 1):
        if V[i]:
            x = 0
            for v in V[i]:
                if v > r:
                    x ^= cnt_c[v - r] ^ 1
                else:
                    x ^= cnt_r[v] ^ 1
            if x:
                flag = False
                break
            else:
                ans -= len(V[i]) - 1

    if flag:
        sum_res = add(sum_res, pw2[ans])

    print(sum_res)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
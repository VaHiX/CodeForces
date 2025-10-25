# Problem: CF 2143 F - Increasing Xor
# https://codeforces.com/contest/2143/problem/F

"""
F. Increasing Xor

Purpose:
This code solves a problem involving transforming a subarray into a strictly increasing sequence using XOR operations.
The key insight uses linear algebra with basis vectors to determine if a subarray can be made strictly increasing.

Algorithms/Techniques:
- Linear basis manipulation for XOR operations (using Gaussian elimination concept)
- Preprocessing to compute maximum reachable index for each starting position
- Efficient query answering based on precomputed data

Time Complexity: O(n^2 * 20 + q) where n is length of array, q is number of queries
Space Complexity: O(n * 20) for storing basis representations
"""

import sys

input = sys.stdin.readline


def add(basis, x):
    # Add x to the basis if not already covered
    for y in basis:
        x = min(x, x ^ y)
    if x == 0:
        return
    for i in range(len(basis)):
        basis[i] = min(basis[i], basis[i] ^ x)
    for i in range(len(basis)):
        if basis[i] < x:
            basis.insert(i, x)
            return
    basis.append(x)


def get_idx(basis, x):
    # Find index of x in the basis (reversed order)
    ans = 0
    sz = len(basis)
    for i in range(sz):
        if (x ^ basis[i]) < x:
            x ^= basis[i]
            ans |= 1 << (sz - 1 - i)
    return ans


def get_from_idx(basis, idx):
    # Get value at given index from basis
    ans = 0
    sz = len(basis)
    for i in range(sz):
        if idx & (1 << (sz - 1 - i)):
            ans ^= basis[i]
    return ans


def solve():
    T = int(input())
    for _ in range(T):
        n, q = map(int, input().split())
        a = list(map(int, input().split()))
        bases = []
        mxr = [0] * n
        for i in range(n - 1, -1, -1):
            sz = 0
            new_bases = []
            for idx, b in bases:
                # Copy basis and add element to it
                b_copy = b[:]
                add(b_copy, a[i])
                # If the new basis size differs, store it
                if sz == 0 or len(b_copy) != len(new_bases[-1][1]):
                    new_bases.append((idx, b_copy))
                    sz += 1
            bases = new_bases[:]
            # Add new basis with just current element
            if not bases or bases[-1][1] != [a[i]]:
                bases.append((i, [a[i]]))
            j = i
            rk = 0
            bidx = len(bases) - 1
            while j < n:
                # Calculate how many steps we can take forward
                steps = min(bases[bidx][0] - j, (1 << len(bases[bidx][1])) - rk - 1)
                rk += steps
                j += steps
                mxr[i] = j
                if j != bases[bidx][0]:
                    break
                if bidx == 0:
                    break
                # Get next element and move to previous basis
                y = get_from_idx(bases[bidx][1], rk)
                j += 1
                bidx -= 1
                rk = get_idx(bases[bidx][1], y)
                rk += 1
                if rk >= (1 << len(bases[bidx][1])):
                    break
        for _ in range(q):
            l, r = map(int, input().split())
            l -= 1
            r -= 1
            print("YES" if mxr[l] >= r else "NO")


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/
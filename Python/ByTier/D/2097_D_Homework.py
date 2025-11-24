# Problem: CF 2097 D - Homework
# https://codeforces.com/contest/2097/problem/D

"""
Problem: Determine if two binary strings s and t can be made equal using specific operations.

Operations:
- Split a string into two equal halves x and y
- Perform one of three actions:
  1. x[i] = (x[i] + y[i]) mod 2 for all i
  2. y[i] = (x[i] + y[i]) mod 2 for all i
  3. Recursively apply operations to x and y independently

The key insight is that the transformations preserve the "linear independence" of the binary vectors.
This problem reduces to checking if the two sets of transformed vectors span the same space.

Algorithm:
- Use Gaussian elimination (with XOR operations) to compute a basis for each string's vector space
- Check if the bases are equivalent under the possible transformations

Time Complexity: O(N)
Space Complexity: O(N)

Note: This is essentially a problem in linear algebra over GF(2).
The transformation rules allow modifying bits via XOR, which means we can only reach vectors
in the span of the original input.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def solve(N, S, T):
    B = N
    # Find the smallest power of 2 that divides N
    while B & 1 == 0:
        B //= 2
    
    # Convert string chunks to integers (binary representation)
    A0 = []
    for i in range(0, N, B):
        A0.append(int(S[i : i + B], 2))
    
    A1 = []
    for i in range(0, N, B):
        A1.append(int(T[i : i + B], 2))

    # Compute a basis for the set of vectors using Gaussian elimination (XOR)
    def calc_base(X):
        res = []
        for x in X:
            for b in res:
                x = min(x, x ^ b)  # XOR reduction
            if x != 0:
                res.append(x)
        return res

    base0 = calc_base(A0)
    base1 = calc_base(A1)
    
    # Check if the two bases are compatible
    for _ in range(2):
        for b1 in base1:
            for b in base0:
                b1 = min(b1, b1 ^ b)  # Reduce using basis elements
            if b1 != 0:
                return False
        base0, base1 = base1, base0  # Swap bases
    
    return True


for _ in range(int(input())):
    N = int(input())
    S = input()
    T = input()
    print("Yes" if solve(N, S, T) else "No")


# https://github.com/VaHiX/codeForces/
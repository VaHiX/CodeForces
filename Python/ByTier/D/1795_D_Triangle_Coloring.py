# Problem: CF 1795 D - Triangle Coloring
# https://codeforces.com/contest/1795/problem/D

"""
Code Purpose:
This code solves the problem of finding the number of valid colorings of a specific graph structure (composed of triangles) that achieve the maximum possible weight. The graph consists of n vertices divided into n/3 triples, where each triple forms a triangle (complete subgraph K3). Each edge has a positive integer weight. A valid coloring uses exactly n/2 red and n/2 blue vertices. The goal is to count how many colorings result in the maximum possible weight, where weight is the sum of weights of edges connecting vertices of different colors.

Algorithmic Techniques:
- Combinatorial counting using binomial coefficients (ncr)
- Sorting and comparison of edge weights within each triangle
- Modular arithmetic for handling large numbers and preventing overflow

Time Complexity: O(n log n) due to sorting operations within each triangle and processing all edges.
Space Complexity: O(1) excluding input storage, as only a few variables are used.
"""

import sys

input = sys.stdin.readline


def print(*args, sep=" ", end="\n"):
    sys.stdout.write(sep.join(map(str, args)))
    sys.stdout.write(end)


mod = 998244353


def ncr(n, r):
    # Calculate combination C(n, r) modulo mod using efficient approach
    num = den = 1
    for i in range(r):
        num = (num * (n - i)) % mod
        den = (den * (i + 1)) % mod
    return (num * pow(den, mod - 2, mod)) % mod


def solution():
    n = int(input())
    a = [int(num) for num in input().split()]
    # Initialize result with number of ways to choose n/6 triples out of n/3 total triples to be colored red
    ans = ncr(n // 3, n // 6) % mod
    # Process each triangle group
    for i in range(0, n, 3):
        # Extract weights of edges in current triangle
        w = sorted(a[i : i + 3])
        # If minimum weight edge is not the smallest, it's a condition that doesn't contribute
        if w[0] < w[1]:
            continue
        # If the smallest two weights are equal but less than the third, there are two choices for optimal coloring
        elif w[0] == w[1] and w[1] < w[2]:
            ans = (ans * 2) % mod
        # If all three weights are equal, there are three choices leading to max weight
        else:
            ans = (ans * 3) % mod
    print(ans)


def main():
    t = 1
    while t:
        solution()
        t -= 1


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
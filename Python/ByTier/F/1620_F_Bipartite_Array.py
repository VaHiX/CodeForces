# Problem: CF 1620 F - Bipartite Array
# https://codeforces.com/contest/1620/problem/F

"""
Bipartite Array Problem

Algorithm:
This solution uses dynamic programming to determine if a bipartite array can be constructed.
The key insight is that we're trying to assign either +p_i or -p_i to each element such that 
the resulting array forms a bipartite graph when edges are added between elements where i < j and a_i > a_j.

Time Complexity: O(n^2) - The nested loops iterate through all pairs of elements.
Space Complexity: O(n) - For storing DP states and the result array.

Approach:
1. For each element, we track two states: whether the current element is positive or negative.
2. We use a DP table where dp[i][s] represents the minimum value that can be achieved up to index i,
   with s indicating if the i-th element is positive (0) or negative (1).
3. For each pair of adjacent elements, we update the DP state based on comparison of values and feasibility.
4. If a valid sequence is found, we reconstruct it using backtracking.

"""

import sys
from math import inf

input = sys.stdin.readline
inf = 1 << 20


def sol(numbers):
    n, elems = numbers

    # dp[i][s] = minimum value achieved at index i with s being the sign state (0 for positive, 1 for negative)
    dp = [[inf, inf] for _ in range(n)]
    dp[0][0] = dp[0][1] = -inf

    # cad[i][s] = parent state used to reach state (i, s)
    cad = [[0, 0] for _ in range(n)]

    # Iterate through all adjacent pairs
    for i in range(n - 1):
        for s in range(2):
            if dp[i][s] != inf:
                x = -1 * elems[i] if s else elems[i]
                y = dp[i][s]
                if x < y:
                    x, y = y, x
                for sp in range(2):
                    z = -1 * elems[i + 1] if sp else elems[i + 1]
                    # Check if the assignment leads to a valid bipartite structure
                    if z > x and dp[i + 1][sp] > y:
                        dp[i + 1][sp] = y
                        cad[i + 1][sp] = s
                    elif z > y and dp[i + 1][sp] > x:
                        dp[i + 1][sp] = x
                        cad[i + 1][sp] = s

    # Find final valid state
    sg = -1
    for s in range(2):
        if dp[n - 1][s] != inf:
            sg = s

    if sg == -1:
        print("NO")
        return

    # Reconstruct the solution using backtracking
    res = [0] * n
    for i in range(n - 1, -1, -1):
        res[i] = -1 * elems[i] if sg else elems[i]
        sg = cad[i][sg]

    print("YES")
    print(*res)


def main():
    t = int(input())

    for _ in range(t):
        n = int(input())
        numbers = (n, list(map(int, input().split(" "))))
        sol(numbers)


main()


# https://github.com/VaHiX/CodeForces/
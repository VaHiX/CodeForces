# Problem: CF 1989 D - Smithing Skill
# https://codeforces.com/contest/1989/problem/D

"""
Algorithm: Dynamic Programming with Cyclical Pattern Recognition
- This problem involves maximizing experience points by repeatedly forging and melting weapons.
- Each weapon class has a cost (ai) to forge and a return (bi) when melted.
- For each metal type, we calculate how many experience points we can gain.
- The pattern of gains is cyclical after a certain point, so we precompute the optimal experience points for small ingot counts.
- Time Complexity: O(n + m + max(a) + sum(c))
- Space Complexity: O(max(a))

Techniques:
- Preprocessing of weapon efficiencies
- Dynamic programming to detect and exploit repetitive cycles
- Efficient handling of large input values using modular arithmetic
"""

import sys


def rs():
    return sys.stdin.readline().rstrip()


def ri():
    return int(sys.stdin.readline())


def ria():
    return list(map(int, sys.stdin.readline().split()))


def ws(s):
    sys.stdout.write(s)
    sys.stdout.write("\n")


def wi(n):
    sys.stdout.write(str(n))
    sys.stdout.write("\n")


def wia(a, sep=" "):
    sys.stdout.write(sep.join([str(x) for x in a]))
    sys.stdout.write("\n")


def solve(n, m, a, b, c):
    max_a = max(a)  # Find maximum required ingots for any weapon
    M = max_a + 1  # Size of lookup table
    best = [M] * M  # best[i] = minimum (a[j] - b[j]) where a[j] = i
    
    # For each weapon class, compute the net loss of ingots (a[i] - b[i])
    # and store the minimum net loss for each required ingot count
    for i in range(n):
        diff = a[i] - b[i]
        best[a[i]] = min(best[a[i]], diff)
    
    # ans[i] = maximum experience points for i ingots
    ans = [0] * M
    waste = M  # Minimum net loss of ingots (cycle length)
    
    # Compute prefix minimums to find cycle
    for i in range(M):
        waste = min(waste, best[i])  # Minimum net loss seen so far
        if waste < M:
            ans[i] = 2 + ans[i - waste]  # 2 for forge + melt (1 + 1)
    
    res = 0  # Total experience points
    
    # For each metal type's ingot count
    for ci in c:
        if ci < M:
            # Direct lookup for small counts
            res += ans[ci]
        else:
            # Use cycle to compute experience points for large counts
            v = 1 + (ci - M) // waste  # Number of full cycles to consider
            ci -= v * waste  # Adjust count after cycles
            res += ans[ci] + 2 * v  # Add points from cycles
    
    return res


def main():
    n, m = ria()
    a = ria()
    b = ria()
    c = ria()
    wi(solve(n, m, a, b, c))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
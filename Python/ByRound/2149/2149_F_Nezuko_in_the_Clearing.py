# Problem: CF 2149 F - Nezuko in the Clearing
# https://codeforces.com/contest/2149/problem/F

"""
F. Nezuko in the Clearing

Problem Description:
Nezuko starts at position 0 with h health points and wants to reach position d.
Each move from position x to x+1 costs j health points where j is the j-th consecutive move.
She can also rest to regain 1 health point per turn.
The goal is to find the minimum number of turns needed to reach d.

Algorithms/Techniques:
- Binary search on the answer (on x, which represents how many times we "rest" before moving)
- Mathematical calculation for total cost of moves based on number of rests and moves

Time Complexity: O(t * log d), where t is the number of test cases
Space Complexity: O(1)

"""

def feasible(h, d, x):
    # m = x + 1: number of moves after (x) rests (since we rest before first move)
    m = x + 1
    # p and q are quotient and remainder when dividing d by m
    p = d // m
    q = d % m
    # compute total cost of moving d positions using p consecutive moves of each type
    # (m-q) moves with health cost p, and q moves with health cost (p+1)
    cost = (m - q) * (p * (p + 1) // 2) + q * ((p + 1) * (p + 2) // 2)
    # check if this cost is less than available health h + x (x = rest turns)
    return cost < h + x


def min_turns(h, d):
    # Binary search over the number of resting turns
    lo, hi = 0, d
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(h, d, mid):
            hi = mid  # try to minimize resting turns
        else:
            lo = mid + 1
    # Return total turns: d (moves) + lo (rests)
    return d + lo


t = int(input())
for _ in range(t):
    h, d = map(int, input().split())
    print(min_turns(h, d))


# https://github.com/VaHiX/CodeForces/
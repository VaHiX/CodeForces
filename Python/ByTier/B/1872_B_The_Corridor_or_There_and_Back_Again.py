# Problem: CF 1872 B - The Corridor or There and Back Again
# https://codeforces.com/contest/1872/problem/B

"""
Problem: The Corridor or There and Back Again
Algorithm/Techniques: Greedy, Math
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves finding the maximum value of k such that a path from room 1 to room k and back to room 1
can be made safely, avoiding active traps. Each trap at room d_i activates after s_i seconds from when the room is entered.
To avoid a trap, one must leave the room before s_i seconds have passed since entering.

Key insight:
For each trap at room d_i with activation time s_i, we calculate the latest time one can be in room d_i to not trigger it.
Since the path is 1 -> k -> 1, the time to go from room 1 to room d_i is d_i - 1 seconds.
Therefore, to avoid triggering the trap, you must leave the room by (d_i - 1 + s_i - 1) = d_i + s_i - 2 seconds.
But we want to maximize k, so we want to delay the latest possible time one can reach room k safely.
This means we must avoid all traps on the way back (to k), and more precisely, avoid them by reaching k just before
the earliest possible activation time among all traps.

We compute for each trap the earliest time one should be out of that room to be safe, and we find the minimum of those.
That minimum gives us the maximum k we can reach.

The formula used:
For a trap at room d with activation delay s:
We must leave room d by s seconds after entering it.
If we enter at time d-1, then we must be out by (d-1 + s - 1) = d + s - 2.
But since we're coming back from k, if we are at room d, we must have left it before s seconds.
So we compute the latest room we can be in, and that's d + (s-1)//2, which means we can go up to that room.
"""

from sys import stdin

inf = int(1e19)
input = stdin.readline
mod = 998244353


def fastfrac(a, b):
    numb = pow(b, mod - 2, mod)
    return ((a % mod) * (numb % mod)) % mod


for _ in range(int(input())):
    n = int(input())
    ans = inf
    for _ in range(n):
        d, s = map(int, input().split())
        # Compute the maximum safe k value for this trap
        # This is d plus half of (s - 1), rounded down
        res = d + ((s - 1) // 2)
        ans = min(ans, res)
    print(ans)


# https://github.com/VaHiX/CodeForces/
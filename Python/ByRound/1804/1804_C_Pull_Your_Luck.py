# Problem: CF 1804 C - Pull Your Luck
# https://codeforces.com/contest/1804/problem/C

"""
Code Purpose:
This code determines whether it's possible to win the "Pull Your Luck" roulette game by pulling the handle with a force from 1 to p such that the arrow points to sector 0.
The wheel has n sectors numbered 0 to n-1, and spinning with force f moves the wheel f + (f-1) + ... + 1 = f*(f+1)/2 sectors forward.
We check all possible forces up to min(p, 2*n + 1) to see if any leads to sector 0.

Algorithms/Techniques:
- Mathematical simulation of wheel spin using arithmetic progression sum formula
- Optimization by limiting the range of forces to check based on the cycle of the wheel

Time Complexity: O(min(p, n))
Space Complexity: O(1)
"""

import sys

input = sys.stdin.buffer.readline
output = sys.stdout.buffer.write


def print(*values, sep=" ", end="\n"):
    output(sep.join(str(value) for value in values).encode())
    output(end.encode())


for _ in range(int(input())):
    n, x, p = map(int, input().split())
    ans = "No"
    # Iterate through possible forces up to a reasonable limit
    # We only need to check up to 2*n + 1 because of periodicity in modular arithmetic
    for i in range(1, min(p + 1, 2 * n + 1)):
        # Calculate total sectors moved by force i
        # Sum of arithmetic sequence: i + (i-1) + ... + 1 = i*(i+1)/2
        total_sectors = i * (i + 1) // 2
        # Check if spinning with force i lands on sector 0
        # (x + total_sectors) % n gives the final position
        if (x + total_sectors) % n == 0:
            ans = "Yes"
    print(ans)


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1993 C - Light Switches
# https://codeforces.com/contest/1993/problem/C

"""
Purpose: 
    This code solves the problem of finding the earliest time when all rooms in an apartment have their lights turned on, 
    given the installation times of chips that control the lights and the period k of each chip.

Algorithms/Techniques:
    - Use modular arithmetic to determine the light on/off cycles.
    - For each room, calculate the "phase" (i.e., time relative to k) of when the chip starts affecting the room's light.
    - If the difference between the maximum and minimum phases is less than k, then there exists a common time when all lights are on.
    - Otherwise, no such time exists.

Time Complexity: O(n)
    - Single pass through the array to compute modulo values and find max/min.
Space Complexity: O(n)
    - Extra space for storing the modulo values.
"""

maxn, inf, eps = 2e5 + 10, 0x3F3F3F3F, 1e-9


def solve():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    maxa = max(a)
    # Compute the phase of each light's cycle
    m = [(maxa - i + k) % (k << 1) for i in a]
    # If the range of phases is less than k, a common time exists
    if max(m) - min(m) < k:
        print(maxa - min(m) + k)
    else:
        print(-1)
    return


for t in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/
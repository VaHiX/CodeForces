# Problem: CF 1971 D - Binary Cut
# https://codeforces.com/contest/1971/problem/D

"""
Algorithm: Greedy approach to count the number of transitions from '0' to '1'.
Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) as we only use a constant amount of extra space.

The idea is to count how many times we transition from '0' to '1' in the string.
Each such transition indicates the start of a new piece that needs to be cut,
since we want all '0's to come before all '1's. The minimum number of pieces
is equal to the number of such transitions plus 1.
"""

import sys

rln = sys.stdin.buffer.readline
rl = lambda: rln().rstrip(b"\r\n").rstrip(b"\n")
ri = lambda: int(rln())
rif = lambda: [*map(int, rln().split())]
rt = lambda: rl().decode()
rtf = lambda: rln().decode().split()
inf = float("inf")
dir4 = [(-1, 0), (0, 1), (1, 0), (0, -1)]
dir8 = [(-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]
YES, NO, Yes, No, yes, no = "YES", "NO", "Yes", "No", "yes", "no"

t = ri()

for _ in range(t):
    s = rt()

    tail = 1
    cuts = 0
    first_time = True

    while tail < len(s):
        if s[tail] == "1" and s[tail - 1] == "0":
            # A transition from '0' to '1' indicates a cut is needed
            if not first_time:
                cuts += 1
            tail += 1
            first_time = False
        elif s[tail] == s[tail - 1]:
            # Same characters, continue
            tail += 1
        else:
            # A transition from '1' to '0' is not relevant for counting cuts here
            cuts += 1
            tail += 1

    print(cuts + 1)


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1932 E - Final Countdown
# https://codeforces.com/contest/1932/problem/E

"""
Problem: Final Countdown
Algorithms/Techniques: Simulation, Digit Manipulation
Time Complexity: O(n) where n is the length of the countdown string
Space Complexity: O(n) for storing the result string

This problem simulates a countdown from a given number to zero.
Each digit transition takes time equal to the number of digits changed.
The solution computes the total time by simulating the reverse process:
starting from 0, we incrementally compute how long it takes to reach
the given number, using digit-wise arithmetic.
"""

import sys


def solve():
    n, z, Z, idx = int(input()), 0, 0, 0
    s = input().strip()
    # Skip leading zeros in the input string
    while s and s[idx] == "0":
        idx += 1
    s = s[idx:]
    # Calculate sum of all digits in the string
    for i in range(len(s)):
        Z += int(s[i])
    t = []
    # Process digits from right to left
    for i in range(len(s) - 1, -1, -1):
        t.append((z + Z) % 10)  # Compute the current digit
        z = (z + Z) // 10       # Carry to next digit
        Z -= int(s[i])          # Reduce remaining sum
    # Handle remaining carry
    while z > 0:
        t.append(z % 10)
        z //= 10
    # Reverse and print the result
    print("".join(map(str, t[::-1])))


input = sys.stdin.readline
write = sys.stdout.write
for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/
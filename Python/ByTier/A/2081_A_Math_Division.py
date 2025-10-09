# Problem: CF 2081 A - Math Division
# https://codeforces.com/contest/2081/problem/A

"""
Expected number of operations to reduce a binary number to 1.
Each step, with prob 1/2, either floor(x/2) or ceil(x/2) is chosen.
Algorithms: Dynamic Programming with reverse iteration and modular arithmetic.
Time Complexity: O(n) per test case, where n is the length of the binary string.
Space Complexity: O(1), only using constant extra space.
"""

if 1:
    import random
    import sys

    input = lambda: sys.stdin.readline().strip()
    import math

    inf = math.inf
    rdm = random.getrandbits(30)

    def I():
        return input()

    def II():
        return int(input())

    def MII():
        return map(int, input().split())

    def LI():
        return list(input())

    def LII():
        return list(map(int, input().split()))

    def LFI():
        return list(map(float, input().split()))

    def LSI():
        return list(map(str, input().split()))

    mod = int(1e9 + 7)
inv = pow(2, mod - 2, mod)  # Modular inverse of 2 mod (1e9 + 7)

for _ in range(II()):
    n = II()
    s = I()
    la = 0  # This will hold the expected number of operations for the current suffix
    for i in range(len(s) - 1, 0, -1):
        # If current bit is '1', we can go to either floor(x/2) or ceil(x/2)
        # If it's '0', only floor(x/2) is possible.
        if s[i] == "1":
            # cur = la + (1 - la) * inv  -> Expected value calculation based on probability
            cur = la + (1 - la) * inv
            cur %= mod
        else:
            # If current bit is '0', we only go to floor(x/2)
            cur = la * inv
            cur %= mod
        la = cur
    # Multiply by the length of string and adjust based on the expected value
    print(la * len(s) + (1 - la) * (len(s) - 1))


# https://github.com/VaHiX/codeForces/
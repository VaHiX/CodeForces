# Problem: CF 2109 C3 - Hacking Numbers (Hard Version)
# https://codeforces.com/contest/2109/problem/C3

"""
C3. Hacking Numbers (Hard Version)

Algorithm:
The solution uses a strategy to convert an unknown number x (1 <= x <= 10^9) into a target number n using at most f(n) operations.
The key insight is to use "mul" with 999999999 and then "digit" to obtain the sum of digits of x, which is always <= 81 for any x in [1, 10^9].
Then, if n != 81, we add (n - 81) to reach n.
This method works because we can always get the digit sum through "digit" and adjust with one addition operation.

Time Complexity: O(1) per test case
Space Complexity: O(1)

Commands used:
- mul 999999999
- digit
- add (if needed)
- !

The process is guaranteed to work for all values x in range [1, 10^9], since S(x) <= 81.
"""

import sys

input = sys.stdin.readline


def ans(*args):
    print(*args if len(args) else "!", flush=True)
    return int(input())


t = int(input())
for _ in range(t):
    n = int(input())
    ans("mul", 999999999)  # Multiply x by large number to make it easier to get digit sum
    ans("digit")           # Get the sum of digits of the current x (at most 81)
    if n != 81:
        ans("add", n - 81) # Add difference to reach target n
    ans()                  # Finalize with "!" to indicate completion


# https://github.com/VaHiX/codeForces/
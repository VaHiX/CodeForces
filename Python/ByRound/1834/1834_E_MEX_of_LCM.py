# Problem: CF 1834 E - MEX of LCM
# https://codeforces.com/contest/1834/problem/E

"""
Algorithm: MEX of LCM
Approach:
- For each element in the array, we maintain a set of all possible LCMs of subsegments ending at the current position.
- We use a greedy approach to build up all possible LCM values incrementally.
- For each new number, we compute LCMs with all previously computed LCMs, and add the new number itself.
- We track the maximum value we need to check (40 * n) to avoid infinite computation.
- Finally, we find the smallest positive integer not present in the set of computed LCMs.

Time Complexity: O(n * log(max(a)) * log(n)) where n is the length of array and log(max(a)) accounts for LCM computation.
Space Complexity: O(n * log(n)) for storing the set of LCMs.
"""

import math
import sys

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


def solve() -> None:
    n = sint()
    nums = ints()
    mx = 40 * n  # Set an upper bound to prevent overflow and infinite loop
    s, f = set(), set()  # s stores all possible LCMs, f stores LCMs from previous step
    for x in nums:
        g = set()  # g stores new LCMs computed in this iteration
        for a in f:  # Iterate over all previous LCMs
            m = math.lcm(x, a)  # Compute LCM of current number and previous LCM
            if m < mx:  # Only consider LCMs under the threshold
                s.add(m)
                g.add(m)
        s.add(x)  # Add the current number itself as a possible LCM
        g.add(x)
        f = g  # Update f for next iteration
    ans = 1
    while ans in s:  # Find the smallest missing positive integer
        ans += 1
    print(ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/
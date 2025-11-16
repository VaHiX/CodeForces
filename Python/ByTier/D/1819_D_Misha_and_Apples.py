# Problem: CF 1819 D - Misha and Apples
# https://codeforces.com/contest/1819/problem/D

"""
Algorithm: Dynamic Programming with Optimization for Apple Disappearance
Time Complexity: O(n * m + sum(k_i)) where n is number of stalls, m is number of apple types, and sum(k_i) is total apples across all stalls
Space Complexity: O(n + m) for storing last occurrence of apples and canZero arrays

The problem is about maximizing the number of apples in Danya's backpack after visiting all shops,
considering that apples of same type disappear when they appear together in the backpack.

Approach:
1. Precompute maxRemain: for each shop, calculate the maximum number of apples that could remain
   in the backpack if all subsequent shops were empty (best case for remaining apples).
2. Compute canZero: for each shop, check if it's possible for that shop to be empty such that 
   no apples disappear (i.e., all apples before this shop have already disappeared or won't be 
   duplicated later).
3. Use dynamic programming and reverse processing to determine optimal configurations.
4. The key insight is to track when apples first appear and ensure no duplicates appear together
   in future visits after a shop, to avoid disappearance.
"""

import os
import sys
from collections import Counter


def run(n, m, shop):
    if n == 1:
        # Special case: only one shop, if it's empty, we can take all m apples
        # otherwise take all apples from that shop
        return len(shop[1]) or m

    maxRemain = [None] * (n + 1)
    canZero = [None] * (n + 1)

    max_count = 0
    total_count = 0
    hasZero = False
    counts = Counter()
    # Process backwards to determine how many apples can remain if all following shops are empty
    for i in reversed(range(n + 1)):
        if max_count >= 2:
            # If there are already 2 or more of any apple type, we can't let more appear
            maxRemain[i] = 0
        elif hasZero:
            # If any shop before had zero apples, we can possibly have m apples (all types)
            maxRemain[i] = m
        else:
            # Default case: we can potentially have all apples we've taken so far
            maxRemain[i] = total_count

        if i > 0:
            # Update state for next iteration
            hasZero |= len(shop[i]) == 0
            total_count += len(shop[i])
            for a in shop[i]:
                counts[a] += 1
                max_count = max(max_count, counts[a])

    # Reset variables for another backward pass
    canZero[0] = True
    counts = Counter()

    last = {}
    lastCanZero = [None] * (n + 1)
    lastCanZero[0] = 0

    last_z = None
    last_cz = 0
    begin_disappear = -1
    
    # Forward pass to determine the minimum index after which no apples can be added
    for i in range(1, n + 1):
        if len(shop[i]) == 0:
            canZero[i] = True
            last_z = i
        else:
            # Check if any of the apples from current shop were seen before (and where)
            L = [last[t] for t in shop[i] if t in last]
            if last_z is not None or L:
                # If there was an empty shop or we've seen these apples before
                j = max(last_z or 0, max(L, default=0))
                s = lastCanZero[j]
                canZero[i] = begin_disappear <= s
            else:
                canZero[i] = False

            for l in L:
                begin_disappear = max(l, begin_disappear)
            for a in shop[i]:
                last[a] = i

        lastCanZero[i] = last_cz
        if canZero[i]:
            last_cz = i

    # Return the maximum apple count from those cases where we can have an empty shop
    return max(maxRemain[i] for i in range(n + 1) if canZero[i])


def main():
    data = os.read(sys.stdin.fileno(), int(1e8)).decode().split("\n")
    if not data[-1]:
        data.pop()

    i = 0

    def read():
        nonlocal i
        i += 1
        return data[i - 1]

    t = int(read())

    out = []
    for _ in range(t):
        n, m = [int(x) for x in read().split()]
        shop = [None] * (n + 1)
        for j in range(1, n + 1):
            _, *shop[j] = [int(x) for x in read().split()]
        out.append(run(n, m, shop))

    out.append("")
    out = "\n".join(str(x) for x in out)
    os.write(sys.stdout.fileno(), out.encode())


main()


# https://github.com/VaHiX/CodeForces/
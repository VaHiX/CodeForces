# Problem: CF 1795 E - Explosions?
# https://codeforces.com/contest/1795/problem/E

"""
Algorithm: 
- The problem involves finding the minimum MP to kill all monsters using a combination of basic spells and one explosion spell.
- The explosion spell can be cast with a certain power (x), and it affects neighboring monsters through a chain reaction.
- A key insight is that we want to minimize the combined cost of basic spells and the explosion power.
- This is solved using a "stack-based" approach to simulate the chain explosions efficiently.
- For each monster, we compute how much damage is needed to eliminate it via explosion (i.e., how much we must "pre-damage" it).
- We use two passes:
    1. Forward pass to compute left-to-right explosion contribution.
    2. Backward pass to compute right-to-left explosion contribution.
- The minimal cost will be the total health minus the maximum sum of contributions from both sides.
Time Complexity: O(n) - We perform two linear passes through the array (forward and backward).
Space Complexity: O(n) - We store arrays for results and use a stack for intermediate computations.
"""

import sys

input = sys.stdin.buffer.readline


def f(a: list[int]) -> list[int]:
    n = len(a)
    q: list[(int, int)] = []  # Stack to store (index, value) pairs for computation
    r = [0] * n  # Result array storing the contribution of each monster
    s = 0  # Running sum for the contribution
    for i in range(n):
        l = i  # Left bound for current computation
        # While stack is not empty and current element "dominates" top of stack
        while len(q) > 0:
            x, ax = q[-1]  # Get top of stack
            # If current point contributes less than the previous one, we merge
            if a[i] - i <= ax - x:
                s -= (ax + ax - x + l - 1) * (l - x) // 2
                l = x  # Update left boundary
                q.pop()  # Remove from stack
            else:
                break  # Otherwise, stop merging
        # Adjust left to ensure we don't go below the required damage
        l = max(l, i - a[i] + 1)
        q.append((l, a[i] - i + l))  # Push updated value to stack
        s += (a[i] - i + l + a[i]) * (i - l + 1) // 2  # Add contribution to running sum
        r[i] = s - a[i]  # Store the value in result array
    return r


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = f(a)  # Compute forward contributions
    c = f(a[::-1])[::-1]  # Compute backward contributions by reversing input and result
    print(sum(a) - max([b[i] + c[i] for i in range(n)]))  # Minimum MP needed


# https://github.com/VaHiX/CodeForces/
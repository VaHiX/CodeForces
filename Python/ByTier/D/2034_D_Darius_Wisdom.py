# Problem: CF 2034 D - Darius' Wisdom
# https://codeforces.com/contest/2034/problem/D

"""
Problem: Darius' Wisdom
Approach:
- The goal is to sort the columns (represented as array of 0,1,2) in non-decreasing order using allowed moves.
- A move is allowed only if difference between two columns is exactly 1, and we move one inscription from the higher to the lower.
- Strategy:
  1. First pass, move all 2s toward left (from right to left)
  2. Second pass, move all 0s toward right (from left to right)
  3. Between these operations, ensure we adjust positions of 1s appropriately.

Time Complexity: O(n) - Each element is visited at most a constant number of times.
Space Complexity: O(n) - For storing the moves and the input array.
"""

import sys

input = sys.stdin.readline


def ri():
    return int(input())


def rl(v_type=int):
    return list(map(v_type, input().split()))


def rs():
    return input().rstrip()


def out(x, sep=" "):
    return sep.join(map(str, x))


def process(a, n, path, phase):
    # phase = True means moving 2s to the left (left to right scan)
    # phase = False means moving 0s to the right (right to left scan)
    l, r = 1, n
    z = 1 if phase else n  # z points to where we can find a 1 to move

    while l < r:
        if phase:
            # Move l to the right until it finds a 2
            while l < r and a[l] != 2:
                l += 1
            # Move r to the left until it finds a non-2
            while l < r and a[r] == 2:
                r -= 1
        else:
            # Move l to the right until it finds a non-0
            while l < r and a[l] == 0:
                l += 1
            # Move r to the left until it finds a 0
            while l < r and a[r] != 0:
                r -= 1
        
        # If l < r implies we found valid pair to process
        if l < r:
            # Check if r has 1 (or l has 1), then swap directly
            if a[r] == 1 if phase else a[l] == 1:
                a[l], a[r] = a[r], a[l]
                path.append((l, r))  # Add move to path
            else:
                # Find 1 to move to facilitate swap
                # z keeps moving in direction to find a 1
                while a[z] != 1 if phase else a[z] != 1:
                    z += 1 if phase else -1
                # Transfer 1 from z to r
                a[z], a[r] = a[r], a[z]
                # Transfer from r to l (now r should be 1 and l should be 0/1)
                a[r], a[l] = a[l], a[r]
                path.append((z, r))  # First move
                path.append((r, l))  # Second move
                z = min(z, l) if phase else max(z, r)


def solve_case():
    n = ri()
    a = [0] + rl()  # Prepend 0 to make index 1-based as per problem description
    path = []
    process(a, n, path, True)   # Move 2s to the left
    process(a, n, path, False)  # Move 0s to the right
    path = [len(path)] + [out(x) for x in path]  # Prepend count of moves
    return out(path, "\n")


if __name__ == "__main__":
    T = int(input())
    ret = [solve_case() for ti in range(1, T + 1)]
    print(out(ret, "\n"))


# https://github.com/VaHiX/CodeForces/
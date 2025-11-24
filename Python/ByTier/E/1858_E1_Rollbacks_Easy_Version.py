# Problem: CF 1858 E1 - Rollbacks (Easy Version)
# https://codeforces.com/contest/1858/problem/E1

"""
Problem: E1. Rollbacks (Easy Version)
Purpose: Maintain an array with operations to add elements, remove last k elements, 
         rollback last operation, and count distinct elements.
Algorithms/Techniques: 
    - Stack-based rollback mechanism using history tracking
    - Efficient distinct count tracking using cumulative counts
    - Fast I/O for performance with large inputs
Time Complexity: O(q) amortized for all operations
Space Complexity: O(q) for storing array state and history

This implementation uses a stack of operations to support rollback functionality
and maintains a count of distinct elements efficiently.
"""

import os
import sys
from io import BytesIO, IOBase

BUFSIZE = 5096

input = lambda: sys.stdin.readline().rstrip("\r\n")


def I():
    return input()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


inf = float("inf")

from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


N = 1 << 20

q = II()

pos = [q] * N  # Position tracking for each element
n = 0

a = []  # Stack to store operation history
b = [0] * q  # Store last value for each position
c = [0] * (q + 1)  # Count of elements at each position
c[q] = n  # Initial count
s = [0] * (q + 1)  # Cumulative count of distinct elements

for _ in range(q):
    o = I()
    if o[0] == "+":  # Add element
        x = int(o[1:])
        # Store current state before change
        a.append([x, pos[x], b[n], pos[b[n]], s[n + 1]])
        # Update position tracking in the case of duplicates
        if pos[b[n]] == n:
            c[pos[b[n]]] -= 1
            pos[b[n]] = q
            c[pos[b[n]]] += 1
        # Update position tracking for element x
        if pos[x] > n:
            c[pos[x]] -= 1
            pos[x] = n
            c[pos[x]] += 1
        # Update cumulative count
        s[n + 1] = s[n] + c[n]
        b[n] = x
        n += 1
    elif o[0] == "-":  # Remove last k elements
        k = int(o[1:])
        n -= k
        a.append([-1, k])  # Mark as removal operation
    elif o == "?":  # Query distinct count
        ans = s[n]
        print(ans)
    else:  # Rollback operation
        tmp = a.pop()  # Get last operation
        if tmp[0] == -1:
            # If it was a removal, restore n
            n += tmp[1]
        else:
            # If it was an addition, restore state
            x, y, z, w, t = tmp
            n -= 1
            b[n] = z  # Restore previous value at this position
            s[n + 1] = t  # Restore cumulative count
            # Restore position tracking for x
            if pos[x] != y:
                c[pos[x]] -= 1
                pos[x] = y
                c[pos[x]] += 1
            # Restore position tracking for previous value z
            if pos[z] != w:
                c[pos[z]] -= 1
                pos[z] = w
                c[pos[z]] += 1


# https://github.com/VaHiX/CodeForces/
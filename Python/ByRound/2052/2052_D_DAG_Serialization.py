# Problem: CF 2052 D - DAG Serialization
# https://codeforces.com/contest/2052/problem/D

"""
D. DAG Serialization

Purpose:
This code solves a problem where we have a directed acyclic graph (DAG) of operations on a single-bit boolean register.
Each operation is either "set" or "unset", and each returns a boolean result ("true" or "false").
The initial state of the register is false.
We're given a partial order of these operations as edges in the DAG, and are to determine if there's a valid linear order such that:
- The topological order respects the DAG.
- The results returned by the operations match what's provided.

Algorithms/Techniques:
1. Topological sorting using Kahn's algorithm with a queue for each operation type.
2. State tracking of register value (0 = false, 1 = true) using a flag 'reg'.
3. Validation that every operation follows valid transition rules from the current register state.

Time Complexity: O(n + m)
Space Complexity: O(n + m)

The algorithm uses a modified topological sort based on operation types to ensure correct sequencing.
"""

import sys
from collections import deque

input = sys.stdin.readline
n = int(input())
adj = [[] for _ in range(n)]
cnt = [0] * n
type_ = [0] * n
p = [
    "unset false",
    "set true",
    "set false",
    "unset true",
]
for i in range(n):
    x = input().strip()
    type_[i] = p.index(x)  # Map operation name to integer id (0-3)
m = int(input())
for _ in range(m):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    adj[u].append(v)
    cnt[v] += 1  # Count incoming edges for topological sort

# Queue per operation type: 0=unset false, 1=set true, 2=set false, 3=unset true
queue = [deque() for _ in range(4)]
for i in range(n):
    if cnt[i] == 0:  # No prerequisites left
        queue[type_[i]].append(i)  # Add to corresponding type queue

ans = []
# Process operations in order: 0,1,2,3 (i.e. unset false, set true, set false, unset true)
for case in [0, 1, 2, 3, 0]:
    while queue[case]:
        u = queue[case].pop()  # Take from queue
        ans.append(u)  # Add to result list
        for v in adj[u]:  # For each successor
            cnt[v] -= 1  # Reduce its prerequisite count
            if cnt[v] == 0:  # If no more prerequisites
                queue[type_[v]].append(v)  # Add to appropriate queue

reg = 0  # Register state flag: 0 for false, 1 for true
verify = True
for i in ans:
    # Check if valid transition based on current register value and next operation type
    if reg:  # If register is currently "true"
        if type_[i] == 2:  # "set false" -> valid: set to false
            pass
        elif type_[i] == 3:  # "unset true" -> valid: set to false, return true
            reg = 0  # Register becomes false now
        else:  # Any other operation leads to invalid state
            verify = False
            break
    else:  # If register is currently "false"
        if type_[i] == 0:  # "unset false" -> valid: stay false, return true
            pass
        elif type_[i] == 1:  # "set true" -> valid: set to true, return true
            reg = 1  # Register becomes true now
        else:  # Any other operation leads to invalid state
            verify = False
            break

if verify and len(ans) == n:
    print(*[k + 1 for k in ans])  # Print indices as 1-based
else:
    print(-1)


# https://github.com/VaHiX/codeForces/
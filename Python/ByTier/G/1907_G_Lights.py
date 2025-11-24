# Problem: CF 1907 G - Lights
# https://codeforces.com/contest/1907/problem/G

"""
Algorithm: 
This problem involves turning off all lights by pressing switches. Each switch toggles two lights: itself and another light specified by the array `a`. 
The approach uses a topological sorting technique to find out which lights can be turned off without affecting others, followed by handling cycles using a greedy method.
Main idea:
1. Construct a dependency graph where each node represents a light and an edge from i to a[i] means pressing switch i affects light a[i].
2. Process nodes in topological order to toggle lights in a controlled manner.
3. For remaining cycles, select the better set of switches to minimize total presses.
Time Complexity: O(n) - Each node is processed at most twice.
Space Complexity: O(n) - For storing graph, queue and auxiliary arrays.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
t = int(input())
inf = pow(10, 9) + 1
ans = []
for _ in range(t):
    n = int(input())
    s = list(input().rstrip())
    s = [0] + [i & 1 for i in s]  # Convert input string to boolean list, 0-indexed
    a = [0] + list(map(int, input().split()))  # 0-indexed array for easier access
    cnt = [0] * (n + 1)  # In-degree count for each node
    for i in a[1:]:  # Count in-degrees
        cnt[i] += 1
    q = []  # Queue for topological sort
    for i in range(1, n + 1):
        if not cnt[i]:
            q.append(i)
    ans0 = []  # Stores the switches to press
    for i in q:
        j = a[i]  # The light affected by switch i
        if s[i]:  # If light i is on
            ans0.append(i)
            s[i] ^= 1  # Toggle light i
            s[j] ^= 1  # Toggle light j (affected by switch i)
        cnt[j] -= 1  # Decrease in-degree of light j
        if not cnt[j]:  # If in-degree becomes 0, add to queue
            q.append(j)
    ok = 1  # Flag to check if solution exists
    for i in range(1, n + 1):
        if not cnt[i]:  # Skip if already processed in topological sort
            continue
        # Start processing a cycle (a group of interdependent switches)
        x, u, v = [i], [], []  # x: list of nodes in cycle, u: switches to press if light is on, v: switch if light is off
        if s[i]:  # If first light in cycle is on
            u.append(i)
            s[i] ^= 1
            s[a[i]] ^= 1  # Toggle both affected lights
        else:
            v.append(i)
        # Traverse the cycle
        while a[x[-1]] ^ i:  # Continue until we reach back to i
            x.append(a[x[-1]])
            j = x[-1]
            if s[j]:  # Light j is on
                u.append(j)
                s[j] ^= 1
                s[a[j]] ^= 1  # Toggle both affected lights
            else:
                v.append(j)
        if s[i] or s[j]:  # If either starting or ending light is still on after traversal, impossible to solve
            ok = 0
            break
        # Choose the smaller set of switches to minimize operations
        if len(u) > len(v):
            u = v
        for j in u:
            ans0.append(j)
        for j in x:
            cnt[j] = 0  # Mark nodes in cycle as processed
    if ok:
        k = len(ans0)
        ans.append(str(k))
        ans.append(" ".join(map(str, ans0)))
    else:
        ans0 = -1
        ans.append(str(ans0))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/
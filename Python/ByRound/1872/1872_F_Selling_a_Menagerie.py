# Problem: CF 1872 F - Selling a Menagerie
# https://codeforces.com/contest/1872/problem/F

"""
Code Purpose:
This code solves the problem of finding an optimal order to sell animals in a menagerie to maximize profit. 
Each animal is afraid of another animal, and the selling value depends on whether the afraid animal was sold before.
The algorithm uses topological sorting-like approach to process nodes with no incoming edges first, 
and then handles cycles by finding minimum cost nodes in cycles and processing them appropriately.

Algorithms/Techniques:
- Topological sorting using in-degree tracking
- Cycle detection and handling in directed graphs
- Greedy approach within cycles to minimize cost

Time Complexity: O(n)
Space Complexity: O(n)
"""

import random
import sys

input = sys.stdin.readline
rd = random.randint(10**9, 2 * 10**9)

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    c = list(map(int, input().split()))
    # cnt[i] keeps track of in-degrees for each node
    cnt = [0] * n
    for i in range(n):
        cnt[a[i] - 1] += 1
    from collections import deque

    # Initialize queue with nodes having in-degree 0
    q = deque([i for i in range(n) if cnt[i] == 0])
    ans = []
    # Process nodes in topological order
    while q:
        i = q.popleft()
        ans.append(i + 1)
        # Reduce in-degree of the node that i is afraid of
        cnt[a[i] - 1] -= 1
        # If in-degree becomes 0, add to queue
        if cnt[a[i] - 1] == 0:
            q.append(a[i] - 1)
    # Handle remaining nodes (part of cycles)
    for i in range(n):
        if cnt[i] > 0:
            mi = 10**18
            # Find the minimum cost node in the cycle
            while cnt[i] > 0:
                if c[i] < mi:
                    mi = c[i]
                    idx = i
                cnt[i] = 0
                i = a[i] - 1
            # Process the cycle by going back to start
            p = a[idx] - 1
            while p != idx:
                ans.append(p + 1)
                p = a[p] - 1
            ans.append(idx + 1)
    print(*ans)


# https://github.com/VaHiX/CodeForces/
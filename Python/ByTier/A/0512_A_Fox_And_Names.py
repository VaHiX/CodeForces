# Contest 512, Problem A: Fox And Names
# URL: https://codeforces.com/contest/512/problem/A

from collections import defaultdict, deque
import sys


def fox_and_names(names):

    # Build graph
    adj = defaultdict(list)
    indegree = {chr(c): 0 for c in range(ord("a"), ord("z") + 1)}

    n = len(names)
    for i in range(n - 1):
        s, t = names[i], names[i + 1]
        # Find first differing character
        min_len = min(len(s), len(t))
        for j in range(min_len):
            if s[j] != t[j]:
                # s[j] -> t[j]
                adj[s[j]].append(t[j])
                break
        else:
            # If no break & s longer than t ⇒ impossible
            if len(s) > len(t):
                return "Impossible"

    # Compute in-degrees
    for u in adj:
        for v in adj[u]:
            indegree[v] += 1

    # Kahn's algorithm
    q = deque([ch for ch in indegree if indegree[ch] == 0])
    order = []
    while q:
        u = q.popleft()
        order.append(u)
        for v in adj[u]:
            indegree[v] -= 1
            if indegree[v] == 0:
                q.append(v)

    # If we didn't include all 26 letters, there's a cycle
    if len(order) < 26:
        return "Impossible"

    return "".join(order)


n = int(input())
names = []
for _ in range(n):
    names.append(input())
print(fox_and_names(names))

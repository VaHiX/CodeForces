# Problem: CF 512 A - Fox And Names
# https://codeforces.com/contest/512/problem/A

from collections import defaultdict, deque


def fox_and_names(names):
    # Build adjacency list and in-degree map for topological sort
    adj = defaultdict(list)
    indegree = {chr(c): 0 for c in range(ord("a"), ord("z") + 1)}

    n = len(names)
    # Compare each pair of consecutive names to infer order
    for i in range(n - 1):
        s, t = names[i], names[i + 1]

        min_len = min(len(s), len(t))
        for j in range(min_len):
            if s[j] != t[j]:
                # Add edge from s[j] to t[j] in the graph
                adj[s[j]].append(t[j])
                break
        else:
            # If all characters match up to min_len and s is longer than t,
            # it's impossible to sort lexicographically
            if len(s) > len(t):
                return "Impossible"

    # Compute in-degrees for topological sorting
    for u in adj:
        for v in adj[u]:
            indegree[v] += 1

    # Initialize queue with nodes having zero in-degree
    q = deque([ch for ch in indegree if indegree[ch] == 0])
    order = []
    # Perform topological sort
    while q:
        u = q.popleft()
        order.append(u)
        for v in adj[u]:
            indegree[v] -= 1
            if indegree[v] == 0:
                q.append(v)

    # If we didn't include all 26 letters, it's impossible
    if len(order) < 26:
        return "Impossible"

    return "".join(order)


n = int(input())
names = []
for _ in range(n):
    names.append(input())
print(fox_and_names(names))

# ### **Code Purpose**
# This code determines if there exists a valid permutation of the English alphabet such that the provided list of names is sorted in lexicographical order according to that permutation. It models the problem as a topological sorting task over a directed graph derived from the relative ordering of the characters in consecutive names.

# ### **Algorithms & Techniques Used**
# - Directed Graph Construction: For each pair of consecutive names, the first differing character implies an ordering constraint.
# - Topological Sort (Kahn's Algorithm): Used to derive a consistent ordering of characters based on dependencies.
# - In-degree Tracking: Essential for Kahn’s algorithm to detect nodes with no incoming edges.

# ### **Time and Space Complexity**
# - **Time Complexity:** O(N × M), where N is the number of names and M is the average length of the names. This accounts for comparing the strings and building the graph.
# - **Space Complexity:** O(1) additional space excluding the input and output. The graph has at most 26 vertices and a few tens of edges for a valid case, so it's constant space.

# https://github.com/VaHiX/CodeForces/
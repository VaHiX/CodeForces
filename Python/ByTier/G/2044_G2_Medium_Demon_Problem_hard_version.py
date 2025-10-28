# Problem: CF 2044 G2 - Medium Demon Problem (hard version)
# https://codeforces.com/contest/2044/problem/G2

"""
G2. Medium Demon Problem (hard version)

Algorithm:
- This problem models a directed graph where each node (spider) points to another node (recipient).
- The goal is to find the first year when the distribution of plushies stabilizes.
- Key observation: The process reaches a cycle in the directed graph, and we simulate the flow of plushies year by year until it stabilizes.
- We use topological sorting approach with reverse edges to compute how many steps each node takes to reach a terminal state (where all nodes have zero in-degree).

Time Complexity: O(n) per test case, where n is the number of spiders.
Space Complexity: O(n) for storing adjacency counts and queues.

Approach:
1. Count the in-degrees of each node (`cnt`).
2. Initialize a queue with nodes having 0 in-degree.
3. Process levels using BFS-like propagation to compute how many steps it takes for each spider to be involved in final cycle or be stable.
4. Find the maximum depth among all terminal nodes and add 2 (since year 1 is not stable, and we need to account for one more step after last change).
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve_case():
    n = int(input())
    r = list(map(lambda x: int(x) - 1, input().split()))  # Convert to 0-indexed
    cnt = [0] * n  # Count in-degrees
    for i in range(n):
        cnt[r[i]] += 1  # Each spider points to another -> increment in-degree of target
    q = [i for i in range(n) if cnt[i] == 0]  # Nodes with no incoming edges (initially)
    if not q:
        return 2  # No zero in-degree, so cycle exists; stable at year 2

    t = [1] * n  # Initialize time counter for each node
    while q:
        qn = []
        for i in q:  # For each node with zero in-degree
            cnt[r[i]] -= 1  # Reduce in-degree of its target
            t[r[i]] += t[i]  # Propagate time to target node (number of plushies it receives)
            if cnt[r[i]] == 0:
                qn.append(r[i])  # Add to queue if now has zero in-degree
        q = qn

    ans = max(t[i] for i in range(n) if cnt[i] == 0) + 2  # Max time among root nodes + 2
    return ans


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/
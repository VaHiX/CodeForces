# Problem: CF 1665 C - Tree Infection
# https://codeforces.com/contest/1665/problem/C

"""
Tree Infection Problem

Algorithm:
This problem involves finding the minimum time to infect an entire tree starting from the root.
The tree is rooted at vertex 1, and each second two operations occur:
1. Spreading: If a node has at least one infected child, we can infect one more child.
2. Injection: We can choose any healthy node to infect.

This solution uses binary search on the answer and greedy approach:
- For each possible number of seconds (mid), we simulate the process to check if it's feasible.
- We calculate the maximum number of nodes that can be infected in 'mid' seconds.

Time Complexity: O(n * log(n)) due to binary search over time (up to n) and sorting degrees
Space Complexity: O(n) for storing degrees and other arrays

The key idea is to determine the minimum number of seconds needed by checking feasibility using a greedy simulation.
"""
t = int(input())
for _ in range(t):
    n = int(input())
    p = list(map(int, input().split()))
    d = [0] * n
    for i in range(n - 1):
        d[p[i] - 1] += 1  # Calculate degree of each node (number of children)
    d.sort()
    l, r = 0, n * n  # Binary search bounds
    while l <= r:
        s, c, m = 0, 1, (l + r) // 2  # s = spreadable nodes, c = current nodes, m = mid (time)
        for i in range(n - 1, -1, -1):
            if d[i] == 0:
                break
            c += max(0, s + d[i] - m)  # Calculate additional nodes needed to be infected
            s += 1
        if m - s >= c:  # If enough time to infect all nodes
            r = m - 1
        else:
            l = m + 1
    print(l)


# https://github.com/VaHiX/CodeForces/
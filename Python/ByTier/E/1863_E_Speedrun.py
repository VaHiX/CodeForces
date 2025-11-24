# Problem: CF 1863 E - Speedrun
# https://codeforces.com/contest/1863/problem/E

"""
Algorithm: Topological Sort with Time Calculation
Approach:
1. Build a directed graph from dependencies and calculate in-degrees.
2. Use topological sorting to determine earliest possible completion times.
3. For each node, compute the minimum start time based on dependencies and hour constraints.
4. Calculate minimum time needed to complete all quests by trying different starting orderings.

Complexity:
Time: O(n + m + n log n) where n is number of quests and m is number of dependencies.
Space: O(n + m) for graph storage and auxiliary arrays.
"""

import sys

input = sys.stdin.readline


def readList():
    return list(map(int, input().split()))


def readInt():
    return int(input())


def readInts():
    return map(int, input().split())


def readStr():
    return input().strip()


def solve():
    n, m, k = readInts()
    H = [0] + readList()  # Hours for each quest (1-indexed)
    graph = [[] for _ in range(n + 1)]
    ind = [0] * (n + 1)
    for _ in range(m):
        a, b = readInts()
        graph[a].append(b)
        ind[b] += 1
    st = [(i, 0) for i in range(1, n + 1) if not ind[i]] # Starting nodes (no incoming edges)
    arr = sorted([v[0] for v in st], key=lambda x: H[x]) # Sort starting nodes by hour
    d = [0] * (n + 1)
    while st:
        node, date = st.pop()
        for nei in graph[node]:
            # If current node's hour <= neighbor's hour, no new day needed
            # Else, advance to next day
            d[nei] = max(d[nei], date) if H[node] <= H[nei] else max(d[nei], date + 1)
            ind[nei] -= 1
            if ind[nei] == 0:
                st.append((nei, d[nei]))
    # Determine minimum total time needed to finish all quests
    fnt = max([d[i] * k + H[i] for i in range(n + 1)])
    ans = fnt - H[arr[0]] # Start with earliest time and initial quest
    for i in range(len(arr) - 1):
        st = [arr[i]]
        fnt = max(fnt, k + H[arr[i]])
        d[arr[i]] = 1
        stt = H[arr[i + 1]]
        while st:
            node = st.pop()
            for nei in graph[node]:
                # If neighbor hour is less than current hour, add one day
                if d[nei] < d[node] + (H[nei] < H[node]):
                    d[nei] = d[node] + (H[nei] < H[node])
                    st.append(nei)
                    fnt = max(fnt, d[nei] * k + H[nei])
        ans = min(ans, fnt - stt)
    return ans


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/
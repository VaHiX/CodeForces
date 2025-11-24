# Problem: CF 1815 C - Between
# https://codeforces.com/contest/1815/problem/C

"""
Algorithm: Graph traversal with BFS to determine if sequence can be infinite
Techniques:
- BFS traversal to find distances from node 1
- Detect cycles in graph to determine infinite sequence possibility
- Construct sequence based on distances

Time Complexity: O(n + m) for each test case, where n is number of nodes and m is number of edges
Space Complexity: O(n + m) for storing the graph and auxiliary arrays

Approach:
1. Build a reverse adjacency list where edge (u,v) means v -> u in the graph
2. Run BFS from node 1 to compute distances to all reachable nodes
3. If any node is unreachable from 1, sequence is infinite (return "INFINITE")
4. Group nodes by their BFS distances
5. Construct sequence by traversing groups in reverse order of distances
"""

import sys
from collections import deque


def input_general():
    return sys.stdin.readline().rstrip("\r\n")


def input_num():
    return int(sys.stdin.readline().rstrip("\r\n"))


def input_multi(x=int):
    return map(x, sys.stdin.readline().rstrip("\r\n").split())


def input_list(x=int):
    return list(input_multi(x))


def main():
    n, m = input_multi()
    # Create reverse adjacency list to represent dependency graph
    edge_dict = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = input_multi()
        # Add edge from v to u (reversing direction)
        edge_dict[v].append(u)

    # seen[i] stores the distance from node 1 to node i
    seen = [-1] * (n + 1)
    seen[1] = 1
    dq = deque([1])

    # BFS traversal to compute distances from node 1
    while dq:
        u = dq.popleft()
        for v in edge_dict[u]:
            if seen[v] > 0:
                continue

            seen[v] = seen[u] + 1
            dq.append(v)

    # Check if any node is unreachable from 1
    # If so, the sequence can be infinitely long
    occ_dict = [[] for _ in range(n + 1)]
    max_occ = -1
    for i, o in enumerate(seen[1:], 1):
        if o == -1:
            print("INFINITE")
            return

        # Group nodes by their distance from node 1
        occ_dict[o - 1].append(i)
        max_occ = max(max_occ, o - 1)

    answer = []
    template = deque()
    # Construct final sequence by traversing distance groups in reverse order
    for occ in range(max_occ, -1, -1):
        template.extendleft(occ_dict[occ])
        answer.extend(template)

    print("FINITE")
    print(len(answer))
    print(" ".join([str(x) for x in answer]))


if __name__ == "__main__":
    cases = input_num()

    for _ in range(cases):
        main()


# https://github.com/VaHiX/CodeForces/
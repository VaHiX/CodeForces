# Problem: CF 1990 E2 - Catch the Mole(Hard Version)
# https://codeforces.com/contest/1990/problem/E2

"""
Algorithm: Tree Search with Binary-Like Strategy
Approach:
- This problem uses a strategy similar to binary search on a tree to find the mole's position
- We compute for each node how many nodes would be eliminated if we query that node
- The node that eliminates the maximum number of possibilities is chosen for querying
- Based on query result, we either:
  1. Narrow down to subtree if mole is in that subtree
  2. Move mole to parent and eliminate current subtree if mole is not in that subtree

Time Complexity: O(n^2) - For each query, we process all nodes to calculate sizes and parent counts
Space Complexity: O(n) - For storing tree structure, parent information, and auxiliary arrays

Key Components:
- Tree traversal to build parent relationships (DFS)
- Size calculation for each subtree
- Parent count calculation 
- Query selection based on maximum elimination potential
"""
def I():
    return input()

def II():
    return int(input())

def GMI():
    return map(lambda x: int(x) - 1, input().split())

def query(x):
    print("?", x + 1, flush=True)
    return II()


def answer(x):
    print("!", x + 1, flush=True)


def f(x):
    # Calculates the maximum number of nodes that can be eliminated by querying node x
    # This is based on subtree size and parent relationship
    return max(
        size[x],
        is_parent[0] - is_parent[x] - (1 if x and parent_cnt[parent[x]] == 1 else 0),
    )


t = II()
for _ in range(t):
    n = II()
    path = [[] for _ in range(n)]

    for _ in range(n - 1):
        u, v = GMI()
        path[u].append(v)
        path[v].append(u)

    parent = [-1] * n

    stack = [0]
    order = []

    while stack:
        u = stack.pop()
        for v in path[u]:
            if parent[u] != v:
                parent[v] = u
                stack.append(v)
                order.append(v)

    order.reverse()

    parent[0] = 0
    possible = [1] * n

    while sum(possible) > 1:
        size = possible[:]
        for u in order:
            size[parent[u]] += size[u]

        parent_cnt = [0] * n
        for i in range(n):
            if possible[i]:
                parent_cnt[parent[i]] += 1

        is_parent = [1 if x > 0 else 0 for x in parent_cnt]
        for u in order:
            is_parent[parent[u]] += is_parent[u]

        chosen_node = 0
        for i in range(1, n):
            if f(i) < f(chosen_node):
                chosen_node = i

        # Query the chosen node to see if mole is in its subtree
        if query(chosen_node):
            # Mole is in the subtree, keep only nodes in that subtree
            npossible = [0] * n
            stk = [chosen_node]
            while stk:
                u = stk.pop()
                if possible[u]:
                    npossible[u] = 1
                    for v in path[u]:
                        if parent[v] == u:
                            stk.append(v)
            possible = npossible
        else:
            # Mole is not in the subtree, eliminate that subtree and move mole to parent
            stk = [chosen_node]
            while stk:
                u = stk.pop()
                possible[u] = 0
                for v in path[u]:
                    if parent[v] == u:
                        stk.append(v)
            npossible = [0] * n
            for i in range(n):
                if possible[i]:
                    npossible[parent[i]] = 1
            possible = npossible

    answer(possible.index(1))


# https://github.com/VaHiX/CodeForces/
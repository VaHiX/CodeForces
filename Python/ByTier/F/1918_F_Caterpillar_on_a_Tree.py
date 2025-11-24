# Problem: CF 1918 F - Caterpillar on a Tree
# https://codeforces.com/contest/1918/problem/F

"""
Algorithm: Tree Traversal with Greedy Approach and Teleportation Optimization

This solution computes the minimum time to visit all nodes in a tree starting from the root,
with a limited number of teleports to the root. The approach uses depth-first search (DFS) 
to calculate node depths and determine optimal traversal paths.

Key Techniques:
- Depth-First Search (DFS) for building the tree and computing node depths
- Greedy selection of leaf nodes to minimize traversal time using available teleports
- Path optimization through careful use of teleportation

Time Complexity: O(n log n) due to sorting of children by depth
Space Complexity: O(n) for storing adjacency list and auxiliary data structures

The core idea is to build the tree, compute for each node its maximum depth of subtree,
and then traverse greedily to minimize the total crawling time, using teleports optimally
at leaf nodes.
"""

def main() -> None:
    print(solve())


def solve():
    [n, k] = [int(i) for i in input().split(" ")]
    array = [int(i) for i in input().split(" ")]
    adj = {}
    for i, a in enumerate(array):
        v = i + 2
        adj.setdefault(a, []).append(v)
    time = 0
    k += 1  # Increment k because we can use one additional teleport at the start
    leafs = []
    node_max_depth = {}
    stack = [(1, 0, 0)]
    while stack:
        (node, flag, depth) = stack.pop()
        if not adj.get(node, []):
            # Base case: if no children, store depth at leaf
            node_max_depth[node] = depth
            continue
        if flag == 0:
            # First time visiting, prepare to process children
            stack.append((node, 1, depth))
            for n in adj[node]:
                stack.append((n, 0, depth + 1))
        else:
            # Second time visiting, compute depth based on children
            max_depth = 0
            for n in adj[node]:
                max_depth = max(max_depth, node_max_depth[n])
            node_max_depth[node] = max_depth
    # Sort children by descending depth to enable greedy traversal
    for _k, v in adj.items():
        adj[_k] = sorted(v, key=lambda x: node_max_depth[x], reverse=True)
    stack = [(1, 0, 0)]
    while stack:
        [node, dist_to_white, dist_to_1] = stack.pop()
        for i, n in enumerate(adj.get(node, [])):
            time += 1  # Going down to child node
            if i == 0:
                # First child - continue path from current node
                stack.append((n, dist_to_white + 1, dist_to_1 + 1))
            else:
                # Other children - return to parent first, then go down
                stack.append((n, 1, dist_to_1 + 1))
            time += 1  # Return back to parent (or continue path)
        if not adj.get(node, None) and (dist_to_1 - dist_to_white) < dist_to_white:
            # Add leaf node contribution only if beneficial to teleport
            leafs.append(dist_to_1 - 2 * dist_to_white)
    leafs.sort()  # Sort in ascending order to pick best (smallest) ones for teleporting
    for i in range(k):
        if i >= len(leafs):
            break
        time += leafs[i]  # Add benefit of teleporting to these optimized paths
    return time


main()


# https://github.com/VaHiX/CodeForces/
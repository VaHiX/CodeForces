# Problem: CF 1900 C - Anji's Binary Tree
# https://codeforces.com/contest/1900/problem/C

"""
Binary Tree Path Optimization

This code solves the problem of finding the minimum number of operations to make a path from the root to a leaf in a binary tree, where each node has a direction character ('U', 'L', or 'R') that determines movement.

Approach:
- Use BFS to explore all possible paths from the root
- For each node, determine if moving to a child is valid based on the character:
  - 'U': move to parent (not applicable for root)
  - 'L': move to left child
  - 'R': move to right child
- Count operations needed to change characters when needed for valid movement
- Return minimum operations to reach any leaf

Time Complexity: O(n) where n is the number of vertices, as we visit each node at most once in BFS
Space Complexity: O(n) for storing children and the BFS queue
"""

import sys
from collections import deque


def main():
    data = sys.stdin.read().splitlines()
    t = int(data[0].strip())
    index = 1
    out_lines = []
    for _ in range(t):
        n = int(data[index].strip())
        index += 1
        s = data[index].strip()
        index += 1
        children = [0] * (n + 1)
        for i in range(1, n + 1):
            line = data[index].split()
            index += 1
            l_i = int(line[0])
            r_i = int(line[1])
            children[i] = (l_i, r_i)
        q = deque()
        q.append((1, 0))  # (current_node, operations_cost)
        ans = float("inf")
        while q:
            u, cost = q.popleft()
            l_i, r_i = children[u]
            # If we reached a leaf, update answer with minimum operations
            if l_i == 0 and r_i == 0:
                ans = min(ans, cost)
                continue
            # If left child exists, check if we need to change character 'L' to move left
            if l_i != 0:
                add = 0 if s[u - 1] == "L" else 1  # 0 if correct, 1 if change needed
                q.append((l_i, cost + add))
            # If right child exists, check if we need to change character 'R' to move right
            if r_i != 0:
                add = 0 if s[u - 1] == "R" else 1  # 0 if correct, 1 if change needed
                q.append((r_i, cost + add))
        out_lines.append(str(ans))
    print("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
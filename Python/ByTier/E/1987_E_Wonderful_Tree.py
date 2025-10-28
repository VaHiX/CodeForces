# Problem: CF 1987 E - Wonderful Tree!
# https://codeforces.com/contest/1987/problem/E

"""
Algorithm: Tree Traversal with Diff Array
Approach:
1. Build the tree from parent information.
2. Perform BFS to calculate for each node the difference between the sum of its children and its own value.
3. Process nodes in reverse BFS order (from leaves to root).
4. For each node, if its diff is positive, move operations up the tree to parent nodes to compensate.

Time Complexity: O(n)
Space Complexity: O(n)

This solution leverages a BFS traversal to compute how much the value of a node needs to be increased 
to satisfy the "wonderful" condition. Then, it propagates these increases up the tree to optimize 
the number of operations needed.

The key idea is to use a difference array technique on the tree:
- For each node, we compute the deficit or excess needed at that node (sum of children - current value).
- We process nodes in reverse BFS order to propagate these deficits upwards efficiently.
"""

from collections import deque
from sys import stdin, stdout

input = lambda: stdin.readline().rstrip()
print = lambda *x, sep=" ", end="\n": stdout.write(sep.join(map(str, x)) + end)


def out(l):
    print(" ".join(map(str, l)))


def yes():
    print("Yes")


def no():
    print("No")


def alice():
    print("Alice")


def bob():
    print("Bob")


def bfs(root, par=0):
    que = deque()
    que.appendleft(root)
    while len(que) != 0:
        par = que.pop()
        tra.append(par)
        # For each child, add its value to the diff of parent
        for i, child in enumerate(adj_list[par - 1]):
            diff[par - 1] += a[child - 1]
            que.appendleft(child)
            lvl[child - 1] = lvl[par - 1] + 1
        # If node has no children, set diff to infinity
        if not adj_list[par - 1]:
            diff[par - 1] = float("inf")
        else:
            # Subtract the current node's own value
            diff[par - 1] -= a[par - 1]


def solve():
    global adj_list, a, diff, lvl, tra
    n = int(input())
    a = list(map(int, input().split()))
    par = list(map(int, input().split()))
    diff = [0] * n
    lvl = [0] * n
    tra = []
    adj_list = [[] for i in range(n)]
    # Build adjacency list (children of each node)
    for i, j in enumerate(par):
        adj_list[j - 1].append(i + 2)
    bfs(1)
    ans = 0
    # Process all nodes in BFS order 
    for i in tra:
        if diff[i - 1] > 0:
            j = i
            # Propagate the diff upward to parent nodes
            while i != 1 and diff[j - 1] > 0:
                i = par[i - 2]
                if diff[i - 1] < 0:
                    k = min(diff[j - 1], -diff[i - 1])
                    ans += (lvl[j - 1] - lvl[i - 1]) * k
                    diff[i - 1] += k
                    diff[j - 1] -= k
    print(ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/
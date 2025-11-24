# Problem: CF 2053 E - Resourceful Caterpillar Sequence
# https://codeforces.com/contest/2053/problem/E

"""
E. Resourceful Caterpillar Sequence

Purpose:
This code solves a game theory problem on a tree where two players (Nora and Aron) move a caterpillar.
A caterpillar is defined by a pair of vertices (p, q), and its "dominance" includes all vertices on the simple path from p to q.
Players take turns moving the caterpillar:
- Nora moves the head (p) towards an adjacent vertex that is not dominated.
- Aron moves the tail (q) towards an adjacent vertex that is not dominated.
The game ends when either p or q becomes a leaf, with corresponding winner:
- If p is a leaf → Nora wins
- If q is a leaf → Aron wins
- If both initially are leaves, or after 10^100 turns → tie

Algorithms/Techniques:
- Tree representation using adjacency lists
- Identification of leaves and near-leaves via node degrees (nodes with degree 1)
- Enumerative analysis to compute number of winning pairs for Aron

Time Complexity: O(n) per test case, where n is the number of nodes in the tree.
Space Complexity: O(n) for storing the adjacency list and auxiliary arrays.

"""

import sys

read = sys.stdin.readline
input = lambda: read().rstrip()
ir = lambda: int(read())
rir = lambda: range(int(read()))
mir = lambda: map(int, read().split())
lmir = lambda: list(map(int, read().split()))


def solve():
    n = ir()
    tree = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = mir()
        tree[u - 1].append(v - 1)
        tree[v - 1].append(u - 1)
    is_leaf = [len(nbs) == 1 for nbs in tree]
    # Find nodes that are not leaves but have at least one leaf neighbor
    near = [
        i
        for i, nbs in enumerate(tree)
        if not is_leaf[i] and any(map(is_leaf.__getitem__, nbs))
    ]
    num_leaves = sum(is_leaf)
    num_far = n - num_leaves - len(near)  # Nodes that are neither leaves nor near to a leaf
    turn0 = num_leaves * (n - num_leaves)  # Count of pairs (p, q):
                                           # p is leaf, q is not leaf
    # For each "near" node, count how many non-leaf neighbors it has.
    # Total such contributions from all 'near' nodes give the number
    # of ways Aron can make a move leading to a win.
    turn1 = num_far * (sum(not is_leaf[j] for i in near for j in tree[i]) - len(near))
    print(turn0 + turn1)


def main():
    for _ in rir():
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/
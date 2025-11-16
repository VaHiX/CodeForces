# Problem: CF 1970 C3 - Game on Tree (Hard)
# https://codeforces.com/contest/1970/problem/C3

"""
Algorithm: Game on Tree (Hard)
Approach: 
    - For each node, calculate the number of moves available from that node (i.e., the number of inactive neighbors)
    - Use DFS traversal to propagate this information up the tree, calculating the nimber (game state) for each node
    - The winner is determined based on the nimber of the starting node:
        - If the nimber > 0, Ron wins (first player advantage)
        - If the nimber = 0, Hermione wins (second player advantage)

Time Complexity: O(n) - Single pass DFS traversal with O(1) operations
Space Complexity: O(n) - Storage for adjacency list, visited array, stack, and node information
"""

import collections
import gc
import sys

gc.disable()


class Tree:

    def __init__(self, num_of_nodes, debug=False):
        self.dfs_nodes = None
        self.visited = None
        self.num_of_nodes = num_of_nodes
        self.edges = [[] for _ in range(self.num_of_nodes + 10)]
        self.debug = debug
        self.enable_collect = True
        self.enable_dfs_preprocess = True
        self.enable_dfs_postprocess = True
        self.enable_bfs_preprocess = True
        self.enable_bfs_postprocess = True
        self.reset()

    def debug_print(self, *args):
        if self.debug:
            print("[debug]", *args)

    def add_edge(self, u, v):

        self.edges[u].append(v)
        self.edges[v].append(u)

    def set_root(self, root):
        self.root = root

    def reset(self):
        self.visited = [0] * len(self.edges)

        self.dummy()

    def dummy(self):
        self.debug_print("Tree dummy")

    def dfs_recursive(self, i):
        self.visited[i] = 1
        self.preprocess(i)
        neighbour: int
        for neighbour in self.edges[i]:
            if self.visited[neighbour] != 1:
                self.dfs_recursive(neighbour)

        self.postprocess(i)

    def bfs_preprocess(self, i):
        self.preprocess(i)

    def bfs_postprocess(self, i):
        self.postprocess(i)

    def bfs(self, beg):
        deq = collections.deque([beg])
        self.visited = [0] * len(self.edges)
        q = []

        while deq:
            i = deq.popleft()
            self.visited[i] = 1
            q.append(i)
            if self.enable_bfs_preprocess:
                self.bfs_preprocess(i)
            neighbour: int
            for neighbour in self.edges[i]:
                if self.visited[neighbour] == 0:
                    deq.append(neighbour)

        for i in reversed(q):
            if self.enable_bfs_postprocess:
                self.bfs_postprocess(i)
            if self.enable_collect:
                self.precollect(i)
                for neighbour in self.edges[i]:
                    if self.visited[neighbour] == 2:
                        self.collect(i, neighbour)
                self.postcollect(i)
            self.visited[i] = 2

    class DFSNode:
        def __init__(self, i, p):
            self.i = i
            self.p = p
            self.cursor = 0
            self.status = 0

    def dfs(self, beg):
        self.visited = [0] * len(self.edges)
        self.p = [0] * len(self.edges)
        self.cursor = [0] * len(self.edges)
        self.node_status = [0] * len(self.edges)
        self.p[beg] = -1
        deq = collections.deque([beg])

        while deq:
            i = deq.popleft()

            if self.node_status[i] == 0:
                self.visited[i] = 1
                if self.enable_dfs_preprocess:
                    self.dfs_preprocess(i)
                self.node_status[i] = 1
            if self.node_status[i] == 1:
                hit = False
                while (not hit) and self.cursor[i] < len(self.edges[i]):
                    neighbour = self.edges[i][self.cursor[i]]
                    if self.visited[neighbour] == 0:
                        self.p[neighbour] = i
                        deq.append(neighbour)
                        hit = True
                    self.cursor[i] += 1
                if not hit:
                    self.node_status[i] = 2
                else:
                    continue
            if self.node_status[i] == 2:
                if self.enable_collect:
                    self.precollect(i)
                    for neighbour in self.edges[i]:
                        if neighbour != self.p[i]:
                            self.collect(i, neighbour)
                    self.postcollect(i)
                if self.enable_dfs_postprocess:
                    self.dfs_postprocess(i)
                if self.p[i] != -1:
                    deq.append(self.p[i])
                self.node_status[i] = -1

    def dfs_preprocess(self, i):
        self.preprocess(i)

    def dfs_postprocess(self, i):
        self.postprocess(i)

    def precollect(self, i):
        self.debug_print("precollect", i)

    def collect(self, i, neighbour):
        self.debug_print("collect", i, neighbour)

    def postcollect(self, i):
        self.debug_print("postcollect", i)

    def preprocess(self, i):
        self.debug_print("in", i)

    def postprocess(self, i):
        self.debug_print("out", i)


class MyTree(Tree):
    def __init__(self, num_of_nodes, debug=False):
        super().__init__(num_of_nodes, debug)
        self.status = [0] * (num_of_nodes + 10)
        self.ans = [0] * (num_of_nodes + 10)
        self.stack: list[list[int]]
        self.stack = [[] for _ in range(self.num_of_nodes + 10)]
        self.stage = 0

    def print_status(self):
        if not self.debug:
            return
        tmp = []
        for i in range(1, self.num_of_nodes + 1):
            tmp.append(self.stack[i][-1])
        self.debug_print(tmp)

    def dfs_preprocess(self, i):
        if i == self.root:
            self.ans[i] = self.status[i]
            return

        p = self.p[i]
        p_status = self.stack[p][-1]
        i_status = self.stack[i][-1]
        new_p_status = p_status - (0 if i_status > 0 else 1)
        new_i_status = i_status + (1 if new_p_status == 0 else 0)
        self.stack[i].append(new_i_status)
        self.stack[p].append(new_p_status)
        self.ans[i] = new_i_status

    def dfs_postprocess(self, i):
        if i != self.root:
            p = self.p[i]
            self.stack[i].pop()
            self.stack[p].pop()

    def bfs_preprocess(self, i):
        pass

    def bfs_postprocess(self, i):
        pass

    def precollect(self, i):
        pass

    def collect(self, i, neighbour):
        if self.stage == 1:
            if self.status[neighbour] == 0:
                self.status[i] += 1
            return
        if self.stage == 2:
            pass

    def postcollect(self, i):
        pass


def debug_print(*args):
    debug = False
    if debug:
        print(*args)


def run():
    n, t = map(int, input().split())
    tree = MyTree(n, False)
    for _ in range(n - 1):
        u, v = sys.stdin.readline().split()
        u = int(u)
        v = int(v)
        tree.add_edge(u, v)

    tree.stage = 1
    tree.enable_bfs_preprocess = False
    tree.enable_bfs_postprocess = False
    tree.bfs(1)

    tree.stage = 2
    for i in range(1, tree.num_of_nodes + 1):
        debug_print("i", i)
        tree.stack[i].append(tree.status[i])
    tree.set_root(1)
    tree.enable_collect = False
    tree.dfs(1)

    query = sys.stdin.readline().split()
    for q in query:
        ansi = "Hermione\n"
        if tree.ans[int(q)] > 0:
            ansi = "Ron\n"

        sys.stdout.write(ansi)
    sys.stdout.flush()


if __name__ == "__main__":
    run()


# https://github.com/VaHiX/CodeForces/
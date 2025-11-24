# Problem: CF 1083 A - The Fair Nut and the Best Path
# https://codeforces.com/contest/1083/problem/A

"""
Algorithm: Tree Diameter / Dynamic Programming on Trees
Time Complexity: O(n)
Space Complexity: O(n)

This solution finds the maximum amount of gasoline that can be collected
while traveling from one city to another in a tree. The approach uses
dynamic programming on trees to compute the maximum path sum considering
gasoline consumption and acquisition at each node. The key insight is to
compute for each node the maximum gas that can be accumulated while
considering the best two paths going through its children.
"""

from sys import stdin


class FastIO:
    def __init__(self):
        self.random_seed = 0
        self.flush = False
        self.inf = 1 << 32
        self.dire4 = [(0, -1), (0, 1), (1, 0), (-1, 0)]
        self.dire8 = [(0, -1), (0, 1), (1, 0), (-1, 0)] + [
            (1, -1),
            (1, 1),
            (-1, -1),
            (-1, 1),
        ]
        return

    @staticmethod
    def read_int():
        return int(stdin.readline().rstrip())

    @staticmethod
    def read_float():
        return float(stdin.readline().rstrip())

    @staticmethod
    def read_list_ints():
        return list(map(int, stdin.readline().rstrip().split()))

    @staticmethod
    def read_list_ints_minus_one():
        return list(map(lambda x: int(x) - 1, stdin.readline().rstrip().split()))

    @staticmethod
    def read_str():
        return stdin.readline().rstrip()

    @staticmethod
    def read_list_strs():
        return stdin.readline().rstrip().split()

    def get_random_seed(self):
        import random

        self.random_seed = random.randint(0, 10**9 + 7)
        return

    def st(self, x):
        return print(x, flush=self.flush)

    def yes(self, s=None):
        self.st("Yes" if not s else s)
        return

    def no(self, s=None):
        self.st("No" if not s else s)
        return

    def lst(self, x):
        return print(*x, flush=self.flush)

    def flatten(self, lst):
        self.st("\n".join(str(x) for x in lst))
        return

    @staticmethod
    def max(a, b):
        return a if a > b else b

    @staticmethod
    def min(a, b):
        return a if a < b else b

    @staticmethod
    def ceil(a, b):
        return a // b + int(a % b != 0)

    @staticmethod
    def accumulate(nums):
        n = len(nums)
        pre = [0] * (n + 1)
        for i in range(n):
            pre[i + 1] = pre[i] + nums[i]
        return pre


class WeightedTree:
    def __init__(self, n):
        self.n = n
        self.point_head = [0] * (self.n + 1)
        self.edge_weight = [0]
        self.edge_from = [0]
        self.edge_to = [0]
        self.edge_next = [0]
        self.edge_id = 1
        self.parent = [-1]
        self.order = 0
        self.start = [-1]
        self.end = [-1]
        self.parent = [-1]
        self.depth = [0]
        self.order_to_node = [-1]
        return

    def add_directed_edge(self, u, v, w):
        assert 0 <= u < self.n
        assert 0 <= v < self.n
        self.edge_weight.append(w)
        self.edge_from.append(u)
        self.edge_to.append(v)
        self.edge_next.append(self.point_head[u])
        self.point_head[u] = self.edge_id
        self.edge_id += 1
        return

    def add_undirected_edge(self, u, v, w):
        assert 0 <= u < self.n
        assert 0 <= v < self.n
        self.add_directed_edge(u, v, w)
        self.add_directed_edge(v, u, w)
        return

    def get_edge_ids(self, u):
        assert 0 <= u < self.n
        i = self.point_head[u]
        ans = []
        while i:
            ans.append(i)
            i = self.edge_next[i]
        return

    def dfs_order(self, root=0):
        self.order = 0
        self.start = [-1] * self.n
        self.end = [-1] * self.n
        self.parent = [-1] * self.n
        stack = [root]
        self.depth = [0] * self.n
        self.order_to_node = [-1] * self.n
        while stack:
            i = stack.pop()
            if i >= 0:
                self.start[i] = self.order
                self.order_to_node[self.order] = i
                self.end[i] = self.order
                self.order += 1
                stack.append(~i)
                ind = self.point_head[i]
                while ind:
                    j = self.edge_to[ind]
                    if j != self.parent[i]:
                        self.parent[j] = i
                        self.depth[j] = self.depth[i] + 1
                        stack.append(j)
                    ind = self.edge_next[ind]
            else:
                i = ~i
                if self.parent[i] != -1:
                    self.end[self.parent[i]] = self.end[i]
        return

    def heuristic_merge(self):
        ans = [0] * self.n
        sub = [None for _ in range(self.n)]
        index = list(range(self.n))
        self.parent = [-1] * self.n
        self.depth = [0] * self.n
        stack = [0]
        while stack:
            i = stack.pop()
            if i >= 0:
                stack.append(~i)
                ind = self.point_head[i]
                while ind:
                    j = self.edge_to[ind]
                    if j != self.parent[i]:
                        self.parent[j] = i
                        self.depth[j] = self.depth[i] + 1
                        stack.append(j)
                    ind = self.edge_next[ind]
            else:
                i = ~i
                sub[index[i]] = {self.depth[i]: 1}
                ans[i] = self.depth[i]
                ind = self.point_head[i]
                while ind:
                    j = self.edge_to[ind]
                    if j != self.parent[i]:
                        a, b = index[i], index[j]
                        if len(sub[a]) > len(sub[b]):
                            res = ans[i]
                            a, b = b, a
                        else:
                            res = ans[j]
                        for x in sub[a]:
                            sub[b][x] = sub[b].get(x, 0) + sub[a][x]
                            if (sub[b][x] > sub[b][res]) or (
                                sub[b][x] == sub[b][res] and x < res
                            ):
                                res = x
                        sub[a] = None
                        ans[i] = res
                        index[i] = b
                    ind = self.edge_next[ind]
        return [ans[i] - self.depth[i] for i in range(self.n)]


class Solution:
    def __init__(self):
        return

    @staticmethod
    def main(ac=FastIO()):
        """
        url: url of the problem
        tag: algorithm tag
        """

        class Graph(WeightedTree):
            def tree_dp(self, nums):
                ans = [0] * self.n
                parent = [-1] * self.n
                stack = [0]
                res = max(nums)
                while stack:
                    i = stack.pop()
                    if i >= 0:
                        stack.append(~i)
                        ind = self.point_head[i]
                        while ind:
                            j = self.edge_to[ind]
                            if j != parent[i]:
                                parent[j] = i
                                stack.append(j)
                            ind = self.edge_next[ind]
                    else:
                        i = ~i
                        ind = self.point_head[i]
                        a = b = 0
                        # Calculate the two best paths from children
                        while ind:
                            j = self.edge_to[ind]
                            if j != parent[i]:
                                cur = ans[j] - self.edge_weight[ind]
                                if cur > a:
                                    a, b = cur, a
                                elif cur > b:
                                    b = cur
                            ind = self.edge_next[ind]
                        # Update the maximum result
                        res = max(res, a + b + nums[i])
                        # Store the maximum gas that can be collected starting from this node
                        ans[i] = a + nums[i]
                return res

        n = ac.read_int()
        graph = Graph(n)
        weights = ac.read_list_ints()
        for _ in range(n - 1):
            u, v, c = ac.read_list_ints_minus_one()
            # Add 1 to edge weights to account for gasoline consumed during travel
            graph.add_undirected_edge(u, v, c + 1)
        final = graph.tree_dp(weights)
        ac.st(final)
        return


Solution().main()


# https://github.com/VaHiX/CodeForces/
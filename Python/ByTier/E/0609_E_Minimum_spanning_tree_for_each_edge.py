# Contest 609, Problem E: Minimum spanning tree for each edge
# URL: https://codeforces.com/contest/609/problem/E

import math
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


class TreeMultiplicationMaxWeights:
    def __init__(self, n):
        self.n = n
        self.point_head = [0] * (self.n + 1)
        self.edge_weight = [0]
        self.edge_from = [0]
        self.edge_to = [0]
        self.edge_next = [0]
        self.edge_id = 1
        self.depth = [0]
        self.cols = max(2, math.ceil(math.log2(self.n)))
        self.weights = [-1]
        self.father = [-1]
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

    def build_multiplication(self):
        self.weights = [0] * self.n * self.cols
        self.father = [-1] * self.n * self.cols
        self.depth = [0] * self.n
        stack = [0]
        while stack:
            nex = []
            for i in stack:
                ind = self.point_head[i]
                while ind:
                    j = self.edge_to[ind]
                    if j != self.father[i * self.cols]:
                        self.father[j * self.cols] = i
                        self.weights[j * self.cols] = self.edge_weight[ind]
                        self.depth[j] = self.depth[i] + 1
                        nex.append(j)
                    ind = self.edge_next[ind]
            stack = nex

        for j in range(1, self.cols):
            for i in range(self.n):
                father = self.father[i * self.cols + j - 1]
                if father != -1:
                    self.weights[i * self.cols + j] = max(
                        self.weights[i * self.cols + j - 1],
                        self.weights[father * self.cols + j - 1],
                    )
                    self.father[i * self.cols + j] = self.father[
                        father * self.cols + j - 1
                    ]
        return

    def get_max_weights_between_nodes(self, x: int, y: int):
        assert 0 <= x < self.n
        assert 0 <= y < self.n
        if self.depth[x] < self.depth[y]:
            x, y = y, x
        ans = 0
        while self.depth[x] > self.depth[y]:
            d = self.depth[x] - self.depth[y]
            ans = max(ans, self.weights[x * self.cols + int(math.log2(d))])
            x = self.father[x * self.cols + int(math.log2(d))]
        if x == y:
            return ans
        for k in range(int(math.log2(self.depth[x])), -1, -1):
            if self.father[x * self.cols + k] != self.father[y * self.cols + k]:
                ans = max(ans, self.weights[x * self.cols + k])
                ans = max(ans, self.weights[y * self.cols + k])
                x = self.father[x * self.cols + k]
                y = self.father[y * self.cols + k]
        ans = max(ans, self.weights[x * self.cols])
        ans = max(ans, self.weights[y * self.cols])
        return ans


class UnionFind:
    def __init__(self, n: int) -> None:
        self.root_or_size = [-1] * n
        self.part = n
        self.n = n
        return

    def initialize(self):
        for i in range(self.n):
            self.root_or_size[i] = -1
        self.part = self.n
        return

    def find(self, x):
        y = x
        while self.root_or_size[x] >= 0:
            # range_merge_to_disjoint to the direct root node after query
            x = self.root_or_size[x]
        while y != x:
            self.root_or_size[y], y = x, self.root_or_size[y]
        return x

    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        if self.root_or_size[root_x] < self.root_or_size[root_y]:
            root_x, root_y = root_y, root_x
        self.root_or_size[root_y] += self.root_or_size[root_x]
        self.root_or_size[root_x] = root_y
        self.part -= 1
        return True

    def union_left(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        self.root_or_size[root_x] += self.root_or_size[root_y]
        self.root_or_size[root_y] = root_x
        self.part -= 1
        return True

    def union_right(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        self.root_or_size[root_y] += self.root_or_size[root_x]
        self.root_or_size[root_x] = root_y
        self.part -= 1
        return True

    def union_max(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        if root_x > root_y:
            root_x, root_y = root_y, root_x
        self.root_or_size[root_y] += self.root_or_size[root_x]
        self.root_or_size[root_x] = root_y
        self.part -= 1
        return

    def union_min(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        if root_x < root_y:
            root_x, root_y = root_y, root_x
        self.root_or_size[root_y] += self.root_or_size[root_x]
        self.root_or_size[root_x] = root_y
        self.part -= 1
        return

    def is_connected(self, x, y):
        return self.find(x) == self.find(y)

    def size(self, x):
        return -self.root_or_size[self.find(x)]

    def get_root_part(self):
        # get the nodes list of every root
        part = defaultdict(list)
        n = len(self.root_or_size)
        for i in range(n):
            part[self.find(i)].append(i)
        return part

    def get_root_size(self):
        # get the size of every root
        size = defaultdict(int)
        n = len(self.root_or_size)
        for i in range(n):
            if self.find(i) == i:
                size[i] = -self.root_or_size[i]
        return size


class Solution:
    def __init__(self):
        return

    @staticmethod
    def main(ac=FastIO()):
        """
        url: url of the problem
        tag: algorithm tag
        """
        n, m = ac.read_list_ints()
        weights = []
        fro = []
        to = []
        for x in range(m):
            i, j, w = ac.read_list_ints_minus_one()
            w += 1
            weights.append(w * m + x)
            fro.append(i)
            to.append(j)
        weights.sort()
        uf = UnionFind(n)
        graph = TreeMultiplicationMaxWeights(n)
        cost = 0
        ans = [-1] * m
        use = []
        for val in weights:
            w, x = val // m, val % m
            i, j = fro[x], to[x]
            if uf.union(i, j):
                cost += w
                graph.add_undirected_edge(i, j, w)
                use.append(x)
            if uf.part == 1:
                break
        graph.build_multiplication()
        for x in use:
            ans[x] = cost
        for val in weights:
            w, x = val // m, val % m
            if ans[x] == -1:
                i, j = fro[x], to[x]
                dis = graph.get_max_weights_between_nodes(i, j)
                ans[x] = cost - dis + w
        ac.flatten(ans)
        return


Solution().main()

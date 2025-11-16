# Problem: CF 1810 E - Monsters
# https://codeforces.com/contest/1810/problem/E

"""
Algorithm: Union Find + Sorting
Time Complexity: O(n * log(n) + m * alpha(n)) where alpha(n) is inverse Ackermann function
Space Complexity: O(n + m)

The problem involves determining if we can defeat all monsters in a graph. 
Each monster has a danger value 'a[i]' which means we must defeat at least a[i] other monsters before defeating it.
We can only move through edges, and we can only move to a monster if we've already defeated it or can defeat it now.
This is solved by:
1. Sorting vertices by their danger values
2. For each vertex in sorted order, we check if it's reachable from a previously defeated monster
3. We use UnionFind to track connected components and whether we can reach each component
4. We mark if a vertex is reachable based on whether its components have sufficient defeated monsters

The key insight is that monsters can be defeated in order of their danger values, and we use UnionFind to group connected vertices.
"""

from sys import stdin

inf = 1 << 32


class FastIO:
    def __init__(self):
        self.random_seed = 0
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

    @staticmethod
    def st(x):
        return print(x)

    @staticmethod
    def lst(x):
        return print(*x)

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


class UnionFind:
    def __init__(self, n: int) -> None:
        self.root_or_size = [-1] * n
        self.part = n
        return

    def find(self, x):
        y = x
        while self.root_or_size[x] >= 0:

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

    def get_node_size(self, x):
        return -self.root_or_size[self.find(x)]


class Solution:
    def __init__(self):
        return

    @staticmethod
    def main(ac=FastIO()):
        for _ in range(ac.read_int()):
            n, m = ac.read_list_ints()
            nums = ac.read_list_ints()
            # Create a unique value for each node combining danger with index
            nums = [num * n + i for i, num in enumerate(nums)]

            edge = [[] for _ in range(n)]
            for _ in range(m):
                u, v = ac.read_list_ints_minus_one()
                # Ensure u has greater or equal danger value than v for processing
                if nums[u] < nums[v]:
                    u, v = v, u
                edge[u].append(v)

            reach = [0] * n
            uf = UnionFind(n)
            # Sort nodes by their danger values (and index)
            nums.sort()
            for val in nums:
                num, i = val // n, val % n
                # If danger level is 0, it's reachable
                if not num:
                    reach[i] = 1
                # Check each neighbor for connection
                for j in edge[i]:
                    # If neighbor was visited and we have sufficient defeated monsters, mark current as reachable
                    if reach[uf.find(j)] and num <= uf.get_node_size(j):
                        reach[i] = 1
                    # Union the current and neighbor vertices
                    uf.union_left(i, j)
            # Check if all nodes are in one component and the initial node is reachable
            ac.st("YES" if uf.part == 1 and reach[uf.find(0)] else "NO")
        return


Solution().main()


# https://github.com/VaHiX/CodeForces/
# Contest 1413, Problem C: Perform Easily
# URL: https://codeforces.com/contest/1413/problem/C

from math import inf
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


class Solution:
    def __init__(self):
        return

    @staticmethod
    def main(ac=FastIO()):
        """
        url: url of the problem
        tag: algorithm tag
        """
        a = ac.read_list_ints()
        n = ac.read_int()
        nums = ac.read_list_ints()
        lst = []
        for i in range(n):
            for num in a:
                lst.append((nums[i] - num) * n + i)
        cnt = [0] * n
        lst.sort()
        ans = inf
        cur = 0
        j = 0
        for i in range(6 * n):
            while j < 6 * n and cur < n:

                cnt[lst[j] % n] += 1
                if cnt[lst[j] % n] == 1:
                    cur += 1
                j += 1
            if cur == n:
                ans = min(ans, lst[j - 1] // n - lst[i] // n)

            cnt[lst[i] % n] -= 1
            if cnt[lst[i] % n] == 0:
                cur -= 1
        ac.st(ans)
        return


Solution().main()

# Problem: CF 1796 D - Maximum Subarray
# https://codeforces.com/contest/1796/problem/D

from collections import deque
from sys import stdin


class FastIO:
    def __init__(self):
        self.random_seed = 0
        self.flush = False
        self.inf = 1 << 32
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
        url: https://codeforces.com/contest/1932/problem/D
        tag: sliding window, prefix sum, two pointers
        Time Complexity: O(n) for each test case
        Space Complexity: O(n) for each test case
        """
        for _ in range(ac.read_int()):
            n, k, x = ac.read_list_ints()
            if x < 0:
                x = -x
                k = n - k
            nums = ac.read_list_ints()
            nums = [num - x for num in nums]

            ans = pre = 0
            pre_min = [0] * (n + 1)
            pre_min[0] = 0
            for i in range(n):
                pre += nums[i]
                # If we've processed at least k elements, compute potential maximum
                if i >= k:
                    ans = max(ans, pre - pre_min[i - k] + 2 * k * x)
                pre_min[i + 1] = min(pre_min[i], pre)

            stack = deque([(-1, 0)])  # (index, prefix_sum)
            pre = 0
            for i in range(n):
                pre += nums[i] + 2 * x  # Add 2*x to account for the increment/decrement effect
                # Maintain sliding window size <= k
                while stack and i - stack[0][0] > k:
                    stack.popleft()
                # Maintain increasing stack (pop elements with larger prefix sums)
                while stack and stack[-1][1] > pre:
                    stack.pop()
                stack.append((i, pre))
                # Compute maximum subarray sum for current window
                ans = max(ans, pre - stack[0][1])
            ac.st(ans)
        return


Solution().main()


# https://github.com/VaHiX/CodeForces/
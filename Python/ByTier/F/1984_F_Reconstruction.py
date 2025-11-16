# Problem: CF 1984 F - Reconstruction
# https://codeforces.com/contest/1984/problem/F

"""
Algorithm: Dynamic Programming with State Compression
Approach:
1. For each test case, we process the string s and array b to determine valid assignments of P/S to ? characters.
2. We use dynamic programming where dp[i][0] represents the number of ways to assign P/S such that the current state satisfies the constraints, and dp[i][1] represents the same for S.

Time Complexity: O(n^2 * m) where n is the length of the string and m is the maximum absolute value of elements in array a.
Space Complexity: O(n) for storing prefix sums and DP states.

The algorithm works by:
- Iterating over all possible combinations of P/S for ? characters.
- Maintaining a dynamic programming state based on constraints derived from prefix and suffix sums.
- Checking feasibility of values at each step.
"""

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
        url: url of the problem
        tag: algorithm tag
        """
        mod = 998244353
        for _ in range(ac.read_int()):
            n, m = ac.read_list_ints()
            s = "P" + ac.read_str() + "S"  # Add sentinel characters
            nums = [0] + ac.read_list_ints() + [0]  # Add sentinel values
            ans = 0
            n += 2
            pre = set()
            for i in range(n - 1):
                cur = nums[i] + nums[i + 1]  # Compute combined value
                if cur in pre:
                    continue
                pre.add(cur)
                dp = [0, 0]
                dp[0] = 1  # Initialize base state
                for j in range(1, n):
                    flag = [0, 0]  # Tracks which characters (P/S) are valid
                    ndp = [0, 0]
                    if s[j] == "P":
                        flag[0] = 1
                    elif s[j] == "S":
                        flag[1] = 1
                    else:
                        flag[0] = flag[1] = 1  # ? can be both
                    # Check if current value assignment is valid
                    if abs(nums[j] - nums[j - 1]) <= m:
                        for k in range(2):
                            if flag[k]:
                                ndp[k] += dp[k]
                    # Transition from previous P transition
                    if dp[0] and flag[1] and cur == nums[j - 1] + nums[j]:
                        ndp[1] += dp[0]
                    # Transition from previous S transition
                    if dp[1] and flag[0]:
                        xx = nums[j] + nums[j - 1] - cur
                        large = max(abs(xx // 2), abs(xx - xx // 2))
                        if large <= m:
                            ndp[0] += dp[1]
                    dp = [x % mod for x in ndp]  # Update DP state
                ans += dp[1]  # Count valid ending in S
                ans %= mod
            ac.st(ans)
        return


Solution().main()


# https://github.com/VaHiX/CodeForces/
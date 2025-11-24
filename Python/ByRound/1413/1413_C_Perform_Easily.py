# Problem: CF 1413 C - Perform Easily
# https://codeforces.com/contest/1413/problem/C

# ====================================================================================================
# Problem: C. Perform Easily
# Algorithms/Techniques: Two Pointers, Sorting
# Time Complexity: O(n log n) where n is the number of notes
# Space Complexity: O(n) for storing the list of (fret_value * n + string_index)
# ====================================================================================================

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
        a = ac.read_list_ints()  # Read 6 string base values
        n = ac.read_int()  # Number of notes to play
        nums = ac.read_list_ints()  # The sequence of notes

        # Generate all possible (note - base_value) * n + string_index combinations for each note and string
        lst = []
        for i in range(n):
            for num in a:
                lst.append((nums[i] - num) * n + i)  # Store frets with encoded info

        # We will use sliding window approach, so we need to sort the list first
        cnt = [0] * n  # Counter to track how many times each string is used in current window
        lst.sort()  # Sort for two-pointer technique
        
        ans = inf
        cur = 0  # Number of unique strings currently in the window
        j = 0  # Right pointer for sliding window

        # Sliding window over extended array of size 6*n (each note can use 6 strings)
        for i in range(6 * n):
            # Expand window until we have used all 6 strings
            while j < 6 * n and cur < n:
                cnt[lst[j] % n] += 1  # Increment count for string index at j
                if cnt[lst[j] % n] == 1:  # If this is first time using this string
                    cur += 1  # Increase unique string counter
                j += 1

            # Once we have used all strings, calculate the min difference
            if cur == n:
                ans = min(ans, lst[j - 1] // n - lst[i] // n)  # Calculate difference between max and min frets

            # Shrink window from left by removing string index at position i
            cnt[lst[i] % n] -= 1
            if cnt[lst[i] % n] == 0:  # If no longer using this string
                cur -= 1  # Reduce unique string count
        ac.st(ans)
        return


Solution().main()


# https://github.com/VaHiX/codeForces/
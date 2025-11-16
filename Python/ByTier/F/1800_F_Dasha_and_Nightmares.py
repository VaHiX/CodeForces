# Problem: CF 1800 F - Dasha and Nightmares
# https://codeforces.com/contest/1800/problem/F

"""
Algorithm: Bitmask + Hash Map
Time Complexity: O(n * L) where n is number of words and L is average word length
Space Complexity: O(2^26) = O(1) since 2^26 is a constant

The solution uses bitmasks to represent the set of characters in each word.
For each word, we maintain two masks:
- a: bitmask of characters with odd occurrences (XOR of all characters)
- b: bitmask of all characters present in the word (OR of all characters)

We then check for valid pairs (i, j) where:
1. Length of s_i + s_j is odd
2. Number of distinct characters is exactly 25
3. Each character appears an odd number of times in the concatenated string

This translates to finding pairs where:
- a_i ^ a_j = mask with exactly one bit set (i.e., exactly one character contributes an odd count to the final string)
- The number of characters in s_i + s_j is odd, so one of s_i or s_j should have an odd number of total characters.

We use a hash map to store frequency counts of each mask and precompute which masks differ in exactly one bit.
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


class Solution:
    def __init__(self):
        return

    @staticmethod
    def main(ac=FastIO()):
        n = ac.read_int()
        ans = 0
        mask = (1 << 26) - 1
        # Precompute masks for each possible single character difference
        state = [mask ^ (1 << j) for j in range(26)]
        dct = dict()
        for _ in range(n):
            a = b = 0
            for w in ac.read_str():
                i = ord(w) - ord("a")
                a ^= 1 << i  # XOR to track odd occurrences
                b |= 1 << i  # OR to track all characters present
            if a not in dct:
                dct[a] = [0] * 26  # Initialize frequency count for each character
            for j in range(26):
                # If character j is not in current word, we look for previous words
                # where combining with current word gives total 25 chars with odd counts
                if not b & (1 << j):
                    if a ^ state[j] in dct:
                        # Add count of matching previous entries, that result in 25 unique chars
                        ans += dct[a ^ state[j]][j]
                    # Increment the count of this character index in current a
                    dct[a][j] += 1
        ac.st(ans)
        return


Solution().main()


# https://github.com/VaHiX/CodeForces/
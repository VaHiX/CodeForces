# Problem: CF 1822 G2 - Magic Triples (Hard Version)
# https://codeforces.com/contest/1822/problem/G2

"""
Algorithm: Magic Triples (Hard Version)
Purpose: Count the number of magic triples (i,j,k) such that a[i]*b = a[j] and a[j]*b = a[k] for some positive integer b.
Techniques: 
- Sorting and counting frequencies of elements.
- Using square factorization to find valid b values.
- Applying combinatorics to count valid combinations.

Time Complexity: O(n * sqrt(max_a) * log(max_a)) where n is the length of input array and max_a is the maximum element.
Space Complexity: O(n + sqrt(max_a)) for storing frequency map and prime sieve.

The solution works by:
1. Sorting the array and counting frequencies of each element.
2. For each unique element, we compute all square factors.
3. For each square factor f, we check if num//f and num//sqrt(f) exist in the frequency map.
4. Using combinatorics to count valid combinations.
"""

import math
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
    def st(x, flush=False):
        return print(x, flush=flush)

    @staticmethod
    def lst(x, flush=False):
        return print(*x, flush=flush)

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


class PrimeSieve:
    def __init__(self):
        return

    @staticmethod
    def eratosthenes_sieve(n):
        """eratosthenes screening method returns prime numbers less than or equal to n"""
        primes = [True] * (n + 1)
        p = 2
        while p * p <= n:
            if primes[p]:
                for i in range(p * 2, n + 1, p):
                    primes[i] = False
            p += 1
        primes = [element for element in range(2, n + 1) if primes[element]]
        return primes


class NumFactor:
    def __init__(self):
        return

    @staticmethod
    def get_all_factor(num):
        """Obtain all factors of an integer, including 1 and itself"""
        assert num >= 1
        factor = set()
        for i in range(1, int(math.sqrt(num)) + 1):
            if num % i == 0:
                factor.add(i)
                factor.add(num // i)
        return sorted(list(factor))

    @staticmethod
    def get_all_factor_square(num):
        """Obtain all square factors of an integer, including 1"""
        lst = []
        for p in primes:
            cnt = 0
            while num % p == 0:
                num //= p
                cnt += 1
            if cnt > 1:
                lst.append((p, cnt // 2))
        if int(num**0.5) ** 2 == num:
            lst.append((int(num**0.5), 1))
        pre = {1}
        for p, c in lst:
            for num in list(pre):
                for i in range(1, c + 1):
                    pre.add(num * p**i)
        return sorted([x * x for x in pre])


ps = PrimeSieve()
primes = ps.eratosthenes_sieve(1000)


class Solution:
    def __init__(self):
        return

    @staticmethod
    def main(ac=FastIO()):
        """
        url: https://codeforces.com/problemset/problem/1208/D
        tag: segment_tree|reverse_thinking|construction|point_set|range_sum_bisect_left
        """
        ps = PrimeSieve()
        ps.eratosthenes_sieve(1000)
        nf = NumFactor()
        for _ in range(ac.read_int()):
            ac.read_int()
            nums = ac.read_list_ints()
            nums.sort()
            cnt = dict()
            for num in nums:
                cnt[num] = cnt.get(num, 0) + 1
            ans = 0
            for num in sorted(cnt):
                if cnt[num] > 2:
                    # Case where all three elements are same
                    ans += cnt[num] * (cnt[num] - 1) * (cnt[num] - 2)
                square = nf.get_all_factor_square(num)
                for f in square:
                    if f > 1:
                        b = int(f**0.5)
                        # Count combinations using the derived relationship
                        ans += cnt[num] * cnt.get(num // b, 0) * cnt.get(num // f, 0)
            ac.st(ans)
        return


Solution().main()


# https://github.com/VaHiX/CodeForces/
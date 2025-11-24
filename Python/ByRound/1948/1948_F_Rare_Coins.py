# Problem: CF 1948 F - Rare Coins
# https://codeforces.com/contest/1948/problem/F

"""
Algorithm: 
- Use prefix sums for gold and silver coins to quickly calculate totals for any range.
- For each query, compute the difference in expected values between the selected range and the rest.
- Use combinatorics to compute the probability that the sum of silver coins in the selected range is greater than the sum in the rest.

Time Complexity: O(n + q + max_sum) where max_sum is the total number of silver coins
Space Complexity: O(n + max_sum) for prefix sums and combinatorial array

Techniques:
- Prefix sums for efficient range queries
- Modular arithmetic with Fermat's little theorem for modular inverse
- Combinatorial mathematics for probability calculation
"""

standard_input, packages, output_together = 1, 1, 0
dfs, hashing, read_from_file = 0, 0, 0
de = 1

if 1:

    if standard_input:
        import os
        import sys

        input = lambda: sys.stdin.readline().strip()

        import math

        inf = math.inf

        def I():
            return input()

        def II():
            return int(input())

        def MII():
            return map(int, input().split())

        def LI():
            return list(input().split())

        def LII():
            return list(map(int, input().split()))

        def LFI():
            return list(map(float, input().split()))

        def GMI():
            return map(lambda x: int(x) - 1, input().split())

        def LGMI():
            return list(map(lambda x: int(x) - 1, input().split()))

    if packages:
        import os
        import random
        from io import BytesIO, IOBase
        from itertools import accumulate

        BUFSIZE = 4096

    if output_together:

        class FastIO(IOBase):
            newlines = 0

            def __init__(self, file):
                self._fd = file.fileno()
                self.buffer = BytesIO()
                self.writable = "x" in file.mode or "r" not in file.mode
                self.write = self.buffer.write if self.writable else None

            def read(self):
                while True:
                    b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                    if not b:
                        break
                    ptr = self.buffer.tell()
                    self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
                self.newlines = 0
                return self.buffer.read()

            def readline(self):
                while self.newlines == 0:
                    b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                    self.newlines = b.count(b"\n") + (not b)
                    ptr = self.buffer.tell()
                    self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
                self.newlines -= 1
                return self.buffer.readline()

            def flush(self):
                if self.writable:
                    os.write(self._fd, self.buffer.getvalue())
                    self.buffer.truncate(0), self.buffer.seek(0)

        class IOWrapper(IOBase):
            def __init__(self, file):
                self.buffer = FastIO(file)
                self.flush = self.buffer.flush
                self.writable = self.buffer.writable
                self.write = lambda s: self.buffer.write(s.encode("ascii"))
                self.read = lambda: self.buffer.read().decode("ascii")
                self.readline = lambda: self.buffer.readline().decode("ascii")

        sys.stdout = IOWrapper(sys.stdout)

    if dfs:
        from types import GeneratorType

        def bootstrap(f, stack=[]):
            def wrappedfunc(*args, **kwargs):
                if stack:
                    return f(*args, **kwargs)
                else:
                    to = f(*args, **kwargs)
                    while True:
                        if type(to) is GeneratorType:
                            stack.append(to)
                            to = next(to)
                        else:
                            stack.pop()
                            if not stack:
                                break
                            to = stack[-1].send(to)
                    return to

            return wrappedfunc

    if hashing:
        RANDOM = random.getrandbits(20)

        class Wrapper(int):
            def __init__(self, x):
                int.__init__(x)

            def __hash__(self):
                return super(Wrapper, self).__hash__() ^ RANDOM

    if read_from_file:
        file = open("input.txt", "r").readline().strip()[1:-1]
        fin = open(file, "r")
        input = lambda: fin.readline().strip()
        output_file = open("output.txt", "w")

        def fprint(*args, **kwargs):
            print(*args, **kwargs, file=output_file)

    if de:

        def debug(*args, **kwargs):
            print("\033[92m", end="")
            print(*args, **kwargs)
            print("\033[0m", end="")


class Factorial:
    def __init__(self, N, mod) -> None:
        N += 1
        self.mod = mod
        self.f = [1 for _ in range(N)]
        self.g = [1 for _ in range(N)]
        for i in range(1, N):
            self.f[i] = self.f[i - 1] * i % self.mod
        self.g[-1] = pow(self.f[-1], mod - 2, mod)
        for i in range(N - 2, -1, -1):
            self.g[i] = self.g[i + 1] * (i + 1) % self.mod

    def fac(self, n):
        return self.f[n]

    def fac_inv(self, n):
        return self.g[n]

    def combi(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[m] % self.mod * self.g[n - m] % self.mod

    def permu(self, n, m):
        if n < m or m < 0 or n < 0:
            return 0
        return self.f[n] * self.g[n - m] % self.mod

    def catalan(self, n):
        return (self.combi(2 * n, n) - self.combi(2 * n, n - 1)) % self.mod

    def inv(self, n):
        return self.f[n - 1] * self.g[n] % self.mod


mod = 998244353
n, q = MII()
nums1 = list(accumulate(MII(), initial=0))  # Prefix sum for gold coins
nums2 = list(accumulate(MII(), initial=0))  # Prefix sum for silver coins

# Precompute reverse probability 1/2^total_silver_coins
rev = pow((mod + 1) // 2, nums2[-1], mod)

# Precompute all combinations
fact = Factorial(nums2[-1], mod)
combs_acc = [fact.combi(nums2[-1], i) for i in range(nums2[-1] + 1)]
# Compute prefix sum of combinations
for i in range(nums2[-1]):
    combs_acc[i + 1] += combs_acc[i]
    combs_acc[i + 1] %= mod
# Multiply by reverse probability
for i in range(nums2[-1] + 1):
    combs_acc[i] *= rev
    combs_acc[i] %= mod

ans = []
for _ in range(q):
    l, r = MII()
    # Get gold and silver coin counts in the range [l, r]
    gold_in, silver_in = nums1[r] - nums1[l - 1], nums2[r] - nums2[l - 1]
    # Get gold and silver coin counts outside the range
    gold_out = nums1[-1] - gold_in
    # Calculate the difference in expected value
    v = silver_in + gold_in - gold_out - 1
    # If difference is negative, probability is 0
    if v < 0:
        ans.append(0)
    # If difference is larger than possible, probability is 1
    elif v > nums2[-1]:
        ans.append(1)
    # Otherwise use precomputed prefix sum of combinations
    else:
        ans.append(combs_acc[v])

print(" ".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/
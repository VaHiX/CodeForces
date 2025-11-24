# Problem: CF 1893 B - Neutral Tonality
# https://codeforces.com/contest/1893/problem/B

"""
Algorithm: Neutral Tonality
Purpose: Minimize the length of the longest increasing subsequence (LIS) when inserting elements from array b into array a.
Approach:
1. Sort array b in descending order.
2. Use a two-pointer technique to merge arrays a and b, always choosing the smaller element to maintain a lower LIS.
   - This greedy approach helps avoid increasing the LIS by inserting smaller elements before larger ones.
3. The result is the final merged array that minimizes LIS.

Time Complexity: O(n + m + m*log(m)) where n and m are lengths of arrays a and b respectively.
Space Complexity: O(n + m) for storing the result array.

The idea is to interleave elements in such a way that we avoid creating long increasing subsequences.
"""

import os
import sys
from io import BytesIO, IOBase

BUFSIZE = 8192


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


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def primes(n):
    ans = []
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            ans.append(i)
            while n % i == 0:
                n //= i
        if n == 1:
            break
    if n != 1:
        ans.append(n)
    return ans


def countSetBits(n):
    ans = 0
    while n:
        ans += n % 2
        n //= 2
    return ans


def factors(n):
    ans = []
    rev = []
    for i in range(1, int(n**0.5) + 1):
        if n % i == 0:
            if i * i == n:
                ans.append(i)
                continue
            ans.append(i)
            rev.append(n // i)

    return ans + rev[::-1]


def factorial(x, mod):
    if x == 1 or x == 0 or x >= mod:
        return 1
    ans = 1
    for i in range(2, x + 1):
        ans *= i
        if ans % mod == 0:
            return 0
        ans %= mod
    return ans
    return ((x % mod) * factorial(x - 1, mod)) % mod


def primeFactorsRepeated(number):
    prime_factors = []
    i = 2
    while i * i <= number and number != 1:
        while number % i == 0:

            prime_factors.append(i)
            number //= i
        i += 1
    if number != 1:
        prime_factors.append(number)
    return prime_factors


def primeFactors(number):
    prime_factors = set()
    i = 2
    while i * i <= number and number != 1:
        while number % i == 0:

            prime_factors.add(i)
            number //= i
        i += 1
    if number != 1:
        prime_factors.add(number)
    return list(prime_factors)


def primes(num):
    prime = [True for i in range(num + 1)]
    p = 2
    while p * p <= num:
        if prime[p] == True:
            for i in range(p * p, num + 1, p):
                prime[i] = False
        p += 1


def ncr(n, r, p):
    num = den = 1
    for i in range(r):
        num = (num * (n - i)) % p
        den = (den * (i + 1)) % p
    return (num * pow(den, p - 2, p)) % p


for _ in range(int(input())):
    [n, m] = list(map(int, input().split()))
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    b.sort(reverse=True)  # Sort b in descending order to control insertion strategy
    ans = []
    i, j = 0, 0
    # Two-pointer merge process
    while i < n or j < m:
        if i == n:
            # If a is exhausted, take remaining elements from b
            ans.append(b[j])
            j += 1
        elif j == m:
            # If b is exhausted, take remaining elements from a
            ans.append(a[i])
            i += 1
        else:
            # Compare elements to decide which to insert next
            # Insert smaller element first to keep LIS low
            if a[i] <= b[j]:
                ans.append(b[j])
                j += 1
            else:
                ans.append(a[i])
                i += 1
    print(" ".join([str(i) for i in ans]))


# https://github.com/VaHiX/CodeForces/
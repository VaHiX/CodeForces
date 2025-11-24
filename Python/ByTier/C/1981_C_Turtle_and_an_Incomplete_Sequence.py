# Problem: CF 1981 C - Turtle and an Incomplete Sequence
# https://codeforces.com/contest/1981/problem/C

"""
Problem: C. Turtle and an Incomplete Sequence
Algorithm: Greedy approach with forward/backward propagation
Time Complexity: O(n) for each test case, where n is the length of the sequence
Space Complexity: O(n) for storing the sequence and auxiliary variables

The problem requires us to reconstruct a sequence of positive integers from a partially
given sequence where some elements are -1 (missing). For every consecutive pair of elements
in the original sequence, one of the following must hold:
- a[i] = floor(a[i+1] / 2) or
- a[i+1] = floor(a[i] / 2)

We use a greedy strategy:
1. Find the first non-missing element and back-propagate values to the left
2. For subsequent non-missing elements, resolve the gap using either forward or backward propagation
3. Fill missing elements based on the constraints of the sequence
4. Validate that the final sequence satisfies all constraints
"""

import math
import sys

input = sys.stdin.readline


def print(*args, **kwargs):
    sep = kwargs.get("sep", " ")
    end = kwargs.get("end", "\n")
    file = kwargs.get("file", sys.stdout)
    flush = kwargs.get("flush", False)
    output = sep.join(map(str, args)) + end
    file.write(output)
    if flush:
        file.flush()


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


import math
from collections import Counter


def readIntLine():
    return [int(char) for char in input().split()]


def readCharLine():
    return [char for char in input().split()]


def modmul(a, b, mod):
    a %= mod
    b %= mod
    return (a * b) % mod


def modadd(a, b, mod):
    a %= mod
    b %= mod
    return (a + b) % mod


def modsub(a, b, mod):
    a %= mod
    b %= mod
    return (a - b + mod) % mod


def modInverse(A, M):
    for X in range(1, M):
        if ((A % M) * (X % M)) % M == 1:
            return X
    return -1


def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


def is_coprime(a, b):
    return gcd(a, b) == 1


def expo(a, n, mod):
    res = 1
    while n:
        if n & 1:
            res = modmul(res, a, mod)
            n -= 1
        else:
            a = modmul(a, a, mod)
            n >>= 1
    return res


def get_mex(arr, N):
    arr = sorted(arr)
    mex = 0
    for idx in range(N):
        if arr[idx] == mex:
            mex += 1
    return mex


def primeFactors(n):
    res = Counter()
    while n % 2 == 0:
        res[2] += 1
        n = n / 2
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        while n % i == 0:
            res[i] += 1
            n //= i
    if n > 2:
        res[n] += 1
    return res


def printDivisors(n):
    i = 1
    divs = []
    while i <= math.sqrt(n):
        if n % i == 0:
            if n / i == i:
                divs.append(i)
            else:
                divs.append(i)
                divs.append(n // i)
        i = i + 1
    return sorted(divs)


def LcmOfArray(arr, idx):

    if idx == len(arr) - 1:
        return arr[idx]
    a = arr[idx]
    b = LcmOfArray(arr, idx + 1)
    return int(a * b / math.gcd(a, b))


UF = {}


def find(x):
    if x not in UF:
        UF[x] = x
    if UF[x] != x:
        UF[x] = find(UF[x])
    return UF[x]


def union(x, y):
    rX, rY = find(x), find(y)
    if rX < rY:
        UF[rY] = rX
    else:
        UF[rX] = rY


def solve(idx):
    n = int(input())

    A = readIntLine()

    l = -1

    for r, a in enumerate(A):
        rr = r
        if a == -1:
            continue

        if l == -1:
            # First non-missing element, fill backward
            for i in range(r - 1, -1, -1):
                if A[i + 1] == 1:
                    A[i] = A[i + 1] * 2
                else:
                    A[i] = A[i + 1] // 2
            l = rr

        else:
            # Fill intermediate gaps between l and r
            while l + 1 != r:
                a, b = A[l], A[r]
                if a == 1 and b == 1:
                    A[l + 1] = 2
                    l += 1
                else:
                    if a >= b:
                        A[l + 1] = a // 2
                        l += 1
                    else:
                        A[r - 1] = b // 2
                        r -= 1
            l = rr

    # If no elements were processed
    if l == -1:
        for i in range(n):
            if i % 2 == 0:
                A[i] = 1
            else:
                A[i] = 2
        print(*A)
        return

    # Propagate from last found element to end
    if l != n - 1:
        for i in range(l, n - 1):
            if A[i] == 1:
                A[i + 1] = A[i] * 2
            else:
                A[i + 1] = A[i] // 2

    # Validate the sequence
    for i, a in enumerate(A[:-1]):
        if (a == A[i + 1] // 2) or (A[i + 1] == a // 2):
            continue
        else:
            print(-1)
            return

    print(*A)


for i in range(int(input())):
    solve(i)


# https://github.com/VaHiX/CodeForces/
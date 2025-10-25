# Problem: CF 1917 B - Erase First or Second Letter
# https://codeforces.com/contest/1917/problem/B

"""
Problem: Erase First or Second Letter
Algorithm: Dynamic Programming / Set-based Approach
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) since there are at most 26 lowercase letters

The key insight is that each unique character in the string contributes to the count of distinct strings.
When we process the string from left to right, for each character we encounter:
- If it's a new character, it can form new distinct strings by being appended to all previously formed strings
- We maintain a set of unique characters seen so far
- For each new character, the number of new distinct strings we can form is equal to the number of unique characters seen so far
"""

import sys
from sys import stdin

sys.setrecursionlimit(300009)
input = stdin.readline
mod = 10**9 + 7
eps = 10**-9


def inp():
    return input().strip()


def linp(type=int):
    return list(map(type, inp().split()))


def minp(type=int):
    return map(type, inp().split())


def tinp(type=int):
    return type(inp())


def __gcd(a, b):
    return a if b == 0 else __gcd(b, a % b)


def __lcm(a, b):
    return a * b / __gcd(a, b)


def __fact(n):
    return 1 if n == 1 else n * __fact(n - 1)


def __mex(a):
    mex = 0
    a.sort()
    for x in a:
        if x <= mex:
            mex += 1
        else:
            break
    return mex


def __dist(x1, y1, x2, y2):
    return (x1 - x2) ** 2 + (y1 - y2) ** 2


def __getprimes(n):
    isprime = [True for i in range(n + 1)]
    primes = []
    for i in range(2, n + 1):
        if isprime[i]:
            for j in range(i * i, n + 1, i):
                isprime[j] = False
    for i in range(2, n + 1):
        if isprime[i]:
            primes.append(i)
    return primes


def __getdividers(n):
    i = 1
    ret = []
    while i * i <= n:
        if n % i == 0:
            ret.append(i)
            if i * i != n:
                ret.append(n // i)
        i += 1
    ret.sort()
    return ret


def __modInverse(a, m):
    m0 = m
    y = 0
    x = 1
    if m == 1:
        return 0
    while a > 1:
        q = a // m
        t = m
        m = a % m
        a = t
        t = y
        y = x - q * y
        x = t
    if x < 0:
        x = x + m0
    return x


def __isprime(n):
    if n < 2:
        return False
    i = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += 1
    return True


def __cntprimediv(n):
    ret = 0
    x = n
    i = 2
    while i * i <= x:
        while n % i == 0:
            n //= i
            ret += 1
        i += 1
    if n > 1:
        ret += 1
    return ret


def __primefactors(n):
    ret = []
    x = n
    i = 2
    while i * i <= x:
        while n % i == 0:
            ret.append(i)
            n //= i
        i += 1
    if n > 1:
        ret.append(n)
    return ret


def __sumdigit(n):
    ret = 0
    while n > 0:
        ret += n % 10
        n //= 10
    return ret


def __zfunc(s):
    n = len(s)
    z = [0 for i in range(n)]
    l = 0
    r = 0
    for i in range(1, n):
        if r >= i:
            z[i] = min(z[i - l], r - i + 1)
        while z[i] + i < n and s[z[i]] == s[z[i] + i]:
            z[i] += 1
        if i + z[i] - 1 > r:
            l = i
            r = i + z[i] - 1
    return z


def __to(n, x):
    ret = ""
    while n > 0:
        q = n % x
        if q < 10:
            ret += str(q)
        else:
            ret += chr(q - 10 + ord("a"))
        n //= x
    return ret[::-1]


def solve(t_id):
    tinp() # Read length (not used)
    s = inp() # Read string
    d = {} # Dictionary to store unique characters seen
    ans = 0 # Total count of distinct strings
    for c in s:
        d[c] = 1 # Add character to set
        ans += len(d) # Add count of unique characters to answer
    print(ans)


tc = 1
tc = int(input())
for i in range(tc):
    solve(i + 1)


# https://github.com/VaHiX/CodeForces/
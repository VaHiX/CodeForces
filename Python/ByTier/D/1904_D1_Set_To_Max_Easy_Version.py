# Problem: CF 1904 D1 - Set To Max (Easy Version)
# https://codeforces.com/contest/1904/problem/D1

"""
Algorithm: Greedy approach with segment processing
Time Complexity: O(n^2) in worst case due to nested loops for finding valid segments
Space Complexity: O(n) for storing indices and auxiliary arrays

This problem asks whether we can transform array 'a' into array 'b' using operations 
that set a segment to the maximum value in that segment. The approach is to process 
elements in order of increasing values in 'b', and for each element, check if we can 
make 'a' match 'b' by applying operations on appropriate segments.
"""

from sys import stdin

input = stdin.readline
mod = 10**9 + 7
eps = 10**-9


def linp(type=int):
    return list(map(type, input().strip().split()))


def minp(type=int):
    return map(type, input().strip().split())


def tinp(type=int):
    return type(input().strip())


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
    n = tinp()
    a = linp()
    b = linp()
    ok = True
    # Create a list of indices for each value in b
    ind = [[] for i in range(n + 1)]
    for i in range(n):
        ind[b[i]].append(i)
    # Process elements in increasing order of value in b
    for i in range(1, n + 1):
        for id in ind[i]:
            # If already equal, continue
            if a[id] == b[id]:
                continue
            # If a[id] > b[id], impossible to make it equal
            if a[id] > b[id]:
                ok = False
                break
            # Look for a previous position where a[j] == b[id] 
            # that can form a valid segment ending at current position
            prev = -1
            ii = id - 1
            while ii >= 0 and a[ii] <= b[ii] and a[ii] <= b[id] and b[id] <= b[ii]:
                if a[ii] == b[id]:
                    prev = ii
                    break
                ii -= 1
            if prev > -1:
                # Update segment [prev, id] to b[id]
                for j in range(prev, id + 1):
                    a[j] = b[id]
            else:
                # Look for a next position where a[j] == b[id]
                # that can form a valid segment starting at current position
                next = -1
                ii = id + 1
                while ii < n and a[ii] <= b[ii] and a[ii] <= b[id] and b[id] <= b[ii]:
                    if a[ii] == b[id]:
                        next = ii
                        break
                    ii += 1
                if next > -1:
                    # Update segment [id, next) to b[id]
                    for j in range(id, next):
                        a[j] = b[id]
                else:
                    # No valid segment found, impossible
                    ok = False
                    break
        if not ok:
            break
    # Final check if a equals b
    for i in range(n):
        if a[i] != b[i]:
            ok = False
    print("YES" if ok else "NO")


tc = 1
tc = int(input())
for i in range(tc):
    solve(i + 1)


# https://github.com/VaHiX/CodeForces/
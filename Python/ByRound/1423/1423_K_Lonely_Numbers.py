# Problem: CF 1423 K - Lonely Numbers
# https://codeforces.com/contest/1423/problem/K

"""
Algorithm: Number Theory + Sieve of Eratosthenes + Prefix Sum
Time Complexity: O(n log log n + q) where n is max element in input and q is number of test cases
Space Complexity: O(n) for storing sieve and prefix sum arrays

The problem asks to count "lonely" numbers from 1 to n, where a number is lonely if it has no friends.
Two numbers are friends if gcd(a,b), a/gcd(a,b), b/gcd(a,b) can form a triangle.
This reduces to checking if a and b are friends by checking triangular inequality.
Key insight:
- If a and b are friends, then gcd(a,b) = g, and the three sides are g, a/g, b/g.
- For triangle inequality to hold, a/g + b/g > g which implies a + b > g^2.
- Also, a/g + g > b/g -> a + g^2 > b, similarly b + g^2 > a.
- A number a is lonely if no b in [1,n] satisfies these conditions.
- A more efficient approach is to precompute for each number whether it's lonely.
- Using sieve technique: mark all composite numbers, only primes and their squares contribute to loneliness.
- For each prime p, we mark all multiples as not lonely.
- For square of prime p^2, we mark it as not lonely.
- We can use prefix sum to efficiently compute count of lonely numbers up to n.
"""

import sys
from random import randint
from types import GeneratorType

RANDOM = randint(1, 10**10)


class op(int):
    def __init__(self, x):
        int.__init__(x)

    def __hash__(self):
        return super(op, self).__hash__() ^ RANDOM


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


inp = lambda: sys.stdin.buffer.readline().decode().strip()
out = sys.stdout.write


def S():
    return inp()


def I():
    return int(inp())


def F():
    return float(inp())


def MI():
    return map(int, inp().split())


def MF():
    return map(float, inp().split())


def MS():
    return inp().split()


def LS():
    return list(inp().split())


def LI():
    return list(map(int, inp().split()))


def LF():
    return list(map(float, inp().split()))


def Query(i, j):
    print3("?", i, j)
    sys.stdout.flush()
    qi = I()
    return qi


def print1(x):
    return out(str(x) + "\n")


def print2(x, y):
    return out(str(x) + " " + str(y) + "\n")


def print3(x, y, z):
    return out(str(x) + " " + str(y) + " " + str(z) + "\n")


def print_arr(arr):
    for num in arr:
        out(str(num) + " ")
    out(str("\n"))


MAX = 10**6 + 10
is_prime = [1] * MAX
is_prime[0], is_prime[1] = 0, 0


def Sieve(n):
    global is_prime
    p = 2
    while p * p <= n:
        if is_prime[p] == 1:
            for i in range(p * p, n + 1, p):
                is_prime[i] = 0
        p += 1


Sieve(MAX - 2)
gg = [0] * (MAX - 1)
for i in range(2, MAX - 1):
    gg[i] += gg[i - 1]
    if not is_prime[i]:
        gg[i] += 1
        continue
    if i * i < MAX - 1:
        gg[i * i] += 1
for _ in range(1):
    t = I()
    arr = LI()
    ans = [i - gg[i] for i in arr]
    for c in ans:
        print1(c)


# https://github.com/VaHiX/CodeForces/
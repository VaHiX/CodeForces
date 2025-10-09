# Contest 774, Problem K: Stepan and Vowels
# URL: https://codeforces.com/contest/774/problem/K

"""
For God so loved the world that he gave his one and only Son, 
that whoever believes in him shall not perish but have eternal life.
JOHN 3:16 
"""
import random
from math import *
from functools import lru_cache, cmp_to_key
from itertools import accumulate, combinations, permutations
from fractions import Fraction
from bisect import bisect_left as bl
from bisect import bisect_right as br
from operator import itemgetter
from collections import Counter, deque, defaultdict
from heapq import heappop as hpop, heappush as hpush

# constants
MOD = [10**9 + 7, 998244353]
MOD = MOD[0]
rand = random.randint(10**8, 10**9)
n, m = 0, 0
YES = ["NO", "YES"]
Yes = ["No", "Yes"]
yes = ["no", "yes"]
import sys

input = sys.stdin.readline
output = sys.stdout.write


# sys.setrecursionlimit(110000)
# #For large input
# input = sys.stdin.read
# data = input().split()
# Shortcut for input()
def I():
    return int(input())


def S():
    return input().strip()


def F():
    return float(input())


def MI():
    return map(int, input().split())


def MS():
    return map(str, input().split())


def MF():
    return map(float, input().split())


def LI():
    return list(map(int, input().split()))


def LS():
    return list(map(str, input().split()))


def LF():
    return list(map(float, input().split()))


def MAT(n):
    return [LI() for _ in range(n)]


def fast_pow(a, b, n):
    a %= n
    res = 1
    while b != 0:
        if b & 1:
            res = (res * a) % n
        a = (a * a) % n
        b >>= 1
    return res


def add(a, b):
    return (a % MOD + b % MOD) % MOD


def sub(a, b):
    return (a % MOD - b % MOD + MOD) % MOD


def pro(a, b):
    return (a % MOD * b % MOD) % MOD


def div(a, b):
    return pro(a, fast_pow(b, MOD - 2, MOD))


def inbound(i, j):
    return 0 <= i < n and 0 <= j < m


def idx(i, j):
    return i * m + j  # DSU [2D - 1D] (0 - n*m-1)


def summ(n):
    return (n * (n + 1)) >> 1


def sod(n):
    return sum(int(i) for i in str(n))


DIR4 = [(1, 0), (-1, 0), (0, 1), (0, -1)]
DIR8 = [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (-1, -1), (1, -1), (-1, 1)]
# Shortcut for output()
res = []


def OI(res):
    output("\n".join(res))


def OL(res):
    output("\n".join(" ".join(i) for i in res))


n = I()
s = S()
v = set(["a", "e", "i", "o", "u", "y"])
st = []
for i in range(n):
    if not st:
        st.append([s[i], 1])
    else:
        if st[-1][0] == s[i]:
            st[-1][1] += 1
        else:
            st.append([s[i], 1])
sp = set(["e", "o"])
ans = []
for i, count in st:
    if i in sp:
        if count == 2:
            ans.append(i * 2)
        else:
            ans.append(i)
    elif i in v:
        ans.append(i)
    else:
        ans.append(i * count)
print("".join(ans))

# Problem: CF 2156 D - Find the Last Number
# https://codeforces.com/contest/2156/problem/D

"""
Algorithm: Bit Manipulation with Binary Search
Purpose: Determine the last element of a hidden permutation by querying bitwise AND operations.

The approach uses binary representation to deduce each bit of the last element:
1. For each bit position from most significant to least significant:
   - Query all elements in the current indices with that bit position
   - Count how many elements have that bit set to 1
   - Based on the query results and count, determine if the bit in the last element is 0 or 1
2. Use bit manipulation to construct the final answer

Time Complexity: O(n * log(max_value)) where max_value is up to 10^9
Space Complexity: O(n) for storing indices and counters

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


for _ in range(I()):
    n = I()
    indices, k, ans, left = [i for i in range(1, n)], -1, 0, [i + 1 for i in range(n)]
    # Find the highest bit position needed to represent n
    for idx in range(20, -1, -1):
        if (n & (1 << idx)) > 0 and k == -1:
            k = idx
    cnt = [0] * (k + 1)
    # Count how many numbers in left have each bit set
    for num in left:
        for idx in range(k + 1):
            if (num & (1 << idx)) > 0:
                cnt[idx] += 1
    # For each bit position from most significant to least significant:
    for idx in range(k + 1):
        if not indices:
            break
        ones, zeros, temp_left = [], [], []
        # Query all elements in indices with current bit position
        for i in indices:
            if Query(i, (1 << idx)) == 1:
                ones.append(i)
                continue
            zeros.append(i)

        # If number of elements with bit set equals expected count,
        # then the bit in the last number is 0; otherwise it's 1
        if len(ones) == cnt[idx]:
            for num in left:
                if (num & (1 << idx)) == 0:
                    temp_left.append(num)
                    continue
                for idx2 in range(k + 1):
                    if (num & (1 << idx2)) > 0:
                        cnt[idx2] -= 1
                        continue
            left, indices = temp_left, zeros
            continue

        ans |= 1 << idx
        for num in left:
            if (num & (1 << idx)) > 0:
                temp_left.append(num)
                continue
            for idx2 in range(k + 1):
                if (num & (1 << idx2)) > 0:
                    cnt[idx2] -= 1
                    continue
        left, indices = temp_left, ones
    # Handle the case where the remaining bit count is 1
    for idx in range(k + 1):
        if cnt[idx] == 1:
            ans |= 1 << idx
    print2("!", ans)
    sys.stdout.flush()


# https://github.com/VaHiX/CodeForces/
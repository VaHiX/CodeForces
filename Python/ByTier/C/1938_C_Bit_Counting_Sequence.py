# Problem: CF 1938 C - Bit Counting Sequence
# https://codeforces.com/contest/1938/problem/C

"""
Bit Counting Sequence

Algorithm:
The problem requires us to find the smallest non-negative integer x such that the sequence of bit counts
p(x), p(x+1), ..., p(x+n-1) matches the given sequence a[0], a[1], ..., a[n-1].

Main approach:
- Use a greedy algorithm to reconstruct possible sequence of numbers that could produce the given bit counts.
- Use bit manipulation and properties of binary representation to validate and compute the result.
- Check transitions in bit counts and maintain consistency via bit operations.

Time Complexity: O(n * log M) where M is the maximum value of x (approximately 2^60).
Space Complexity: O(n) for storing the intermediate array b.

Techniques:
- Bit counting using .bit_count()
- Bit manipulation to detect transitions in binary representation
- Greedy reconstruction of bit patterns
"""

import sys

input = sys.stdin.readline

rn = lambda: int(input())
rs = lambda: input().strip()
rl = lambda: list(map(int, input().split()))


def solve():
    n, a = rn(), rl()

    def check():
        b = [0] * (n + 1)
        if min(a) == 0:
            b = list(range(n))
            if a == [i.bit_count() for i in b]:
                return b
            return False
        if len(a) == 1:
            return [(1 << a[0]) - 1]
        if a[1] - a[0] == 1:
            b[0] = 1
            b[1] = 1
        elif a[1] - a[0] > 1:
            return False
        else:
            b[1] = 1 << (a[0] - a[1] + 1)
            b[0] = b[1] - 1

        for i in range(2, len(a)):
            b[i] = b[i - 1] + 1
            if b[i] & 1:
                if a[i] != a[i - 1] + 1:
                    return False
            else:
                t = a[i - 1] - a[i]
                diff = (b[i - 1]).bit_count() - b[i].bit_count()
                if t < diff:
                    return False
                elif t > diff:
                    if b[i] != b[i] & -b[i]:
                        return False
                    b[i] = 1 << (t + 1)
        return b

    b = check()

    if b:
        bit_len = b[n - 1].bit_length()
        b[0] = b[n - 1] - n + 1
        _bits = [i for i in range(62) if b[0] & (1 << i)]
        bits = _bits + list(range(bit_len, bit_len + a[0] - b[0].bit_count()))
        print(sum([1 << x for x in bits]))

    else:
        print("-1")


[solve() for _ in range(rn())]


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1925 E - Space Harbour
# https://codeforces.com/contest/1925/problem/E

"""
Problem: Space Harbour
Algorithm: Binary Indexed Tree (Fenwick Tree), Coordinate Compression, Range Queries
Time Complexity: O((n + m + q) * log n)
Space Complexity: O(n)

This solution uses a Binary Indexed Tree to efficiently manage harbour positions and calculate 
the cost of moving ships. It maintains the cost of moving ships from each position to the next harbour
and handles both adding new harbours and querying ranges of ship movement costs.
"""

import sys
from types import GeneratorType


def bootstrap(f, stack=None):
    if stack is None:
        stack = []

    def func(*args, **kwargs):
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

    return func


input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))

MOD = 10**9 + 7

mx = 2 * 10**5


fac = [1] * (mx + 1)
for i in range(1, mx + 1):
    fac[i] = fac[i - 1] * i % MOD

ifac = [0] * (mx + 1)
ifac[mx] = pow(fac[mx], MOD - 2, MOD)
for i in range(mx, 0, -1):
    ifac[i - 1] = ifac[i] * i % MOD


def comb(n: int, m: int, MOD=MOD) -> int:
    if m < 0 or m > n:
        return 0
    return fac[n] * ifac[m] % MOD * ifac[n - m] % MOD


def query(x: int, y: int) -> None:
    print("?", x, y, flush=True)


def answer(x: int, y: int) -> None:
    print("!", x, y, flush=True)


class BIT:
    def __init__(self, n: int):
        self.tree = [0] * n
        self.n = n
        self.m = len(bin(n)[2:])

    def add(self, x: int, val: int) -> None:
        while x < self.n:
            self.tree[x] += val
            x |= x + 1

    def sm(self, x: int) -> int:
        res = 0
        while x > 0:
            res += self.tree[x - 1]
            x &= x - 1
        return res

    def range_sm(self, l: int, r: int) -> int:
        return self.sm(r) - self.sm(l)

    def select(self, k: int):
        x = 0
        cur = 0
        i = 1 << self.m
        while i > 0:
            if x + i <= self.n and cur + self.tree[x + i - 1] <= k:
                x += i
                cur += self.tree[x - 1]
            i //= 2
        return x


def cf1925E():
    n, m, q = mint()
    a = list(map(lambda x: int(x) - 1, input().split()))
    v = ints()

    harbour_values = [0] * n
    for x, y in zip(a, v):
        harbour_values[x] = y

    bit = BIT(n)
    for x in a:
        bit.add(x, 1)

    def get_harbour_to_left(x):
        if harbour_values[x]:
            return x
        sm = bit.sm(x + 1)
        return bit.select(sm - 1)

    def get_harbour_to_right(x):
        if harbour_values[x]:
            return x
        sm = bit.sm(x + 1)
        return bit.select(sm)

    bit_costs = BIT(n)
    cost_val = [0] * n
    idx = sorted(range(m), key=lambda p: a[p])
    for i in range(1, m):
        left_harbour = a[idx[i - 1]]
        left_harbour_value = harbour_values[left_harbour]
        habour = a[idx[i]]
        # Precompute cost for each harbour interval
        cost_val[habour] = (
            (habour - left_harbour - 1)
            * (habour - left_harbour)
            // 2
            * left_harbour_value
        )
        bit_costs.add(habour, cost_val[habour])

    ans = []
    for _ in range(q):
        op = ints()
        if op[0] == 1:
            new_harbour, new_harbour_value = op[1], op[2]
            new_harbour -= 1
            left_harbour = get_harbour_to_left(new_harbour)
            left_harbour_value = harbour_values[left_harbour]
            right_harbour = get_harbour_to_right(new_harbour)

            bit.add(new_harbour, 1)
            harbour_values[new_harbour] = new_harbour_value

            # Calculate cost for new harbour
            d = new_harbour - left_harbour - 1
            cost_val[new_harbour] = d * (d + 1) // 2 * left_harbour_value
            bit_costs.add(new_harbour, cost_val[new_harbour])

            # Adjust cost for right harbour
            d = right_harbour - new_harbour - 1
            delta = d * (d + 1) // 2 * new_harbour_value - cost_val[right_harbour]
            cost_val[right_harbour] += delta
            bit_costs.add(right_harbour, delta)
        elif op[0] == 2:
            l, r = op[1], op[2]
            l -= 1
            r -= 1

            # Check if the range has a single harbour
            if get_harbour_to_right(l) > r:
                left_harbour = get_harbour_to_left(l)
                right_harbour = get_harbour_to_right(r)
                left_harbour_value = harbour_values[left_harbour]
                d1 = right_harbour - l
                d2 = right_harbour - (r + 1)
                res = (d1 * (d1 + 1) // 2 - d2 * (d2 + 1) // 2) * left_harbour_value
                ans += [str(res)]
                continue

            # Use BIT to get accumulated cost
            res = bit_costs.range_sm(l, r + 1)

            left_harbour = get_harbour_to_left(l)
            if left_harbour == l:
                res -= cost_val[l]
            else:
                left_harbour_value = harbour_values[left_harbour]
                harbour = get_harbour_to_right(left_harbour + 1)
                d1 = harbour - (left_harbour + 1)
                d2 = harbour - l
                res -= (d1 * (d1 + 1) // 2 - d2 * (d2 + 1) // 2) * left_harbour_value

            right_harbour = get_harbour_to_right(r)
            if r < right_harbour:
                res += cost_val[right_harbour]
            harbour = get_harbour_to_left(right_harbour - 1)
            harbour_value = harbour_values[harbour]
            d = right_harbour - (r + 1)
            res -= d * (d + 1) // 2 * harbour_value
            ans += [str(res)]

    print("\n".join(ans))
    return


if __name__ == "__main__":

    cf1925E()


# https://github.com/VaHiX/CodeForces/
# Problem: CF 2009 G2 - Yunli's Subarray Queries (hard version)
# https://codeforces.com/contest/2009/problem/G2

"""
G2. Yunli's Subarray Queries (hard version)
Algorithm: Sliding window with frequency counting and deque-based optimization.
Time Complexity: O(n + q) amortized per test case assuming all operations are constant.
Space Complexity: O(n + q)

This problem asks to compute the sum of minimum operations needed to form a consecutive subarray of length k,
where each element in that subarray is increasing by 1 from the previous one, for all subarrays ending at each index
in queries. Uses preprocessing, sliding window techniques with hash map frequency tracking and deque optimization
for answering range queries efficiently.
"""

import sys
from collections import Counter
from random import getrandbits
from types import GeneratorType

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


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


def cf2002A():
    n, k, q = mint()
    a = ints()
    for i in range(n):
        a[i] -= i  # Normalize array values relative to index
    h = getrandbits(30)  # Random hash value to avoid collisions in XOR
    cnt = Counter()      # Count frequency of elements after hashing
    cnt_mx = Counter()   # Maintain count of frequencies (helps track max freq)
    mx = 0               # Current maximum frequency of any element in window
    for i in range(k):
        x = a[i]
        cnt[x ^ h] += 1
        cnt_mx[cnt[x ^ h]] += 1
        if cnt[x ^ h] > 1:
            cnt_mx[cnt[x ^ h] - 1] -= 1
        mx = max(mx, cnt[x ^ h])
    res = [k - mx]       # For each position in sliding window: min moves to make sequence continuous
    l = 0
    for r in range(k, n):
        x = a[r]
        cnt[x ^ h] += 1           # Add new element to window
        cnt_mx[cnt[x ^ h]] += 1
        if cnt[x ^ h] > 1:
            cnt_mx[cnt[x ^ h] - 1] -= 1
        mx = max(mx, cnt[x ^ h])
        x = a[l]
        cnt[x ^ h] -= 1           # Remove old element from window
        cnt_mx[cnt[x ^ h]] += 1
        cnt_mx[cnt[x ^ h] + 1] -= 1
        if cnt[x ^ h] + 1 == mx and cnt_mx[cnt[x ^ h] + 1] == 0:
            mx -= 1
        l += 1
        res.append(k - mx)
    queries = [[] for _ in range(n)]   # Store query indices for each position
    for i in range(q):
        l, r = mint()
        l -= 1
        r -= 1
        r -= k - 1
        queries[l].append(r * q + i)   # Encode query info into a single number

    res.append(0)
    m = len(res)
    dq = [m - 1]       # Monotonic deque for optimization
    acc = [0]
    ans = [-1] * q

    def check(x: int, y: int) -> bool:
        return dq[x] <= y

    for i in range(m - 2, -1, -1):
        while res[i] < res[dq[-1]]:   # Maintain monotonicity in deque
            dq.pop()
            acc.pop()
        acc.append(acc[-1] + res[i] * (dq[-1] - i))
        dq.append(i)
        for query in queries[i]:      # Process all queries starting from index i
            r, idx = divmod(query, q)
            left = 0
            right = len(dq) - 1
            while left < right:
                mid = (left + right) >> 1
                if check(mid, r):
                    right = mid - 1
                else:
                    left = mid + 1
            left = left if check(left, r) else left + 1  # Binary search for result
            ans[idx] = acc[-1] - acc[left] + res[dq[left]] * (r - dq[left] + 1)
    for x in ans:
        print(x)
    return


if __name__ == "__main__":
    t_ = sint()
    for _ in range(t_):
        cf2002A()


# https://github.com/VaHiX/codeForces/
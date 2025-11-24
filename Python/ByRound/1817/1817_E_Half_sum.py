# Problem: CF 1817 E - Half-sum
# https://codeforces.com/contest/1817/problem/E

"""
Algorithm: Half-sum
Techniques: Greedy, Bit manipulation, Modular arithmetic

Time Complexity: O(n log n + n^2)
Space Complexity: O(n)

The problem involves reducing a multiset of integers to two values by repeatedly replacing
two elements with their average. The goal is to maximize the absolute difference between
the final two values.

Approach:
1. Sort the input array to process elements in order.
2. Try different splitting points to simulate various operations.
3. Use bit manipulation and modular arithmetic to compute the result.
4. The key insight is to process the differences that can be achieved with specific splits,
   and use prefix sums and bit operations to accumulate the final answer.

The solution uses a greedy approach with binary representation to compute the maximum
possible absolute difference.
"""

import sys

MAXN = int(1e6 + 10)
MOD = int(1e9 + 7)
IV2 = (MOD + 1) // 2  # Modular inverse of 2
INF = int(1e9)

n = 0
a = [0] * MAXN
c = [0] * MAXN
d = [0] * MAXN
pw = [0] * MAXN
ans = 0


def chk(k):
    """Performs the `chk` function logic."""
    global c, d, a, n
    for i in range(n + 1):
        d[i] = 0
    for i in range(1, k + 1):
        d[i] -= a[i]
    for i in range(k + 1, n + 1):
        d[n - i + 1] += a[i]
    d[k] -= a[k]
    if k + 1 <= n:
        d[n - k] += a[k + 1]

    for i in range(n, 0, -1):
        d[i - 1] += d[i] // 2
        d[i] %= 2
        if d[i] == -1:
            d[i - 1] -= 1
            d[i] = 1

    for i in range(n + 1):
        if d[i] > c[i]:
            break
        elif d[i] < c[i]:
            return
    for i in range(n + 1):
        c[i] = d[i]


def compute_result(T, test_cases):
    global n, a, c, pw, ans
    pw[0] = 1
    for i in range(1, MAXN):
        pw[i] = pw[i - 1] * IV2 % MOD

    results = []
    for t in range(T):
        n, *numbers = test_cases[t]
        a[1 : n + 1] = numbers
        ans = 0
        c[0] = 0
        for i in range(1, n + 1):
            c[i] = 0
        a[1 : n + 1] = sorted(a[1 : n + 1])
        chk(1)
        chk(n - 1)

        cnt = 35
        for i in range(1, n):
            if cnt > 0 and a[i] != a[i + 1]:
                chk(i)
                cnt -= 1

        cnt = 35
        for i in range(n - 1, 0, -1):
            if cnt > 0 and a[i] != a[i + 1]:
                chk(i)
                cnt -= 1

        for i in range(n + 1):
            ans = (ans + pw[i] * c[i]) % MOD

        results.append(ans)
    return results


def main():
    input = sys.stdin.read
    data = list(map(int, input().split()))
    T = data[0]
    idx = 1
    test_cases = []
    for _ in range(T):
        n = data[idx]
        test_cases.append([n] + data[idx + 1 : idx + 1 + n])
        idx += 1 + n
    results = compute_result(T, test_cases)
    for result in results:
        print(result)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
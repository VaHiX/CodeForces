# Contest 1864, Problem E: Guess Game
# URL: https://codeforces.com/contest/1864/problem/E

import sys

input = sys.stdin.readline

mod = 998244353


def f(a, b):
    cnt = 0
    for i in range(30, -1, -1):
        if a & (1 << i) == b & (1 << i) != 0:
            cnt += 1
        elif a & (1 << i) != b & (1 << i):
            break
    return cnt


def g(arr):
    stack = []
    sum_of_minimums = 0
    for i in range(len(arr) + 1):
        # when i reaches the array length, it is an indication that
        # all the elements have been processed, and the remaining
        # elements in the stack should now be popped out.
        while stack and (i == len(arr) or arr[stack[-1]] >= arr[i]):
            # Notice the sign ">=", This ensures that no contribution
            # is counted twice. right_boundary takes equal or smaller
            # elements into account while left_boundary takes only the
            # strictly smaller elements into account
            mid = stack.pop()
            left_boundary = -1 if not stack else stack[-1]
            right_boundary = i
            # count of subarrays where mid is the minimum element
            count = (mid - left_boundary) * (right_boundary - mid)  # %mod
            sum_of_minimums = sum_of_minimums + (count * arr[mid])  # %mod
        stack.append(i)
    return sum_of_minimums


t = int(input())
for _ in range(t):
    n = int(input())
    s = sorted(list(map(int, input().split())))
    ans = n * (n - 1) // 2
    curr = 1
    for i in range(1, n):
        if s[i] == s[i - 1]:
            curr += 1
        else:
            ans -= curr * (curr - 1) // 2
            curr = 1
    ans -= curr * (curr - 1) // 2
    l = []
    for i in range(n):
        ans += f(s[i], s[i]) + 1
        if i < n - 1:
            l.append(f(s[i], s[i + 1]) + 1)
    ans = ((ans + 2 * g(l)) * pow(n, 2 * (mod - 2), mod)) % mod
    print(ans)

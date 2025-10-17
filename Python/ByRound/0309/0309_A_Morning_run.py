# Contest 309, Problem A: Morning run
# URL: https://codeforces.com/contest/309/problem/A

import bisect
from math import gcd, lcm
import sys

input = lambda: sys.stdin.readline().strip()


def I():
    return input()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def LFI():
    return list(map(float, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


# def main():
#     n, l, t = MII()
#     nums = LII()

#     t *= 2

#     ans = 0

#     # 任意两个人，跑的总距离 2t
#     # 设两人相向而行的位置差 = d
#     # k = [2t / l]
#     # k: d > 2t - k * l
#     # k + 1: d <= 2t - k * l

#     k, d = divmod(t, l)
#     ans = n * (n - 1) * k

#     for i in range(n):
#         nums.append(nums[i] + l)

#     for i in range(n):
#         ans += bisect.bisect_right(nums, nums[i] + d) - i - 1

#     print(ans / 4)

# main()


def main():
    n, l, t = MII()
    a = LII()
    # 将时间乘以2
    t *= 2
    d = t % l
    k = t // l

    ans = n * (n - 1) * k

    # 扩展数组以处理环状情况
    a.extend([x + l for x in a])
    left = 0

    for right in range(n):
        while left < 2 * n and a[left] <= a[right] + d:
            left += 1
        ans += left - right - 1

    print(ans / 4)


if __name__ == "__main__":
    main()

# Problem: CF 2053 H - Delicate Anti-monotonous Operations
# https://codeforces.com/contest/2053/problem/H

"""
Algorithm: Delicate Anti-monotonous Operations
Purpose: To find the maximum possible sum of array elements after performing 
         operations that eliminate adjacent equal elements by replacing them 
         with values within [1, w], ensuring no adjacent elements are equal.
Approach:
    - If no adjacent equal elements exist, return sum and 0 operations.
    - Otherwise:
        - Max sum is calculated as w * n - 1 (if possible).
        - Minimum operations are determined through analysis of segments 
          and specific pattern recognition.

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm works by:
1. Identifying if any adjacent equal elements exist.
2. Computing the maximum achievable sum.
3. Evaluating the minimum number of operations required using
   dynamic considerations on segments of the array.
"""

import sys

input = sys.stdin.read
data = input().split()
index = 0


def fast_input():
    global index
    value = data[index]
    index += 1
    return value


def main():
    ta = int(fast_input())
    for _ in range(ta):
        n = int(fast_input())
        w = int(fast_input())
        a = [int(fast_input()) for _ in range(n)]
        can = 0
        for i in range(1, n):
            if a[i] == a[i - 1]:
                can = 1
        total_sum = sum(a)
        if can == 0:
            print(total_sum, 0)
            continue
        ans = w * n - 1
        if total_sum >= ans:
            print(total_sum, 0)
            continue
        if w == 2:
            k = 0
            l = 0
            for i in range(n):
                if a[i] == 1 and (i == 0 or a[i - 1] == 2):
                    k += 1
                if i > 0 and a[i] == 1 and a[i - 1] == 1:
                    l += 1
            print(2 * n - k, l)
            continue
        dist = 2 * n
        if (a[0] == a[1] and a[0] == w) or (a[n - 1] == a[n - 2] and a[n - 1] == w):
            dist = 0
        while a and a[-1] == w:
            a.pop()
        a.reverse()
        while a and a[-1] == w:
            a.pop()
        pen = 0
        n = len(a)
        cnt = 0
        for x in a:
            if x == w:
                cnt += 1
            else:
                if cnt == 1:
                    pen += 2
                else:
                    pen += (cnt + 1) // 2
                cnt = 0
        if cnt == 1:
            pen += 2
        else:
            pen += (cnt + 1) // 2
        ans3 = 10 * n + 1000000000
        if dist == 0:
            ans3 = n + 1 + pen
        i = 1
        c1 = 0
        while i < n and a[i] != a[i - 1]:
            if a[i - 1] == w:
                c1 += 1
            i += 1
        ans1 = ans3
        dec = 0
        if (
            i > 1
            and i + 1 < n
            and a[i] != w
            and a[i + 1] == w
            and a[i + 2] != w
            and (i == 1 or a[i - 2] != w)
        ):
            dec = 1
        if i < n:
            ans1 = n - 1 + pen - c1 * 2 + i - 1 - int(a[i] == w) - dec
        a.reverse()
        i = 1
        c1 = 0
        while i < n and a[i] != a[i - 1]:
            if a[i - 1] == w:
                c1 += 1
            i += 1
        ans2 = ans3
        dec = 0
        if (
            i > 1
            and i + 1 < n
            and a[i] != w
            and a[i + 1] == w
            and a[i + 2] != w
            and (i == 1 or a[i - 2] != w)
        ):
            dec = 1
        if i < n:
            ans2 = n - 1 + pen - c1 * 2 + i - 1 - int(a[i] == w) - dec
        print(ans, min(ans1, ans2, ans3))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1979 A - Guess the Maximum
# https://codeforces.com/contest/1979/problem/A

"""
Algorithm: 
The problem requires finding the maximum value of k such that Alice always wins.
Alice wins if the maximum element in any subarray chosen by Bob is strictly greater than k.
To guarantee Alice's win, we must find the largest k such that ALL possible subarrays have max <= k.
This is equivalent to finding the largest k where the maximum of all adjacent pairs is greater than k.
Hence, the answer is the minimum of all adjacent pairs minus 1.

Time Complexity: O(n) - We iterate through the array once to compute the minimum of adjacent pairs.
Space Complexity: O(1) - Only constant extra space is used.
"""

from sys import stdin


def input():
    return stdin.readline()[:-1]


def ili():
    return list(map(int, input().split()))


def fastout(S):
    print(" ".join(map(str, S)))


def solve():
    n = int(input())
    a = ili()
    # Find the minimum of all adjacent pairs
    val = min(max(a[i], a[i + 1]) for i in range(n - 1))
    # The maximum k such that Alice always wins is this minimum minus 1
    print(val - 1)
    return


case_num = 1
case_num = int(input())
for case in range(case_num):
    solve()


# https://github.com/VaHiX/CodeForces/
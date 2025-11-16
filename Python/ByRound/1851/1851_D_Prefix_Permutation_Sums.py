# Problem: CF 1851 D - Prefix Permutation Sums
# https://codeforces.com/contest/1851/problem/D

"""
Algorithm: Prefix Permutation Sums
Purpose: Determine if a given array of prefix sums (with one element missing) can correspond to a permutation of numbers from 1 to n.

Approach:
1. We know that the original array's prefix sums have the property that a[i] - a[i-1] equals the i-th element of the original permutation.
2. Since we're missing one element from the prefix sums, we examine the differences between consecutive elements.
3. For a valid permutation, these differences should correspond to a subset of {1, 2, ..., n} (missing one element).
4. Identify the missing two elements from the set {1, 2, ..., n} that were not represented in the differences.
5. Try reconstructing possible values for these missing elements and check if valid.

Time Complexity: O(n) for each test case, since we process at most n elements in the loop.
Space Complexity: O(n) for storing the seen array and remainder elements.
"""

import sys
from os import path

if path.exists("Input.txt"):
    sys.stdin = open("Input.txt", "r")
    sys.stdout = open("Output.txt", "w")


input = sys.stdin.buffer.readline

print = sys.stdout.write


from random import randint


class mydict:
    def __init__(self, func=lambda: 0):
        self.random = randint(0, 1 << 32)
        self.default = func
        self.dict = {}

    def __getitem__(self, key):
        mykey = self.random ^ key
        if mykey not in self.dict:
            self.dict[mykey] = self.default()
        return self.dict[mykey]

    def get(self, key, default):
        mykey = self.random ^ key
        if mykey not in self.dict:
            return default
        return self.dict[mykey]

    def __setitem__(self, key, item):
        mykey = self.random ^ key
        self.dict[mykey] = item

    def getkeys(self):
        return [self.random ^ i for i in self.dict]

    def __str__(self):
        return f"{[(self .random ^i ,self .dict [i ])for i in self .dict ]}"


def solve():
    n = int(input())
    a = [int(x) for x in input().split()]
    seen = [False for i in range(n + 1)]
    for i in range(1, n - 1):
        val = a[i] - a[i - 1]
        if val < 1 or val > n:
            continue
        seen[val] = True
    rem = []
    for i in range(1, n + 1):
        if seen[i] == False:
            rem.append(i)
    if len(rem) > 3:
        print("NO\n")
        return

    if len(rem) == 2:

        if sum(rem) == a[0]:
            print("YES\n")
            return

        if a[0] in rem:
            print("YES\n")
            return
    else:

        s = sum(rem)
        if a[0] >= 1 and a[0] <= n and seen[a[0]] == False:
            seen[a[0]] = True
            s -= a[0]
        else:
            print("NO\n")
            return
        times = 0
        for i in range(1, n - 1):
            if a[i] - a[i - 1] == s:
                times += 1
        if s >= 1 and s <= n and seen[s]:
            if times == 2:
                print("YES\n")
                return
            else:
                print("NO\n")
                return
        if times == 1:
            print("YES\n")
            return

    print("NO\n")


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/
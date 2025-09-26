# Contest 1641, Problem B: Repetitions Decoding
# URL: https://codeforces.com/contest/1641/problem/B

# for I/O for local system
import sys
from os import path

if path.exists("Input.txt"):
    sys.stdin = open("Input.txt", "r")
    sys.stdout = open("Output.txt", "w")

# For fast I/O
input = sys.stdin.buffer.readline
# input = sys.stdin.readline
print = sys.stdout.write

# Import libraries here whenever required
from random import randint


# Use this because normal dict can sometimes give TLE
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
        return f"{[(self.random ^ i, self.dict[i]) for i in self.dict]}"


# Solver function
def solve():
    d = mydict()
    for i in a:
        d[i] += 1
    for i in d.getkeys():
        if d[i] & 1:
            print("-1\n")
            return
    l = 0
    r = 1
    ans = []
    size = []
    prev = -1
    while r < len(a):
        while r < len(a):
            if a[r] == a[l]:
                break
            r += 1
        # l...r subarray
        till = r
        size.append((r - l) * 2)
        # print(l, r)
        # print(a)
        l += 1
        r += 1
        while l < till:
            a.insert(r, a[l])
            a.insert(r, a[l])
            ans.append([r, a[l]])
            r += 1
            l += 1
        l = r
        r += 1
    assert len(ans) <= 2 * n * n
    print(str(len(ans)) + "\n")
    for x, y in ans:
        print(str(x) + " " + str(y) + "\n")
    print(str(len(size)) + "\n")
    # print(a)
    print(" ".join(map(str, size)) + "\n")


# Main
for _ in range(int(input())):
    n = int(input())
    a = [int(x) for x in input().split()]
    solve()

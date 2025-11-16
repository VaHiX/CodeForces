# Problem: CF 1641 B - Repetitions Decoding
# https://codeforces.com/contest/1641/problem/B

"""
Algorithm: Repetitions Decoding
Approach:
1. First, check if the array can be split into tandem repeats by ensuring all elements appear an even number of times.
2. If not, it's impossible to split into tandem repeats, so return -1.
3. If yes, we process the array greedily:
   - Find segments that can form tandem repeats by looking for matching pairs.
   - When a mismatch is found, we insert duplicate elements to make the segment a tandem repeat.
   - Record all insertions made.
4. Finally, output the number of operations, the operations themselves, and the decomposition into tandem repeat lengths.

Time Complexity: O(n^3) where n is the array length due to nested loops and insertions.
Space Complexity: O(n) for storing the array and helper structures.
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
        return f"{[(self.random ^ i, self.dict[i]) for i in self.dict]}"


def solve():
    d = mydict()
    for i in a:
        d[i] += 1
    for i in d.getkeys():
        if d[i] & 1:  # Check if count is odd
            print("-1\n")
            return
    l = 0
    r = 1
    ans = []
    size = []
    while r < len(a):
        while r < len(a):
            if a[r] == a[l]:
                break
            r += 1
        till = r
        size.append((r - l) * 2)  # Length of the tandem repeat
        l += 1
        r += 1
        while l < till:
            # Inserting duplicate elements to maintain tandem repeat property
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
    print(" ".join(map(str, size)) + "\n")


for _ in range(int(input())):
    n = int(input())
    a = [int(x) for x in input().split()]
    solve()


# https://github.com/VaHiX/CodeForces/
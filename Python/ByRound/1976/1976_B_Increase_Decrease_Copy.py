# Problem: CF 1976 B - Increase/Decrease/Copy
# https://codeforces.com/contest/1976/problem/B

"""
Algorithm/Technique: Greedy + Minimization
Approach:
1. For each element in array a, we compute the absolute difference with the corresponding element in array b.
2. We then consider the last element of b (b[n]) as a "target" for potential copying operations.
3. The idea is to determine whether we can minimize the operations by copying an element from a such that it helps with the last element of b.
4. If the last element of b falls within the range of any element in a and its corresponding element in b, then no extra operations are needed for that case.
5. Otherwise, we evaluate the minimum cost of copying any element from a such that it helps reduce operations involving the last element of b.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage
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
    lst = b[-1]  # Last element of b array
    ans = 1      # Start with one operation count (possibly a copy operation)
    adder = 10**18  # Initialize with a large value to track minimum cost
    
    for i in range(n):
        # Accumulate the cost of changing each element of a to match b
        ans += abs(a[i] - b[i])
        
        # Determine the minimum and maximum values between current a[i] and b[i]
        mn = min(b[i], a[i])
        mx = max(b[i], a[i])
        
        # If lst (last element of b) lies in the range [mn, mx], 
        # it means no operation is needed for this part
        if lst >= mn and lst <= mx:
            adder = 0
        else:
            # Otherwise, take the minimum difference between lst and either mn or mx
            adder = min(adder, abs(mn - lst), abs(mx - lst))
    
    # Add the minimal extra cost for handling last element if needed
    ans += adder
    print(str(ans) + "\n")


for _ in range(int(input())):
    n = int(input())
    a = [int(x) for x in input().split()]
    b = [int(x) for x in input().split()]
    solve()


# https://github.com/VaHiX/CodeForces/
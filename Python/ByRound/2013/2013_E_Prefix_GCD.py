# Problem: CF 2013 E - Prefix GCD
# https://codeforces.com/contest/2013/problem/E

"""
E. Prefix GCD

Purpose:
This code solves the problem of finding the minimum possible sum of GCDs of prefixes of an array,
where the array elements can be rearranged in any order.

Algorithm:
- First, compute the GCD of all elements in the array. This value is used to normalize the array.
- Then, for each element in the array, divide it by this global GCD to reduce the problem size.
- The strategy involves computing prefix GCDs greedily: at each step, we select an element that minimizes
  the prefix GCD among remaining elements.
- Once a prefix GCD of 1 is achieved, all remaining terms are 1, so we add (n - i - 1) to the result.

Time Complexity: O(n * sqrt(max_a)) where n is the number of elements in the array and max_a is the maximum element.
Space Complexity: O(n) for storing the input array and intermediate results.

Techniques:
- GCD computation using math.gcd
- Greedy prefix selection with optimization when GCD becomes 1
"""

import sys

input = sys.stdin.readline
from math import gcd


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    
    # Compute the GCD of all elements to normalize the array
    g = 0
    for x in a:
        g = gcd(g, x)
    
    # Normalize the array by dividing each element by the global GCD
    for i in range(n):
        a[i] //= g
    
    # Initialize answer and current prefix GCD
    ans = 0
    cur = 0
    
    # Compute prefix GCDs greedily
    for i in range(n):
        mn = 1e9  # Minimum GCD found so far
        for j in range(n):
            # Update minimum prefix GCD by considering current element
            mn = min(mn, gcd(cur, a[j]))
        cur = mn  # Set new prefix GCD
        ans += cur  # Add to total sum
        
        # If GCD of prefix becomes 1, all remaining elements will also have GCD 1
        if cur == 1:
            ans += n - i - 1
            break
    
    print(ans * g)  # Multiply by global GCD to get final result


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/
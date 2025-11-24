# Problem: CF 1909 D - Split Plus K
# https://codeforces.com/contest/1909/problem/D

"""
Algorithm: Split Plus K
Purpose: Determine the minimum number of operations to make all numbers on the blackboard equal.
Techniques:
    - Mathematical analysis using GCD (Greatest Common Divisor)
    - Transformation of problem into GCD-based solution
Time Complexity: O(n * log(max(a))) where n is the number of elements, due to GCD computation
Space Complexity: O(n) for storing the transformed array

The key insight is to consider the transformation a[i] -> a[i] - k, then check if all elements 
have the same sign. Then compute the GCD of absolute values and determine how many splits 
are needed to make all elements equal to the GCD.
"""

import sys

input = sys.stdin.readline
import math


def readList():
    return list(map(int, input().split()))


def readInt():
    return int(input())


def readInts():
    return map(int, input().split())


def readStr():
    return input().strip()


def solve():
    n, k = readInts()
    a = readList()
    # Transform all elements by subtracting k
    a = [v - k for v in a]
    mi, ma = min(a), max(a)
    
    # If all elements are of the same sign (both non-negative or both non-positive)
    if mi * ma > 0:
        # Take absolute values to work with magnitudes
        a = [abs(v) for v in a]
        g = a[0]
        # Compute GCD of all transformed numbers
        for v in a:
            g = math.gcd(g, v)
        
        # Calculate total operations needed:
        # For each number, we need (number / g) - 1 operations to split it down to g
        return sum([v // g - 1 for v in a])
    
    # If all elements are zero (same value after transformation)
    elif mi == ma:
        return 0
    
    # Otherwise, it is impossible to make all numbers equal
    else:
        return -1


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/
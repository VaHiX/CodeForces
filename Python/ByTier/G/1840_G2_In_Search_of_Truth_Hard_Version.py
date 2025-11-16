# Problem: CF 1840 G2 - In Search of Truth (Hard Version)
# https://codeforces.com/contest/1840/problem/G2

"""
Interactive problem to determine the number of sectors in a circle.
Uses random and systematic queries to deduce the total number of sectors.

Algorithms/Techniques:
- Random queries to find a maximum sector number
- Systematic queries to track movement patterns
- Set-based detection to identify cycle and repeat patterns
- Mathematical deduction based on movement and repetition

Time Complexity: O(1000) = O(1) since maximum queries are fixed
Space Complexity: O(d) = O(300) = O(1) for storing list of queries
"""

import sys
from random import randint as r

def print(value):
    sys.stdout.write(str(value) + "\n")

def brint(l):
    print(" ".join(str(y) for y in l))

def ii():
    return int(input())

def rl():
    return list(map(int, input().split()))

d = 300  # Number of iterations for systematic queries
x = int(input())  # Initial sector number
m = x  # Track maximum sector number encountered

# Random queries to find a likely maximum sector number
for i in range(d):
    print(f"+ {r(1, 10 ** 9)}")  # Move by a random amount (1 to 10^9)
    sys.stdout.flush()
    x = int(input())
    m = max(m, x)  # Keep track of maximum seen sector

a = [x]  # List to store results of systematic queries

# Perform systematic queries of +1 to track movement
for i in range(d):
    print("+ 1")
    sys.stdout.flush()
    x = ii()
    a.append(x)

s = set(a)  # Convert to set to detect duplicates
if len(s) < len(a):  # If duplicates exist, we've wrapped around
    # Determine n from the index of repeated element
    print(f"! {a[1:].index(a[0]) + 1}")
    sys.exit()

# Query forward by 'm' sectors
print(f"+ {m}")
sys.stdout.flush()
x = ii()
if x in s:  # If this sector was seen in the pattern
    # Calculate n using the offset and the index of repeated sector
    print(f"! {m + d - a.index(x)}")
    sys.exit()

# Perform systematic queries of +d to find pattern again
for i in range(d):
    print(f"+ {d}")
    sys.stdout.flush()
    x = ii()
    if x in s:  # If repeated sector found
        # Use formula to calculate n based on iterations and offset
        print(f"! {m + d * (i + 2) - a.index(x)}")
        sys.exit()


# https://github.com/VaHiX/CodeForces/
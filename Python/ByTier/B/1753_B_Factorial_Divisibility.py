# Problem: CF 1753 B - Factorial Divisibility
# https://codeforces.com/contest/1753/problem/B

from collections import Counter

# Flower box describing the code purpose, algorithms, time and space complexity
"""
Code Purpose:
This code determines if the sum of factorials of elements in an array is divisible by x!.
It uses an efficient approach to calculate the sum of factorials modulo x! and checks divisibility.

Algorithms/Techniques:
- Uses factorial properties and modular arithmetic
- Processes elements in ascending order
- Builds up factorials incrementally, avoiding recomputation
- Uses Counter to count occurrences of each factorial value

Time Complexity: O(n + x)
Space Complexity: O(x)
"""

n, x = map(int, input().split())
a = Counter(map(int, input().split()))
c = min(a)
while c < x:
    if a[c] % (c + 1):  # If current count is not divisible by (c+1), then it's not divisible by (c+1)!
        print("No")
        exit()
    else:
        # Add the number of (c+1)! contributions to the next level
        a[c + 1] += a[c] // (c + 1)
        c += 1
print("Yes")


# https://github.com/VaHiX/CodeForces/
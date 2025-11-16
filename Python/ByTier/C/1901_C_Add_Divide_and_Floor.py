# Problem: CF 1901 C - Add, Divide and Floor
# https://codeforces.com/contest/1901/problem/C

"""
Algorithm/Techniques: Binary search, bit manipulation, floor division optimization

Time Complexity: O(n * log(max(a)) + sum(n)) where n is the length of array and max(a) is the maximum value in the array
Space Complexity: O(n) for storing the answer array and intermediate results

The problem involves reducing an array to all equal elements by performing operations where each element is replaced with floor((element + x) / 2) for some value x. We use binary representation and bit shifting to simulate the operations efficiently.
"""
import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

t = int(input())
ans = []
inf = 1 << 32
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    mi, ma = min(a), max(a)
    if mi == ma:
        ans0 = 0
        ans.append(str(ans0))
        continue
    x = inf - mi   # Compute x such that (mi + x) >> 1 is the midpoint
    mi, ma = (mi + x) >> 1, (ma + x) >> 1   # Update min and max after adding x and dividing by 2
    ans0 = [x]
    while mi ^ ma:   # While mi and ma are not equal (different bits)
        mi, ma = mi >> 1, ma >> 1   # Right shift both to check next bit
        ans0.append(0)   # Append 0 for operation (no addition of x)
    l = len(ans0)
    ans.append(str(l))
    if l <= n:
        ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/
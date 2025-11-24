# Problem: CF 1805 C - Place for a Selfie
# https://codeforces.com/contest/1805/problem/C

"""
Algorithm: 
- For each parabola y = ax^2 + bx + c, we want to find a line y = kx such that 
  the line does not intersect or touch the parabola.
- This is equivalent to solving ax^2 + bx + c = kx for x, which gives ax^2 + (b-k)x + c = 0.
- For no intersection, the discriminant must be negative: (b-k)^2 - 4ac < 0.
- Rearranging this inequality: (b-k)^2 < 4ac.
- Taking square root: |b-k| < 2*sqrt(ac) => -2*sqrt(ac) < b-k < 2*sqrt(ac).
- Solving for k: b - 2*sqrt(ac) < k < b + 2*sqrt(ac).
- We need to find a k from the list of available k values that is NOT in this range [b - 2*sqrt(ac), b + 2*sqrt(ac)].
- To do this efficiently, sort the k values and use binary search to check if 
  any value lies in the invalid range. If none does, we can return any suitable value.

Time Complexity: O(n log n + m * log n)
Space Complexity: O(n)

"""
import sys
from bisect import *

input = sys.stdin.readline
print = sys.stdout.write
for _ in range(int(input())):
    n, m = map(int, input().split())
    ans = []
    lis = sorted([int(input()) for i in range(n)])
    for j in range(m):
        a, b, c = map(int, input().split())
        if a * c <= 0:
            print("NO\n")
            continue
        # Calculate the lower and upper bounds for k such that line intersects the parabola
        left = b - (4 * a * c) ** 0.5
        right = b + (4 * a * c) ** 0.5
        # Use binary search to find first element in lis that is greater than left
        val = bisect_right(lis, left)
        # Check if there is a valid k in the list (i.e., k > left and k < right)
        if val != n and right > lis[val] >= left:
            print("YES\n")
            print(str(lis[val]) + "\n")
        else:
            print("NO\n")


# https://github.com/VaHiX/CodeForces/
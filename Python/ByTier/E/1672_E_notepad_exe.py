# Problem: CF 1672 E - notepad.exe
# https://codeforces.com/contest/1672/problem/E
 
"""
Algorithm: Binary search + Query optimization to find the minimum area w * h_w
Approach:
1. Use binary search to find the minimum width w such that h_w = 1 (i.e., all words can fit in one line)
2. Once we have this width, we try dividing it by integers from 2 to n to find better combinations
3. For each valid width, query the height and compute the area w * h_w to track the minimum
 
Time Complexity: O(n * log(max_length) + n * log(n))
Space Complexity: O(1)
 
The key insight is that for very small widths, h_w = 0 (crash), and for large enough width h_w = 1.
We binary search to find this transition point, then test a few candidates around it.
"""
 
I = lambda: int(input())
n = I()
sml = 0
big = 5000000
while big - sml > 1:
    mid = (big + sml) // 2
    print("?", mid)
    x = I()
    if x != 1:  # If height is not 1, we are too narrow, increase lower bound
        sml = mid
    else:  # If height is 1, we can try a smaller width
        big = mid
 
best = big  # Initial best area is width * height = big * 1
for i in range(2, n + 1):  # Try dividing the width by 2 to n
    print("?", big // i)  # Query with reduced width
    x = I()
    if x > 0:  # Only consider valid widths (where h_w != 0)
        best = min(best, x * (big // i))  # Update minimum area
print("!", best)
 
 
# https://github.com/VaHiX/CodeForces/
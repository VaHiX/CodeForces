# Problem: CF 1718 A2 - Burenka and Traditions (hard version)
# https://codeforces.com/contest/1718/problem/A2

"""
Code Purpose:
This code solves the problem of finding the minimum time needed to reduce all elements of an array to zero using a specific XOR operation on segments. The key insight is to use XOR prefix sums and track when a prefix sum repeats, indicating a segment that can be toggled to zero in one operation.

Algorithms/Techniques:
- Prefix XOR technique
- Set-based tracking of seen prefix XOR values
- Greedy approach to minimize operations

Time Complexity: O(n) where n is the length of the array
Space Complexity: O(n) for storing prefix XOR values in a set
"""

for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    ans = n  # Initially assume we need n operations (each element handled separately)
    now = 0  # Current prefix XOR value
    s = set()
    s.add(0)  # Add 0 to handle the case where a prefix itself is 0
    
    for a in arr:
        now ^= a  # Compute prefix XOR
        if now in s:
            # If we have seen this prefix XOR before, 
            # it means we can toggle the segment from that point to current
            ans -= 1  # Reduce the number of operations needed
            s.clear()  # Reset the set to start fresh from current index
        s.add(now)  # Add current prefix XOR to set
        
    print(ans)


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1957 A - Stickogon
# https://codeforces.com/contest/1957/problem/A

"""
Purpose: 
    This code solves the problem of finding the maximum number of regular polygons 
    that can be formed using given stick lengths. Each polygon requires at least 3 
    sticks of equal length (since a regular polygon with k sides needs k equal sides).
    
    The algorithm uses a frequency counting approach:
    - Count how many sticks of each length exist.
    - For each length, calculate how many complete polygons (with at least 3 sides) 
      can be formed using those sticks.
    - Sum up all such possible polygons across all lengths.

Algorithms/Techniques:
    - Frequency counting using Counter from collections
    - Greedy selection: for each stick length, we determine how many 3-sided 
      polygons can be made (as minimum for a polygon).

Time Complexity: O(n)
    - Where n is the number of sticks. We iterate through the list once to build 
      the counter, and then iterate through the frequency map, which is at most 
      the number of unique stick lengths (at most n).

Space Complexity: O(n)
    - For storing the frequency map (Counter), which in the worst case stores all 
      stick lengths if they are all unique.

"""
from collections import Counter

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    v = Counter(a)  # Count frequency of each stick length
    ans = 0
    for i in v.values():  # For each frequency count
        ans += i // 3  # Each set of 3 sticks can form one polygon (minimum 3 sides)
    print(ans)


# https://github.com/VaHiX/CodeForces/
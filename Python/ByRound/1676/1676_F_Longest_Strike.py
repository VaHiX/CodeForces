# Problem: CF 1676 F - Longest Strike
# https://codeforces.com/contest/1676/problem/F
 
"""
Algorithm: Longest Strike
Techniques: 
- Sorting and frequency counting using Counter
- Sliding window / greedy approach to find maximum valid range
 
Time Complexity: O(n log n) due to sorting, where n is the length of the array
Space Complexity: O(n) for storing frequency counts and the sorted array
 
The problem asks to find the longest contiguous range [l, r] such that every number in this range appears at least k times in the array.
"""
 
from collections import Counter
 
t = int(input())
while t > 0:
    n, k = map(int, input().split())
    d = list(map(int, input().split()))
    d.sort()  # Sort the array to process elements in order
    p = Counter(d)  # Count frequency of each element
    p1 = Counter()  # This will store the length of valid sequence ending at each element
    mx = 0  # Track the maximum endpoint of a valid sequence
    for i in p:
        # If current element occurs at least k times
        if p[i] >= k:
            p1[i] = p1[i - 1] + 1  # Extend previous sequence by 1
        if p1[i] > p1[mx]:  # Update maximum length if needed
            mx = i
    print()
    if mx == 0:
        print(-1)  # No valid range found
    else:
        # Calculate left endpoint of the longest valid range
        print(mx - p1[mx] + 1, mx)
    t -= 1
 
 
# https://github.com/VaHiX/CodeForces/
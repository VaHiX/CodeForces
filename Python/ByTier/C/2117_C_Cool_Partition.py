# Problem: CF 2117 C - Cool Partition
# https://codeforces.com/contest/2117/problem/C

"""
C. Cool Partition
Algorithms/Techniques: Two-pointer technique with set operations to track element presence.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n) for storing sets to track unique elements in segments.

The problem asks to find the maximum number of contiguous segments such that 
every element in a segment also appears in the next segment (if it exists). 
This can be efficiently solved using two sets to maintain the union of elements 
in current and previous segments, and incrementing the count when all elements 
of previous segment are present in current.
"""

for _ in range(int(input())):  # Read number of test cases
    n, a = int(input()), list(input().split())  # Read array size and elements
    r, l = set(), set()  # r tracks elements in current segment; l tracks elements in previous segments
    cnt = 0  # Count of cool partitions
    for _ in a:  # Iterate through each element in array
        r.add(_)  # Add current element to the set of current segment
        l.add(_)  # Add current element to the set of all seen so far
        if len(r) == len(l):  # If sets are equal, it means all elements in r have been seen in earlier segments
            cnt += 1  # Increment partition count
            r.clear()  # Reset current segment's element set for next segment
    print(cnt)  # Output the maximum number of cool partitions


# https://github.com/VaHiX/codeForces/
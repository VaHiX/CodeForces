# Problem: CF 2057 B - Gorilla and the Exam
# https://codeforces.com/contest/2057/problem/B

"""
B. Gorilla and the Exam

Problem Description:
Given an array of integers and a number of allowed modifications k, find the minimum number of operations 
to empty the array using a specific removal rule.

The operation is: choose a subarray, take its minimum value, then remove all elements equal to that minimum.
This process continues until the array is empty. We are allowed to modify up to k elements in the array.

Algorithm:
1. Count frequencies of each unique element in the sorted array.
2. Sort frequency counts in ascending order.
3. Greedily reduce the number of groups by using available modifications (k) on smaller frequency groups.
4. The result is the count of remaining groups after applying optimal modifications.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing frequency counts and sorted array

"""

for t in range(int(input())):
    n, k = map(int, input().split())
    m = sorted(list(map(int, input().split())))
    p = [1]
    # Group consecutive equal elements and count their frequencies
    for i in range(1, n):
        if m[i] == m[i - 1]:
            p[-1] += 1
        else:
            p.append(1)
    p.sort()  # Sort frequencies in ascending order
    r = len(p)  # Initialize result as total number of groups
    
    # Try to merge smaller groups using at most k operations
    for i in range(len(p) - 1):
        if p[i] > k:
            break  # Cannot merge this group with others using remaining k operations
        r -= 1  # Reduce count of groups by merging
        k -= p[i]  # Use up operations to merge this group
    
    print(r)


# https://github.com/VaHiX/codeForces/
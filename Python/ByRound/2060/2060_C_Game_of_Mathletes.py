# Problem: CF 2060 C - Game of Mathletes
# https://codeforces.com/contest/2060/problem/C

"""
C. Game of Mathletes

Purpose:
This code solves a game theory problem where Alice and Bob take turns selecting integers from a list.
Alice tries to minimize the score (number of pairs summing to k), while Bob tries to maximize it.
The optimal strategy is modeled using a two-pointer technique on a sorted array.

Algorithms/Techniques:
- Two-pointer technique
- Greedy approach

Time Complexity: O(n log n) per test case due to sorting; O(n) for the two-pointer traversal.
Space Complexity: O(1) if we ignore the space used for input/output, otherwise O(n) for sorting.

Input Format:
- First line: number of test cases t
- For each test case:
  - Line 1: n (number of integers) and k (target sum)
  - Line 2: n integers on the blackboard

Output:
- Score after game ends with optimal play.
"""

for _ in range(int(input())):  # Process each test case
    n, k = map(int, input().split())  # Read n and k
    a = list(map(int, input().split()))  # Read the array of integers
    a.sort()  # Sort the array to enable two-pointer technique
    
    l = 0  # Left pointer
    r = n - 1  # Right pointer
    ctr = 0  # Counter for valid pairs
    
    while r > l:  # While pointers haven't crossed
        if a[r] + a[l] == k:  # If sum equals target
            r -= 1  # Move right pointer left
            l += 1  # Move left pointer right
            ctr += 1  # Increment pair count
        elif a[r] + a[l] > k:  # If sum is greater than target
            r -= 1  # Reduce sum by moving right pointer left
        else:  # If sum is less than target
            l += 1  # Increase sum by moving left pointer right
    
    print(ctr)  # Output the final score


# https://github.com/VaHiX/codeForces/
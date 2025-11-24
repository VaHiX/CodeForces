# Problem: CF 1899 E - Queue Sort
# https://codeforces.com/contest/1899/problem/E

"""
Purpose: 
    This code determines the minimum number of operations required to sort an array 
    using a specific operation: extract the first element and insert it at the end, 
    then swap it backward until it's in the correct position relative to previous elements.
    
    The key insight is that the array can only be sorted if it's a rotated version 
    of a sorted array. We find the smallest element and check if the array from 
    that point onward is non-decreasing. If yes, we return the index of the smallest 
    element as the number of operations needed.

Algorithms/Techniques:
    - Find minimum element index in the array
    - Validate that the array from that index is sorted in non-decreasing order
    - If valid, return index of minimum element, otherwise return -1

Time Complexity: O(n)
Space Complexity: O(1)
"""

def solve():
    n = int(input())
    a = [int(x) for x in input().split()]
    fm = 0
    # Find index of the minimum element
    for i in range(n):
        if a[i] < a[fm]:
            fm = i
    # Check if the array from the minimum element onward is non-decreasing
    for i in range(fm + 1, n):
        if a[i] < a[i - 1]:
            print(-1)
            return
    print(fm)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/
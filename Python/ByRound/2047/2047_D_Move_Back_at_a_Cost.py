# Problem: CF 2047 D - Move Back at a Cost
# https://codeforces.com/contest/2047/problem/D

"""
D. Move Back at a Cost

Purpose:
This code aims to find the lexicographically smallest array possible by performing operations where an element can be incremented and moved to the end of the array.
The strategy involves using a stack to simulate the process, keeping track of elements that need to be "moved back" (incremented), and finally sorting those elements to achieve a lexicographically minimal result.

Algorithms/Techniques:
- Stack-based simulation to handle the movement of elements
- Greedy approach: when an element is smaller than the top of the stack, it's moved out (to be incremented)
- Sorting the elements that were moved back for minimal lexicographical order

Time Complexity: O(n log n) due to sorting the "no" array in the worst case.
Space Complexity: O(n) for storing the stack and auxiliary arrays.

"""

import sys

input = sys.stdin.readline


def fn(n, a):
    stk = []  # Stack to simulate operations
    no = []   # List to store elements that will be incremented and moved
    for i in a:
        # While current element is smaller than stack top, move the top (increment it)
        while stk and i < stk[-1]:
            no.append(stk.pop() + 1)  # Increment and add to no list
        stk.append(i)  # Add current element to stack
    
    if not no:  # If no elements were moved, return original stack
        return stk
    
    no.sort()  # Sort to make the result lexicographically minimal
    ans = []
    for i in stk:
        if i <= no[0]:
            ans.append(i)
        else:
            no.append(i + 1)  # If value is greater than smallest in no, increment and add
    return ans + sorted(no)


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(*fn(n, a))


# https://github.com/VaHiX/codeForces/
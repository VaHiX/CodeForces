# Problem: CF 1691 D - Max GEQ Sum
# https://codeforces.com/contest/1691/problem/D

"""
Algorithm: Max GEQ Sum
Techniques: Prefix Sum, Next Greater Element, Two Passes

Time Complexity: O(n) - Each element is pushed and popped from the stack at most once, and all operations are linear.
Space Complexity: O(n) - For prefix sum array, next greater element array, and stack storage.

This solution checks whether for every subarray [i, j], the maximum element in that subarray is greater than or equal to the sum of all elements in that subarray. 
It uses a two-pass approach:
1. First pass: Check if the condition holds for original array.
2. Second pass: Check if condition holds for reversed array.
If both passes pass, then the answer is YES, otherwise NO.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip("\r\n")


def check(a):
    # Compute prefix sums to quickly calculate subarray sums
    pre = [0]
    for x in a:
        pre += [pre[-1] + x]

    # Find next greater element for each index
    nge = list(range(n))  # Initialize to array of indices
    st = [n - 1]  # Stack to hold indices
    for i in reversed(range(n)):
        # While stack is not empty and current element is greater than top of stack
        while st and a[i] > a[st[-1]]:
            st.pop()  # Pop elements from stack
        if st:
            nge[i] = st[-1]  # Set next greater index
        st += [i]  # Push current index to stack

    # For each element, check if the max in the subarray (from i to nge[i]) 
    # is less than the sum of that subarray
    for i, x in enumerate(a):
        if a[nge[i]] < pre[nge[i] + 1] - pre[i]:
            return False  # Condition violated

    return True


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    # Check both original and reversed arrays
    if check(a) and check(a[::-1]):
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/
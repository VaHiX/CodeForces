# Problem: CF 1991 C - Absolute Zero
# https://codeforces.com/contest/1991/problem/C

"""
Code Purpose:
This code solves the "Absolute Zero" problem where we aim to reduce all elements of an array to zero 
using at most 40 operations. Each operation involves choosing a value x and replacing each array element 
a[i] with |a[i] - x|. The key insight is to use bit manipulation and specific sequences of x values to 
achieve the goal efficiently.

Algorithms/Techniques:
- Bit manipulation and greedy approach
- Use of powers of 2 to reduce array elements step-by-step
- Special handling for odd and even cases based on parity of elements

Time Complexity:
O(n) per test case, where n is the size of the array. This is due to the operations on the set of unique elements.

Space Complexity:
O(n) for storing the unique elements in the set.
"""

for s in [*open(0)][2::2]:
    s = {int(x) % 2 for x in s.split()}  # Get set of parities (even/odd) of all elements
    print(
        *(s > {0} and [-1] or [31, *(1 << i for i in range(29, -1, -1)), s.pop() ^ 1])
    )


# https://github.com/VaHiX/CodeForces/
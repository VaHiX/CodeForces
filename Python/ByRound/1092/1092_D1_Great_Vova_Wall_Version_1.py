# Problem: CF 1092 D1 - Great Vova Wall (Version 1)
# https://codeforces.com/contest/1092/problem/D1

"""
D1. Great Vova Wall (Version 1)
Algorithms/Techniques: Simulation with Stack
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves determining if a wall can be made uniform using two types of operations:
1. Place a vertical brick (increase height by 2) on any part.
2. Place a horizontal brick between two adjacent parts of equal height (increase both by 1).

Key insight:
- Horizontal bricks can only be placed if adjacent heights are equal.
- Vertical bricks can be placed anywhere, but we simulate the effect of reducing differences using a stack-based approach:
    - We represent each part as 0 if even, 1 if odd.
    - Adjacent equal values can be "merged" (popped from stack), effectively simulating horizontal brick placement.
    - If final stack size is 1 or 0, it implies all parts can be made equal via vertical bricks and horizontal pairs.
"""

n = eval(input())
l = [int(x) & 1 for x in input().split()]  # Convert height to parity (0 for even, 1 for odd)
st = []
st.append(l[0])  # Initialize stack with first element

for i in range(1, n):
    if len(st) and st[-1] == l[i]:  # If top of stack equals current element
        st.pop()  # Remove from stack (simulate horizontal brick operation)
    else:
        st.append(l[i])  # Add to stack

if len(st) >= 2:  # Two or more elements remain => not all can be made equal
    print("NO")
else:
    print("YES")


# https://github.com/VaHiX/codeForces/
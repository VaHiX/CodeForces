# Problem: CF 1098 A - Sum in the tree
# https://codeforces.com/contest/1098/problem/A

"""
A. Sum in the tree
Algorithms/Techniques: Tree traversal, greedy assignment, validation of constraints.

Time complexity: O(n)
Space complexity: O(n)

The problem involves reconstructing values on a tree based on given prefix sums from root.
We process nodes in two passes:
1. Forward pass: for each node, if it's not -1 and its parent is -1 or larger than current,
   set parent value to current node's value.
2. Backward pass: for each node, ensure validity of values and accumulate sum of differences.

"""

n = int(input())
p = [-1] + list(map(int, input().split()))  # p[i] is the parent of node i
s = list(map(int, input().split()))         # s[i] is the prefix sum for node i, -1 if erased
ans = 0

# Forward pass: propagate values to parents where needed
for i in range(1, n):
    if s[i] != -1 and (s[p[i] - 1] == -1 or s[p[i] - 1] > s[i]):
        s[p[i] - 1] = s[i]

# Backward pass: validate and compute the sum of minimum values
for i in range(n - 1, 0, -1):
    if s[i] != -1:
        if s[p[i] - 1] > s[i]:
            ans = -1
            break
        else:
            ans += s[i] - s[p[i] - 1]

print(ans + s[0] if ans != -1 else -1)


# https://github.com/VaHiX/codeForces/
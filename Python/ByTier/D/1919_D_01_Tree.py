# Problem: CF 1919 D - 01 Tree
# https://codeforces.com/contest/1919/problem/D

"""
Purpose: Determine if a given array of distances from root to leaves in DFS order
         can correspond to a valid complete binary tree where edges have weights 0 or 1.

Algorithms/Techniques: 
    - Stack-based validation of DFS order compatibility with binary tree structure
    - Monotonic stack to track the depth of the most recent leaf processed in the current path

Time Complexity: O(n) for each test case, where n is the number of leaves.
Space Complexity: O(n) for the stack storage in the worst case.

"""
import sys

sys.setrecursionlimit(2147483647)
MOD = 1000000007
input = sys.stdin.readline


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    s = [a[0]]  # Initialize stack with the first element of array
    for i in range(1, n):
        # While the last element in stack is greater than current depth and
        # can be reduced by 1 to match current depth, pop it (backtrack in DFS)
        while len(s) > 1 and s[-1] > a[i] and s[-1] - 1 == s[-2]:
            s.pop()
        # If the last element in stack is less than the current depth, 
        # we must extend the path (push new depth)
        if s[-1] < a[i]:
            s.append(a[i])
        # If the last element in stack is one more than the current depth,
        # update the last element (i.e., move to sibling in DFS)
        elif s[-1] - 1 == a[i]:
            s[-1] = a[i]
        # If they are equal and the depth is 0, it's invalid since root cannot have a sibling
        elif s[-1] == a[i]:
            if a[i] == 0:
                print("NO")
                return
        # Otherwise, it's an invalid sequence
        else:
            print("NO")
            return
    # After processing all elements, prune the stack by removing redundant depths
    while len(s) > 1 and s[-1] - 1 == s[-2]:
        s.pop()
    # If we end up with exactly one depth of 0, the sequence is valid
    if len(s) == 1 and s[0] == 0:
        print("YES")
    else:
        print("NO")


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/
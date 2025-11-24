# Problem: CF 1600 A - Weights
# https://codeforces.com/contest/1600/problem/A

"""
Code Purpose:
This code solves the problem of arranging weights on a balance scale such that the sequence of
left (L) and right (R) placements satisfies a given string S. The strategy uses a greedy approach:
- Sort weights in ascending order
- For each step, place the heaviest remaining weight on the side that will satisfy the requirement
  in S; if previous and current requirements are the same, we place from a pointer accordingly
- Use a permutation array P to determine which weight goes in which position
- Output the weights with their corresponding sides in order

Algorithms/Techniques:
Greedy algorithm, sorting, two-pointer technique

Time Complexity:
O(N log N) due to sorting of weights

Space Complexity:
O(N) for storing the array P, S, and Ans

"""

n = int(input())
A = list(map(int, input().split()))
A.sort()  # Sort weights in ascending order
S = input()
# Convert string S to 0 (L) and 1 (R) for easier handling
S = [0 if S[i] == "L" else 1 for i in range(n)]
P = [-1] * n  # Array to store the correct index of weight to be used
cor = S[-1] + n + 1  # Correction factor for cycle in output
a = 0  # Left pointer
b = n - 1  # Right pointer

# Traverse backwards to assign weights to positions based on changes in S
for c in range(n - 1, -1, -1):
    if S[c - 1] != S[c]:  # If the current requirement differs from the previous
        P[b] = c  # Assign to right pointer
        b -= 1
    else:  # If requirements are same
        P[a] = c  # Assign to left pointer
        a += 1

# Build answer array with (index, weight, side)
Ans = [(P[i], A[i], (i + cor) % 2) for i in range(n)]
Ans.sort()  # Sort to get output in correct order

# Print each weight and side
for ans in Ans:
    print(ans[1], "R" if ans[2] else "L")


# https://github.com/VaHiX/CodeForces/
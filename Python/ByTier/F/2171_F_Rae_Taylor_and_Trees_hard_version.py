# Problem: CF 2171 F - Rae Taylor and Trees (hard version)
# https://codeforces.com/contest/2171/problem/F

"""
Algorithm: Tree Construction from Permutation
Purpose: Determine if a tree can be constructed such that for every edge (u,v), u appears before v in the given permutation.
Technique: 
    - Precompute minimum prefix and maximum suffix arrays
    - For each adjacent pair in the permutation, determine valid edges based on min/max constraints
    - Check if it's possible to create a valid spanning tree with the given constraints

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Approach:
    1. Compute prefix minimums and suffix maximums
    2. For each consecutive pair in the permutation, check if a valid edge can be formed
    3. If valid, add an edge to the result
    4. Output the edges if possible

Implementation Details:
    - Use prefix min array to track minimum value seen so far from left
    - Use suffix max array to track maximum value seen so far from right
    - Check constraint that for edge (u,v), u < v in perm and u comes before v in perm
"""

def thing(arr):
    # Precompute prefix minimums (minimum value from start to index i)
    minns = [arr[0]]
    maxxs = []
    maxx = 0
    edges = []

    for i in arr:
        minns.append(min(i, minns[-1]))

    minns.pop(0)  # Remove first element to align with indices

    # Precompute suffix maximums (maximum value from index i to end)
    for i in range(len(arr) - 1, -1, -1):
        maxx = max(maxx, arr[i])
        maxxs.append(maxx)

    maxxs.reverse()  # Reverse to align with original array indices

    # Process pairs of adjacent elements in the permutation
    for i in range(len(arr) - 1):
        # If current prefix minimum exceeds next suffix maximum, impossible to form valid tree
        if minns[i] > maxxs[i + 1]:
            print("No")
            return
        else:
            # Determine which element should be parent based on conditions
            if arr[i + 1] > minns[i]:
                # Connect arr[i+1] with minns[i]
                edges.append((arr[i + 1], minns[i]))
            elif maxxs[i + 1] > arr[i]:
                # Connect maxxs[i+1] with arr[i]
                edges.append((maxxs[i + 1], arr[i]))
            else:
                # Connect maxxs[i+1] with minns[i] 
                edges.append((maxxs[i + 1], minns[i]))

    print("Yes")

    # Output all edges in the constructed tree
    for i in edges:
        print(*i)


testcases = range(int(input()))

for case in testcases:
    input()
    thing([int(i) for i in input().split()])


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1970 B2 - Exact Neighbours (Medium)
# https://codeforces.com/contest/1970/problem/B2

"""
Code Purpose:
This code solves the problem of placing n wizards' houses on an n×n grid such that:
1. Each wizard's house is at a specific distance a_i from their designated house.
2. No two wizards share the same column (i.e., x-coordinates are unique).
3. The distance is measured using Manhattan distance.

Algorithm:
- The approach is greedy and constructs the solution column by column.
- Since a_1 = 0, the first wizard's house is at the (1,1) position (we use 0-based indexing).
- For each wizard i (from 1 to n-1), we calculate where their house should be placed based on the previous positions and the required distance.
- We determine which wizard the i-th wizard should visit using a lookup table.

Time Complexity:
- O(n) - Single pass through the array.

Space Complexity:
- O(n) - For storing positions and relations arrays.
"""

n = int(input())
dists = list(map(int, input().split(" ")))

pos = [0]  # Position of the first wizard's house (0-based index)
relation = [1]  # For the first wizard, it is its own house

# Loop through remaining wizards
for i in range(1, n):
    if dists[i] == 0:
        # If distance is 0, this wizard's house is at the same location as their own house
        # Assign column 0 and update relation
        pos.append(0)
        relation.append(i + 1)
        continue

    # Calculate the previous column index with a distance constraint
    prev_col = max(0, i - dists[i])
    # Get the row of the previous column
    prev_row = pos[prev_col]
    # Compute the row of the current wizard's house based on Manhattan distance
    pos.append(prev_row + dists[i] - (i - prev_col))
    # Assign the relation (the wizard whose house is to be visited)
    relation.append(prev_col + 1)

# Output the result
print("YES")
for i, p in enumerate(pos):
    print(f"{i +1 } {p +1 }")

print(" ".join(map(str, relation)))


# https://github.com/VaHiX/CodeForces/
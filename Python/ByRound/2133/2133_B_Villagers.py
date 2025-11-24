# Problem: CF 2133 B - Villagers
# https://codeforces.com/contest/2133/problem/B

"""
Problem: Villagers
Purpose:
    Given n villagers with initial grumpiness values, Steve wants to make every villager friends with every other one.
    He can merge two villagers by giving them max(g_i, g_j) emeralds, and their grumpiness decreases by min(g_i, g_j).
    Each merge operation creates a friendship between the two villagers. 
    Goal: Find minimum total emeralds needed to make all villagers friends (i.e., one connected component).

Algorithm:
    - Sort the grumpiness array.
    - To minimize emeralds spent, we should always merge the two smallest remaining grumpiness values.
    - However, a key insight is that we want to minimize sum of max(g_i, g_j) over all merges.
    - The optimal strategy is to pick the largest elements in pairs (since they contribute most to cost),
      and only keep one element from each pair after merging.
    - Therefore, sorting the array and taking every second element from the end (in reverse order)
      gives us the minimal sum of emeralds.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(1) if we don't count input storage, otherwise O(n).

Techniques:
    - Greedy approach with sorting
    - Strategy: select pairs of maximal elements in reverse order after sorting
"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())           # Read number of villagers
    a = list(map(int, input().split()))  # Read grumpiness values
    a.sort()                   # Sort the grumpiness array
    sm = 0                     # Initialize total emeralds needed
    # Iterate from last element to first, taking every second element (largest elements)
    for i in range(n - 1, -1, -2):
        sm += a[i]             # Add largest unpaired grumpiness value
    print(sm)                  # Output result


# https://github.com/VaHiX/codeForces/
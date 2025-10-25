# Problem: CF 1900 A - Cover in Water
# https://codeforces.com/contest/1900/problem/A

"""
Problem: A. Cover in Water
Algorithm/Technique: Greedy approach
Time Complexity: O(n), where n is the length of the string s
Space Complexity: O(1), only using a few variables for counting

The problem requires us to determine the minimum number of actions of type 1 
(i.e., placing water in an empty cell) needed to fill all empty cells. 

Key insight:
- When a cell has water on both its left and right neighbors, it gets filled.
- For a group of consecutive empty cells ("..."), we can greedily place the minimum number of water sources such that each source covers at most 2 consecutive empty cells.
- However, if there are 3 or more consecutive empty cells, the optimal strategy is to place water in every third cell.

Approach:
1. If a string contains "..." (three consecutive dots), we must place 2 water sources somewhere among those cells.
   - This is because if we split three empty cells, it's always possible to fill them with at most 2 sources.
2. Otherwise, count all the isolated dots (".").
"""

for _ in range(int(input())):  # Process multiple test cases
    a = int(input())  # Read number of cells
    s = input()  # Read string representation of cells
    
    if "..." in s:  # If there are 3 or more consecutive empty cells
        print(2)  # We need at most 2 actions to fill them
    else:
        print(s.count("."))  # Count total number of empty cells (all isolated)


# https://github.com/VaHiX/codeForces/
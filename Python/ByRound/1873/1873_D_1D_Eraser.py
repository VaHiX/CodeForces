# Problem: CF 1873 D - 1D Eraser
# https://codeforces.com/contest/1873/problem/D

"""
Algorithm: Greedy
Approach:
- Traverse the string from left to right.
- When we encounter a 'B', we must perform an operation to cover it.
- To minimize operations, we greedily place each operation as far right as possible, 
  i.e., starting at the first 'B' we find, and covering k cells.
- This ensures maximum overlap and minimum operations.

Time Complexity: O(n) - We traverse the string once per test case.
Space Complexity: O(1) - Only using a few variables, no extra space apart from input.
"""

def erase(list, k, n):
    r = 0  # Count of operations
    i = 0  # Pointer to traverse the string
    while i < n:
        if list[i] == "B":  # If current cell is black
            r += 1  # Increment operation count
            i += k  # Skip k cells (as they are now covered)
        else:
            i += 1  # Move to next cell
    return r


t = int(input())
for i in range(t):
    n, k = map(int, input().split())
    list = input()
    print(erase(list, k, n))


# https://github.com/VaHiX/CodeForces/
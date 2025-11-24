# Problem: CF 1705 C - Mark and His Unfinished Essay
# https://codeforces.com/contest/1705/problem/C

"""
Purpose: Solve the problem of finding specific characters in a dynamically growing string after multiple copy-paste operations.
Algorithm/Technique: 
    - Store the start of each copy-paste operation in a list along with the original string length.
    - For each query, backtrack through the operations to find the original position of the character in the initial string.
Time Complexity: O(c * q) in worst case per test case where c is the number of operations and q is number of queries.
Space Complexity: O(c) for storing the operation start positions.
"""

for _ in range(int(input())):
    n, c, q = map(int, input().split())  # Read n, c, q
    s = input()  # Read initial string
    L = []  # Store the start positions of each operation
    for i in range(c):
        l, r = map(int, input().split())  # Read operation range
        L.append((n, l))  # Store (length before operation, start index of substring to copy)
        n = n + r - l + 1  # Update the new length after this operation
    for i in range(q):
        k = int(input())  # Read query index (1-based)
        # Backtrack through operations to find original position
        for j in range(-1, -1 - c, -1):  # Iterate backwards through operations
            if k > L[j][0]:  # If k is beyond the length before this operation
                k = k - L[j][0] + L[j][1] - 1  # Adjust k to point to original string
        print(s[k - 1])  # Print the character at adjusted k (convert to 0-based index)


# https://github.com/VaHiX/CodeForces/
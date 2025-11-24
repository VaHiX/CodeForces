# Problem: CF 1926 B - Vlad and Shapes
# https://codeforces.com/contest/1926/problem/B

"""
Code Purpose:
This code determines whether a given binary grid represents a square or a triangle made of '1's.
The algorithm works by counting the number of '1's in each row that contains at least one '1'.
If all non-empty rows have the same count of '1's, it's a square. Otherwise, it's a triangle.

Algorithms/Techniques:
- Row-wise counting of '1's
- Set-based comparison to detect uniformity
- Simple conditional logic to classify shape

Time Complexity:
O(n^2) where n is the size of the grid. This is because we iterate through all n rows and each row has n characters.

Space Complexity:
O(n) for storing the counts of '1's in non-empty rows.
"""

for _ in range(int(input())):
    n = int(input())
    l = []
    for i in range(n):
        s = input()
        a = s.count("1")  # Count number of 1s in current row
        if a != 0:
            l.append(a)  # Only store counts for rows that have at least one 1
    if len(set(l)) == 1:  # If all counts are the same, it's a square
        print("SQUARE")
    else:  # Otherwise, it's a triangle
        print("TRIANGLE")


# https://github.com/VaHiX/CodeForces/
# Problem: CF 2068 A - Condorcet Elections
# https://codeforces.com/contest/2068/problem/A

"""
Algorithm: Condorcet Elections
Techniques: Graph construction, topological sorting, cycle detection

Time Complexity: O(n^2 + m) where n is number of candidates and m is number of defeat relations.
Space Complexity: O(n^2) for storing the graph and adjacency lists.

This code determines whether a set of Condorcet election outcomes can be realized
by constructing a valid ranking (permutation) of candidates such that each known
defeat relationship holds. It uses topological sorting to detect cycles and generate
a consistent voting order.
"""

n, m = map(int, input().split())
print("YES")
print(2 * m)  # We'll print 2*m votes to satisfy all the conditions
for i in range(m):
    a, b = map(int, input().split())  # Read pair of candidates where a defeats b
    str1 = str(a) + " " + str(b)  # Build first vote: a comes before b
    str2 = ""  # Build second vote with reversed order
    for j in range(1, n + 1):  # For all other candidates (excluding a and b)
        if j == a or j == b:
            continue
        str2 = str(j) + " " + str2  # Add to end of str2 (reverse order)
        str1 += " " + str(j)  # Add to end of str1 (forward order)
    print(str1)  # Print first vote line
    print(str2 + str(a) + " " + str(b))  # Print second vote line with proper formatting


# https://github.com/VaHiX/codeForces/
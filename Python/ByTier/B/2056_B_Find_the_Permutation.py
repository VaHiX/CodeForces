# Problem: CF 2056 B - Find the Permutation
# https://codeforces.com/contest/2056/problem/B

"""
B. Find the Permutation
Algorithm: 
    - The graph is constructed such that there's an edge between vertices p[i] and p[j] if and only if p[i] < p[j].
    - Given the adjacency matrix of this graph, we need to reconstruct the permutation p.
    
Approach:
    - For each row (i), we count how many '1' bits are in the prefix up to column i.
      This gives us how many elements before i have a value less than i in the final sequence.
    - Inserting at that index effectively places element i+1 into the correct position of the permutation.

Time Complexity: O(n^2)
Space Complexity: O(n)

Input:
Each test case contains n, followed by an n x n adjacency matrix.
Output:
Reconstructed permutation p as a space-separated list.

Example:
For input:
5
00101
00101
11001
00001
11110
Output:
4 2 1 3 5
"""

from sys import stdin

input = stdin.readline
for _ in range(int(input())):
    for i in range([int(input()), arr := []][0]):  # Read n, initialize empty array arr
        arr.insert(input()[:i].count("1"), i + 1)   # Insert i+1 at index equal to count of '1's in prefix
    print(*arr)                                     # Print the permutation


# https://github.com/VaHiX/codeForces/
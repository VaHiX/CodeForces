# Problem: CF 1918 B - Minimize Inversions
# https://codeforces.com/contest/1918/problem/B

"""
Minimize Inversions

Algorithm:
The problem asks us to minimize the total number of inversions in two permutations a and b,
by swapping elements at the same indices in both arrays any number of times.

Key Insight:
- An inversion in a permutation occurs when an element at a lower index is greater than an element at a higher index.
- Since we can perform swaps on matching indices in both arrays, we can essentially arrange both permutations to be as close to sorted as possible in terms of their relative order.
- To minimize inversions, we want to arrange elements such that for any index i, a[i] and b[i] are as "aligned" as possible in their sorted order.

Approach:
1. Create a mapping c such that c[a[i] - 1] = b[i]. This effectively maps the positions of values in a to values in b.
2. Reconstruct the arrays a' and b' so that a' = [1, 2, ..., n] (sorted), and b' is derived based on the mapping.
3. Output these two permutations.

Time Complexity: O(n)
Space Complexity: O(n)
"""

def solve(a, b, n):
    c = [0 for i in range(n)]  # Create a list to store mapping from a to b
    for i in range(n):         # For each index in the arrays
        c[a[i] - 1] = b[i]     # Map value a[i] to b[i] (using 0-based indexing)
    print(" ".join(list(map(str, list(range(1, n + 1))))))     # Print sorted array [1, 2, ..., n]
    print(" ".join(list(map(str, c))))          # Print the mapped array


def question():
    n = int(input())           # Read length of array
    a = list(map(int, input().split(" ")))    # Read array a
    b = list(map(int, input().split(" ")))    # Read array b
    solve(a, b, n)             # Solve for current test case


t = int(input())               # Read number of test cases
for j in range(t):             # Iterate through each test case
    question()                 # Process each test case


# https://github.com/VaHiX/CodeForces/
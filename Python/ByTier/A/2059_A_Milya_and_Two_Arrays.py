# Problem: CF 2059 A - Milya and Two Arrays
# https://codeforces.com/contest/2059/problem/A

"""
Task: Determine if it's possible to rearrange array `a` such that the sum array `c = a + b` has at least 3 distinct elements.

Approach:
- For each test case, we compute the number of unique elements in both arrays `a` and `b`.
- If the product of unique elements in `a` and `b` is at least 3, then it's possible to create at least 3 distinct sums.
- This works because if both arrays have at least 2 unique elements, there are enough combinations to generate 3 distinct values when summing.

Time Complexity: O(n) per test case, where n is the length of the arrays. This is due to converting arrays to sets and calculating their lengths.
Space Complexity: O(n) per test case for storing the sets of unique elements.

Algorithms/Techniques: Set operations, greedy approach based on uniqueness.
"""

for _ in range(int(input())):  # Process multiple test cases
    n = int(input())  # Read size of arrays
    a = len(set(input().split()))  # Get count of unique elements in array a
    b = len(set(input().split()))  # Get count of unique elements in array b
    print("YES" if a * b >= 3 else "NO")  # Output result based on condition


# https://github.com/VaHiX/codeForces/
# Problem: CF 2040 A - Game of Division
# https://codeforces.com/contest/2040/problem/A

"""
Code Purpose:
This code solves the "Game of Division" problem where two players take turns choosing indices from an array.
The first player wants to choose an index such that the absolute difference between the selected element and any other element is NOT divisible by k.
The goal is to determine if the first player can win and, if so, which index to choose.

Algorithm/Techniques:
- Brute-force approach: For each element in the array, check if there exists at least one other element such that their difference is NOT divisible by k.
- Uses Python's `all()` function combined with a generator expression to efficiently validate the condition.
  
Time Complexity:
O(n^2) where n is the length of the array. For each element, we check all other elements (n-1), leading to a quadratic complexity.

Space Complexity:
O(1) excluding the input storage. The algorithm uses only a constant amount of extra space.
"""

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    # Iterate through each index i
    for i in range(n):
        # Check if for current i, all differences (a[j] - a[i]) where j != i are divisible by k
        # If not all are divisible, then there exists at least one j such that (a[j] - a[i]) % k != 0
        # Which means first player wins by choosing index i
        if all((a[j] - a[i]) % k for j in range(n) if i != j):
            print("YES")
            print(i + 1)  # Output 1-based index
            break
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/
# Problem: CF 1873 B - Good Kid
# https://codeforces.com/contest/1873/problem/B

"""
Algorithm: Greedy Approach
Time Complexity: O(n), where n is the number of digits. We iterate through the array twice: once to find the minimum and once to calculate the product.
Space Complexity: O(n), where n is the number of digits. We store the list of digits and modify it in place.

The approach is greedy: to maximize the product, we should add 1 to the smallest digit in the array.
This ensures that the increase in product is maximized.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for aa in range(int(input())):
    n = int(input())
    li = list(map(int, input().split()))
    x = min(li)  # Find the smallest digit
    li.remove(x)  # Remove the smallest digit
    li.append(x + 1)  # Add 1 to the smallest digit and append it back
    p = 1
    for i in range(n):
        p *= li[i]  # Calculate the product of all digits
    print(p)


# https://github.com/VaHiX/CodeForces/
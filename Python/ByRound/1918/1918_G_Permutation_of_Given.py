# Problem: CF 1918 G - Permutation of Given
# https://codeforces.com/contest/1918/problem/G

"""
Purpose: 
    This code solves the problem of finding a permutation of given length n such that 
    when each element is replaced by the sum of its neighbors, the resulting array 
    is a permutation of the original array.

Algorithms/Techniques:
    - Constructive algorithm with pattern-based array generation
    - Handle special cases for n = 3 and n = 5
    - Use a base pattern and extend it for even and odd n

Time Complexity: O(n)
    - The algorithm constructs the answer array in linear time by appending elements
    - A single loop runs up to n/2 times, leading to linear growth

Space Complexity: O(n)
    - The output array 'ans' stores n elements
    - Additional variables use constant space

"""

import sys

input = sys.stdin.readline
n = int(input())
if n in [3, 5]:
    print("NO")
    sys.exit()
ans = [1, 2]
if n % 2:  # If n is odd, append a specific pattern to the base array
    ans += [-3, 2, 4, -5, -2]
while len(ans) < n:  # Extend the array until it reaches size n
    a = ans[-2]
    b = ans[-1]
    ans.append(-b)       # Add the negation of last element
    ans.append(a - b)    # Add the difference of last two elements
print("YES")
print(*ans)


# https://github.com/VaHiX/CodeForces/
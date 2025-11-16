# Problem: CF 1975 C - Chamo and Mocha's Array
# https://codeforces.com/contest/1975/problem/C

"""
Algorithm: 
- For arrays of length 2, the result is simply the minimum of the two elements.
- For arrays of length > 2, we iterate through all possible triplets (l, l+1, l+2) 
  and find the median of each triplet. The maximum of these medians is the answer.
  
Time Complexity: O(n), where n is the length of the array. We iterate through the array once.
Space Complexity: O(1), as we use only a constant amount of extra space.
"""

from sys import stdin

input = stdin.readline

for t in range(int(input())):

    n = int(input())

    l = list(map(int, input().split()))
    if n == 2:
        print(min(l[0], l[1]))
        continue

    temp = 0
    for i in range(n - 2):  # Iterate through all triplets
        lis = [l[i], l[i + 1], l[i + 2]]  # Extract triplet
        lis.sort()  # Sort to find median
        temp = max(temp, lis[1])  # lis[1] is the median for sorted triplet of size 3
    print(temp)


# https://github.com/VaHiX/CodeForces/
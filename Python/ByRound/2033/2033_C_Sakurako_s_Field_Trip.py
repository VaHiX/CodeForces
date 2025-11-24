# Problem: CF 2033 C - Sakurako's Field Trip
# https://codeforces.com/contest/2033/problem/C

"""
C. Sakurako's Field Trip
Algorithms/Techniques: Greedy approach with two-pointer style swaps

Time Complexity: O(N) per test case, where N is the length of the array.
Space Complexity: O(1) extra space (not counting input storage).

The problem asks to minimize the number of adjacent equal elements by swapping
elements at symmetric positions (i and N-i+1). The key insight is to process
the first half of the array and swap elements with their counterparts from the
end, aiming to reduce adjacent duplicates.
"""

import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N = int(input())
    A = list(map(int, input().split()))
    # Iterate through the first half of the array to perform swaps
    for i in range(1, N // 2):
        # If current element equals its previous one OR the symmetric element equals 
        # the next one in reverse order, swap them
        if A[i] == A[i - 1] or A[N - 1 - i] == A[N - i]:
            A[i], A[N - 1 - i] = A[N - 1 - i], A[i]
    result = 0
    # Count the number of adjacent equal elements
    for i in range(1, N):
        if A[i] == A[i - 1]:
            result += 1
    print(result)


# https://github.com/VaHiX/codeForces/
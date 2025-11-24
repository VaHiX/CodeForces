# Problem: CF 1903 C - Theofanis' Nightmare
# https://codeforces.com/contest/1903/problem/C

"""
Code Purpose:
This code solves the problem of finding the maximum "Cypriot value" of dividing an array into non-empty subarrays.
The Cypriot value is defined as the sum over all subarrays of (index of subarray * sum of that subarray).
We use a greedy approach to determine the optimal division.

Algorithms/Techniques:
- Greedy algorithm
- Prefix sum technique

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(1), only using a few variables for computation.
"""

t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    ans = s = sum(arr)  # Initialize ans and s with total sum
    for i in range(1, n):
        s -= arr[i - 1]  # Subtract the previous element from running sum
        if s > 0:        # If the remaining sum is positive
            ans += s     # Add it to the answer (greedily extend the last subarray)
    print(ans)


# https://github.com/VaHiX/CodeForces/
# Problem: CF 2149 A - Be Positive
# https://codeforces.com/contest/2149/problem/A

"""
Task: Make the product of array elements strictly positive with minimum operations.
Algorithm/Techniques: Greedy approach
Time Complexity: O(n) per test case, where n is the length of the array
Space Complexity: O(1), only using a few variables for counting

The solution works as follows:
- Count zeros (each zero needs to be incremented to 1, so add 1 operation per zero)
- If there's an odd number of -1s, we need to make at least one of them positive,
  which requires 2 operations (turning -1 into 1). If even, no extra operations needed.
"""

t = int(input())
for i in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    res = a.count(0)  # Each zero contributes 1 operation to make it 1
    if a.count(-1) % 2 != 0:  # If odd number of -1s, need 2 more operations
        res += 2
    print(res)


# https://github.com/VaHiX/CodeForces/
# Problem: CF 2151 A - Incremental Subarray
# https://codeforces.com/contest/2151/problem/A

"""
Algorithm/Techniques: Simulation, Sorting, Subarray Matching

Time Complexity: O(n^2 + m*log(m)) where n is the maximum number written by James and m is the length of array a.
Space Complexity: O(n^2) for storing the generated array b.

This code simulates the pattern of numbers written by James on the blackboard.
The pattern follows a specific structure:
- First step: 1
- Second step: 1, 2
- Third step: 1, 2, 3
- ...
- nth step: 1, 2, ..., n

So the final array b is formed by concatenating these sequences.
For each test case:
1. Generate the array b of all numbers written by James (simulated).
2. Check if the input array a is sorted and has no duplicates.
3. If so, return n - a[-1] + 1 (number of valid subarray positions).
4. Otherwise, return 1 since we are guaranteed that a is a subarray of b.

The key insight is:
- For an array a = [1, 2, ..., k], if a is sorted and has no duplicates,
  then it will appear as a subarray starting at multiple positions.
  The count depends on the last element of a and how many such sequences begin with that element.
"""

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = sorted(a)
    # Check if a is already sorted and all elements are unique
    if a == b and len(set(a)) == len(a):
        # If array a forms an increasing sequence from 1 to some k,
        # then number of valid subarray positions = n - last_element + 1
        print(n - a[-1] + 1)
    else:
        # In all other cases, answer is always 1 since we are guaranteed to have at least one match
        print(1)


# https://github.com/VaHiX/CodeForces/
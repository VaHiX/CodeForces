# Problem: CF 1903 A - Halloumi Boxes
# https://codeforces.com/contest/1903/problem/A

"""
Problem: Halloumi Boxes

Task:
Determine if an array can be sorted using only reversals of subarrays of length at most k.

Algorithm/Techniques:
- Greedy approach with key insight:
  - If k > 1, we can perform any number of swaps by reversing subarrays of length up to k.
  - If k = 1, only adjacent swaps are allowed (like bubble sort).
  - A key observation: if the array is already sorted or k > 1, we can always sort it.

Time Complexity: O(n log n) per test case due to sorting step in worst-case scenario.
Space Complexity: O(n) for storing the input array and its sorted version.

Approach:
- For each test case:
  - If k > 1 or the array is already sorted, output YES
  - Otherwise, output NO
"""

_t = int(input())
for _ in range(_t):
    n, k = map(int, input().split())  # Read n (number of boxes) and k (max reverse length)
    a = list(map(int, input().split()))  # Read the array of box numbers
    
    # Check if sorting is possible:
    # If k > 1, we can sort using multiple reverses of size up to k.
    # If array is already sorted, no action needed.
    print("YES" if k > 1 or a == list(sorted(a)) else "NO")


# https://github.com/VaHiX/codeForces/
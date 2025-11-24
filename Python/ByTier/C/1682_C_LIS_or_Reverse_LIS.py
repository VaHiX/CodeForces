# Problem: CF 1682 C - LIS or Reverse LIS?
# https://codeforces.com/contest/1682/problem/C

"""
Purpose: 
    This code computes the maximum possible beauty of an array after rearranging its elements.
    Beauty is defined as min(LIS(a), LIS(a')), where a' is the reverse of a.
    The key insight is that to maximize beauty, we want to balance the LIS of the array and its reverse.
    
    Approach:
    - Count the frequency of each element in the array.
    - For each unique element, we can use at most 2 elements to form a subsequence.
      - If frequency is 1, we can use 1 element.
      - If frequency is 2 or more, we can use 2 elements.
    - The total number of such pairs contributes to the maximum possible LIS (and its reverse).
    - Final answer is derived from total pairs divided by 2 to account for double counting.

Algorithms/Techniques:
    - Frequency counting using dictionary
    - Greedy approach to maximize LIS by balancing usage of elements

Time Complexity: O(n) where n is the length of the array
Space Complexity: O(n) for storing frequency map
"""

for i in range(int(input())):
    n = input()
    d = {}
    for j in list(map(int, input().split())):
        d[j] = d.get(j, 0) + 1
    ans = 1
    for j in d:
        ans += min(2, d[j])  # Add at most 2 for each unique element
    print(ans // 2)  # Divide by 2 to get final answer


# https://github.com/VaHiX/CodeForces/
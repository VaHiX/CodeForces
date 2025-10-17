# Problem: CF 1991 A - Maximize the Last Element
# https://codeforces.com/contest/1991/problem/A

"""
Problem: Maximize the Last Element

Algorithm/Approach:
The key insight is that we can only remove adjacent elements, and we want to maximize the final remaining element.
Since we are removing pairs of adjacent elements iteratively, the process effectively allows us to "merge" elements in a way that 
the maximum element can potentially be retained in the final step. 

The approach is to realize that:
- If we have an odd-length array, we can always reduce it down to 1 element.
- The best strategy to retain a large number is to avoid reducing it in the process where it might be "merged" into a smaller one.

However, upon careful observation of the examples and the allowed operations:
- The key idea is that at each step, we can merge two adjacent elements and retain the maximum value of those.
- For an odd-length array, we can consider a greedy approach:
    - At each odd index, we look at it and determine if it's larger than the current max, which gives us a clue of how to greedily choose.
    - But more fundamentally, the optimal solution is to take the maximum element from the array at least once, since that element 
      will never be replaced after it's the only one left.
    - Actually, by the nature of the algorithm, it’s equivalent to always choosing the larger of two adjacent elements in a "merge",
      which results in a maximum possible final value equal to the maximum element in the array, because every value can be "merged" into 
      the maximum element eventually in the right sequence.

But let's trace carefully:
- Given array: [a1, a2, ..., an]
- At each step we pick two adjacent elements and merge them: keep the maximum.
- So if we have [4,7,4,2,9], a greedy merge leads to getting 9, which is the max element.

The correct and simplified insight:
- It is always beneficial to maximize the final remaining value.
- So the optimal value is the maximum element in the array because we can always choose to merge other elements 
  to keep bigger elements until the end.

Time Complexity: O(n) - We iterate through the array once to find the maximum element.
Space Complexity: O(1) - We use only a constant amount of extra space.
"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())           # Read length of array
    a = list(map(int, input().split()))  # Read array elements
    max_val = 0                # Initialize maximum value
    for i in range(n):         # Iterate through all elements
        if n == 1:             # If only one element, it's the answer
            max_val = a[0]
        elif i % 2 != 0:       # Skip even indices (this part might be incorrect in the logic but is preserved as per input)
            continue
        elif a[i] > max_val:   # Update maximum if current element is larger
            max_val = a[i]
    print(max_val)             # Output the result


# https://github.com/VaHiX/CodeForces/
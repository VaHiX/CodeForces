# Problem: CF 2128 B - Deque Process
# https://codeforces.com/contest/2128/problem/B

"""
B. Deque Process

Algorithm/Technique: Greedy with two pointers
Time Complexity: O(n)
Space Complexity: O(1) excluding output string

This problem involves choosing whether to remove the leftmost or rightmost element
from a permutation at each step, such that the resulting sequence is "good".
A good sequence avoids having 5 consecutive elements in strictly increasing or
decreasing order.

The approach uses a greedy two-pointer strategy:
- We maintain pointers at both ends (left and right).
- At each step, we compare the potential next elements based on the last two
  elements of our result array.
- We decide whether to pick left or right element to avoid forming bad subsequences.
"""

def appendToResult(result: list[str], reversed: bool | None):
    # Append "L" and "R" if reversed is False, otherwise "R" then "L"
    if not reversed:
        result.append("L")
        result.append("R")
    else:
        result.append("R")
        result.append("L")


def main(N: int, array: list[int]) -> str:
    # Start with initial elements in result
    result = ["L", "R"]
    left, right = 1, N - 2  # Pointers for current subarray being considered
    
    while left <= right:
        # Determine first and second elements based on last two operations
        first = array[left - 1] if result[-2] == "L" else array[right + 1]
        second = array[right + 1] if result[-1] == "R" else array[left - 1]
        
        # If difference is positive, favor the larger value
        if second - first > 0:
            # Choose based on which pointer has a larger element
            if array[left] >= array[right]:
                appendToResult(result, False)
            else:
                appendToResult(result, True)
        else:
            # If difference is non-positive, favor the smaller value
            if array[left] >= array[right]:
                appendToResult(result, True)
            else:
                appendToResult(result, False)
                
        # Handle the case when both pointers meet
        if left == right:
            result.pop()
            
        left += 1
        right -= 1
        
    return "".join(result)


for _ in range(int(input())):
    result = main(int(input()), list(map(int, input().split())))
    print(result)


# https://github.com/VaHiX/codeForces/
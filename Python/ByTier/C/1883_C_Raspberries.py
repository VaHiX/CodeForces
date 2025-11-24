# Problem: CF 1883 C - Raspberries
# https://codeforces.com/contest/1883/problem/C

"""
Algorithm: Raspberries
Purpose: Find minimum operations to make product of array divisible by k
Techniques: 
- Preprocessing: Count occurrences of each number in array
- Case analysis: Handle different values of k (2, 3, 4, 5) with specific divisibility rules
- Optimization: Direct lookup for small k values instead of complex recursion

Time Complexity: O(n) per test case where n is array size
Space Complexity: O(1) as we only use fixed-size arrays (10 or 13 elements max)
"""

import io
import os


def recurse(
    memo: list, index: int, k: int, current: int, modifications: int, result: list
):
    # If current product is divisible by k and we have fewer modifications, update result
    if current % k == 0 and modifications < result[0]:
        result[0] = modifications
    # Base case: reached end of possible indices
    if index == 13:
        return
    # If we have one instance of current index
    if memo[index] == 1:
        recurse(memo, index + 1, k, current * index, modifications, result)
        memo[index + 1] += 1
        memo[index] -= 1
        recurse(memo, index + 1, k, current, modifications + 1, result)
        memo[index + 1] -= 1
        memo[index] += 1
    # If we have more than one instance of current index
    elif memo[index] > 1:
        recurse(memo, index + 1, k, current * index * index, modifications, result)
        memo[index + 1] += 2
        memo[index] -= 2
        recurse(memo, index + 1, k, current, modifications + 2, result)
        memo[index + 1] -= 2
        memo[index] += 2
        memo[index + 1] += 1
        memo[index] -= 1
        recurse(memo, index + 1, k, current * index, modifications + 1, result)
        memo[index + 1] -= 1
        memo[index] += 1
    else:
        # No instances of current index, move to next
        recurse(memo, index + 1, k, current, modifications, result)


def solve2(nums: list, k: int):
    # Memo array to count occurrences of numbers from 1 to 13
    memo = [0 for _ in range(14)]
    for num in nums:
        memo[num] += 1
    result = [5]  # Initialize with maximum possible operations
    recurse(memo, 1, k, 1, 0, result)
    return result[0]


def solve(nums: list, k: int):
    # Memo array to count occurrences of numbers from 1 to 10
    memo = [0 for _ in range(11)]
    for num in nums:
        memo[num] += 1
    
    # Case when k = 2
    if k == 2:
        # Check if any even number exists
        if memo[2] or memo[4] or memo[6] or memo[8] or memo[10]:
            return 0  # Already divisible by 2
        else:
            return 1  # Need one operation to make one number even
    # Case when k = 3  
    elif k == 3:
        # Check if any multiple of 3 exists
        if memo[3] or memo[6] or memo[9]:
            return 0  # Already divisible by 3
        elif memo[2] or memo[5] or memo[8]:  # Check if we can make product divisible by 3
            return 1  # Need one operation to get to next multiple of 3
        else:
            return 2  # Need two operations
    # Case when k = 4
    elif k == 4:
        # If any multiple of 4 or two even numbers exist:
        if (
            memo[4]
            or memo[8]
            or memo[2] > 1
            or memo[6] > 1
            or memo[10] > 1
            or (memo[2] and memo[6])
            or (memo[2] and memo[10])
            or (memo[6] and memo[10])
        ):
            return 0  # Already divisible by 4
        elif (
            memo[3]
            or memo[7]
            or (memo[6] and memo[1])
            or (memo[5] and memo[2])
            or (memo[2] and memo[9])
            or (memo[1] and memo[10])
            or (memo[5] and memo[10])
            or (memo[6] and memo[9])
            or (memo[5] and memo[6])
            or (memo[10] and memo[9])
            or (memo[2] and memo[1])
        ):
            return 1  # Need one operation 
        elif (
            memo[2]
            or memo[6]
            or memo[10]
            or memo[1] > 1
            or memo[5] > 1
            or memo[9] > 1
            or (memo[1] and memo[5])
            or (memo[1] and memo[9])
        ) or (memo[5] and memo[9]):
            return 2  # Need two operations
        else:
            return 3  # Need three operations
    # Case when k = 5
    elif k == 5:
        # If any multiple of 5 exists
        if memo[5] or memo[10]:
            return 0  # Already divisible by 5
        elif memo[4] or memo[9]:  # One way to make it divisible by 5
            return 1  # Need one operation
        elif memo[3] or memo[8]:  # Another way
            return 2  # Need two operations
        elif memo[2] or memo[7]:  # Yet another way
            return 3  # Need three operations
        else:  # Need to find two numbers that make product divisible by 5
            return 4  # Need four operations


input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
cases = int(input())
for _ in range(cases):
    args = input().split()
    k = int(args[1])
    nums = [int(i) for i in input().split()]
    print(solve(nums, k))


# https://github.com/VaHiX/CodeForces/
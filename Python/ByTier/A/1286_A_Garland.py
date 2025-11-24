# Problem: CF 1286 A - Garland
# https://codeforces.com/contest/1286/problem/A

"""
Problem: Garland

Task:
Given a garland with n light bulbs, some of which are missing (marked as 0), 
we need to place the missing bulbs back such that the number of adjacent pairs 
with different parity (odd/even) is minimized.

Approach:
- Identify gaps between existing bulbs and determine how many even/odd numbers are available.
- Use greedy strategy with dynamic programming to compute minimum complexity.
- Use a two-pointer technique to calculate segments between known bulbs.
- Sort segments by length and greedily minimize complexity by replacing segments with fewer parity changes.

Time Complexity: O(n^2), where n is the number of bulbs. Sorting and nested traversals dominate.
Space Complexity: O(n), for storing lists of odd/even segment gaps.

Algorithms/Techniques:
1. Two-pointer technique to identify segments.
2. Greedy selection of segments to minimize parity changes.
3. Dynamic programming concept through greedy matching.
"""

n = int(input())
nums = list(map(int, input().split()))
if max(nums) == 0:
    print(1 if n > 1 else 0)
else:
    odd_count = n - n // 2
    even_count = n // 2
    for i in range(n):
        if nums[i]:
            if nums[i] % 2:
                odd_count -= 1
            else:
                even_count -= 1
    start_count = 0
    startEven = False
    for i in range(n):
        if nums[i]:
            startEven = nums[i] % 2 == 0
            idx1 = i
            break
        else:
            start_count += 1
    end_count = 0
    endEven = False
    for i in range(n - 1, -1, -1):
        if nums[i]:
            endEven = nums[i] % 2 == 0
            idx2 = i
            break
        else:
            end_count += 1
    ans = 2
    v = idx1
    odd_lst = []
    even_lst = []
    for i in range(idx1 + 1, idx2 + 1):
        if nums[i]:
            if (nums[i] - nums[v]) % 2:
                ans += 1
            else:
                if nums[i] % 2:
                    odd_lst.append(i - v - 1)
                else:
                    even_lst.append(i - v - 1)
                ans += 2
            v = i
    odd_lst.sort()
    even_lst.sort()
    for x in odd_lst:
        if odd_count >= x:
            odd_count -= x
            ans -= 2
    for x in even_lst:
        if even_count >= x:
            even_count -= x
            ans -= 2
    if startEven:
        if even_count >= start_count:
            even_count -= start_count
            ans -= 1
    else:
        if odd_count >= start_count:
            odd_count -= start_count
            ans -= 1
    if endEven:
        if even_count >= end_count:
            even_count -= end_count
            ans -= 1
    else:
        if odd_count >= end_count:
            odd_count -= end_count
            ans -= 1
    print(ans)


# https://github.com/VaHiX/codeForces/
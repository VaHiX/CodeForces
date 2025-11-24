# Problem: CF 2018 D - Max Plus Min Plus Size
# https://codeforces.com/contest/2018/problem/D

"""
D. Max Plus Min Plus Size

Purpose:
This code solves the problem of selecting a subset of elements from an array such that:
- No two adjacent elements are selected (i.e., a valid "red" selection with no adjacent reds)
- The score is computed as: max_value + min_value + count_of_selected_elements
- Find the maximum possible score over all valid selections.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) data structure for efficiently grouping segments of selected elements
- Sorting to process elements in descending order for greedy selection
- Segment-based tracking of odd/even counts and affected intervals

Time Complexity: O(n log n)
Space Complexity: O(n)

The algorithm processes the array elements in descending order of values, and uses union-find to group adjacent selected elements.
This allows for efficient updates when merging intervals and maintaining counters for max/min conditions.
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
inf = 10**18


def unionfind(group, root):
    son = root
    while group[root] != root:
        root = group[root]
    while son != root:
        temp = group[son]
        group[son] = root
        son = group[temp]
    return root


def main(t):
    n = int(input())
    arr = list(map(int, input().split()))
    nums = sorted(set(arr), reverse=True)
    dic = {}
    maxindex = []
    for i in range(n):
        if arr[i] == nums[-1]:
            maxindex.append(i)
    for num in nums:
        dic[num] = []
    for i in range(n):
        dic[arr[i]].append(i)
    group = [i for i in range(n)]
    visited = [False] * n
    count = [1] * n
    contain = [[0, 0] for _ in range(n)]
    effect = 0
    odds = 0
    ans = 0
    tot = 0

    def judge(index):
        if count[index] % 2 == 0 and max(contain[index]) > 0:
            return True
        if count[index] % 2 == 1 and contain[index][index % 2] > 0:
            return True
        return False

    for key in nums:
        tot += len(dic[key])
        for index in dic[key]:
            visited[index] = True
            odds += 1
            if key == nums[0]:
                contain[index][index % 2] += 1
                effect += 1
            # Merging with right neighbor
            if index + 1 < n and visited[index + 1]:
                if judge(index):
                    effect -= 1
                if count[index] % 2 == 1:
                    odds -= 1
                if judge(index + 1):
                    effect -= 1
                if count[index + 1] % 2 == 1:
                    odds -= 1
                count[index] += count[index + 1]
                contain[index][0] += contain[index + 1][0]
                contain[index][1] += contain[index + 1][1]
                group[index + 1] = index
                if judge(index):
                    effect += 1
                if count[index] % 2 == 1:
                    odds += 1
            # Merging with left neighbor
            if index - 1 >= 0 and visited[index - 1]:
                root = unionfind(group, index - 1)
                if judge(index):
                    effect -= 1
                if count[index] % 2 == 1:
                    odds -= 1
                if judge(root):
                    effect -= 1
                if count[root] % 2 == 1:
                    odds -= 1
                group[index] = root
                count[root] += count[index]
                contain[root][0] += contain[index][0]
                contain[root][1] += contain[index][1]
                if judge(root):
                    effect += 1
                if count[root] % 2 == 1:
                    odds += 1
        curr = nums[0] + key + (tot - odds) // 2 + odds
        if effect == 0:
            curr -= 1
        ans = max(ans, curr)
    print(ans)


T = int(input())
t = 1
while t <= T:
    main(t)
    t += 1


# https://github.com/VaHiX/codeForces/
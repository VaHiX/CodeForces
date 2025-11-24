# Problem: CF 1267 J - Just Arrange the Icons
# https://codeforces.com/contest/1267/problem/J

"""
Algorithm: Greedy with Binary Search on Screen Size
Time Complexity: O(n * sqrt(n)) where n is the number of applications
Space Complexity: O(n) for storing category counts

The problem asks to find the minimum number of screens to place all icons such that:
1. All icons on a screen belong to the same category
2. Each screen is either full (size s) or almost full (size s-1)

Key insights:
- For a given screen size s, we can determine how many screens we need for each category
- If a category has k icons and screen size is s, we need at least ceil(k / s) screens
- We use binary search or iterate through possible screen sizes to minimize the total number of screens
- For each screen size s, we compute the total number of screens needed
- To optimize, we only check screen sizes up to the maximum count of any category

"""

def II():
    return int(input())

def GMI():
    return map(lambda x: int(x) - 1, input().split())

t = II()
outs = []
for _ in range(t):
    n = II()
    cnt = [0] * n
    for x in GMI():
        cnt[x] += 1
    tmp = [x for x in cnt if x] # Only consider non-zero category counts
    res = n # Initialize with worst case (1 icon per screen)
    for i in range(1, min(tmp) + 1): # Try all possible screen sizes up to min count
        cnt = 0
        for v in tmp:
            cur = (v - 1) // (i + 1) + 1 # Calculate how many screens needed for this category
            cnt += cur
            if i * cur > v: # Early termination condition
                break
        else:
            if cnt < res:
                res = cnt
    outs.append(res)
print("\n".join(map(str, outs)))


# https://github.com/VaHiX/CodeForces/
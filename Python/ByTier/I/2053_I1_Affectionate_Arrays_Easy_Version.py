# Problem: CF 2053 I1 - Affectionate Arrays (Easy Version)
# https://codeforces.com/contest/2053/problem/I1

"""
Affectionate Arrays (Easy Version)

This problem involves finding the minimum length of an array `b` such that:
1. Array `a` is a subsequence of `b`.
2. The sum of `a` equals the sum of `b`.
3. The maximum subarray sum (boredom) of `b` is minimized.
4. Among all such arrays with minimal boredom, the length of `b` is minimized.

Key Insight:
Since we must preserve the order of elements in `a` as a subsequence, and we want to minimize the total length of `b`, we need to efficiently "pack" elements of `a` into a sequence that satisfies the constraints. The key optimization is to track how much "slack" we have in terms of how much we can extend the prefix sum without violating constraints.

Algorithm:
- We simulate building the array `b` from `a`, maintaining prefix sums and tracking bounds (`l` and `r`) of valid subarrays.
- For each element in `a`, attempt to add it to current window.
- If adding it would violate the sum constraint or make the subarray sum invalid, we must extend the array by adding new elements to maintain validity.
- The time complexity is O(n), since we iterate through the array once.
- Space complexity is O(1), as we only use a constant number of variables.

Time Complexity: O(n)
Space Complexity: O(1)
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    s = sum(a)
    l, r = 0, 0
    ans = n
    for x in a:
        if l + x > s or r + x < 0:
            # If adding x would make the current prefix exceed sum s or the suffix fall below 0,
            # we must insert a new element to keep the sum constraint.
            ans += 1
            l, r = 0, s
        l = max(0, l + x)
        r = min(s, r + x)
    print(ans if r == s else ans + 1)


# https://github.com/VaHiX/CodeForces/
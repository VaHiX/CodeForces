# Problem: CF 2041 M - Selection Sort
# https://codeforces.com/contest/2041/problem/M

import heapq


def solve(a, n):
    # Sort the array to know the target configuration
    b = sorted(a)
    ans = float("inf")
    pq = []

    j = 0
    # Iterate through all possible prefix lengths (i)
    for i in range(n + 1):
        # Remove elements from heap that match the sorted array from the start
        while j < i and pq and pq[0] == b[j]:
            heapq.heappop(pq)
            j += 1

        # Skip elements in original array that already match the sorted array
        while j >= i and j < n and a[j] == b[j]:
            j += 1

        # Calculate cost: prefix sort cost + suffix sort cost
        ans = min(ans, i * i + (n - j) * (n - j))
        # Add current element to heap for future consideration
        if i < n and j <= i:
            heapq.heappush(pq, a[i])

    return ans


n = int(input())
a = list(map(int, input().split()))

ans = solve(a, n)

# Reverse array and negate elements to handle suffix operations as prefix after reversal
a = [-x for x in a]
a.reverse()
# Check both original and reversed array for minimum cost
print(min(ans, solve(a, n)))

### Time and Space Complexity

# **Time Complexity:**  
# Let `n` be the size of the input array. The algorithm uses a sliding window approach over the array with heap operations, where each insertion and removal from the heap takes `O(log n)` time. In the worst case, we process at most `n` elements for prefix and suffix checks, leading to an overall time complexity of `O(n log n)`.

# **Space Complexity:**  
# The space used by the heap is `O(n)` in the worst case, as we may store up to `n` elements in the heap. Additionally, sorting the array contributes `O(n)` space. Overall, the space complexity is `O(n)`.

# https://github.com/VaHiX/CodeForces/
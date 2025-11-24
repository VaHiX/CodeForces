# Problem: CF 1693 F - I Might Be Wrong
# https://codeforces.com/contest/1693/problem/F

"""
Algorithm: Greedy approach with prefix sums and tracking of operations
Time Complexity: O(n^2) in worst case due to nested loops and operations on segments
Space Complexity: O(n) for storing prefix sums and auxiliary arrays

This solution attempts to sort a binary string by performing operations that allow
sorting a substring and paying a cost based on the difference in counts of 0s and 1s.
The approach uses prefix sums to track cumulative imbalance and greedy selection
of segments to minimize total cost.
"""

inf = float("inf")

buffer = open(1, "w", 10**6)

def print(*args, sep=" ", end="\n"):
    buffer.write(sep.join(str(arg) for arg in args) + end)

def flush():
    buffer.flush()

def read_ints(index=None):
    return [int(x) for x in input().split()]

def read_ints_indexed(index):
    return [(int(x), i + index) for i, x in enumerate(input().split())]

def findPrevGreater(arr):
    # Find the previous greater element for each index using a stack
    if not arr:
        return []

    s = list()
    ans = []

    for i in range(len(arr)):
        while s:
            if arr[s[-1]] >= arr[i]:
                ans.append(s[-1])
                break
            else:
                s.pop()

        if not s:
            ans.append(-1)

        s.append(i)

    return ans

def solve():
    n = int(input())
    s = [bool(int(x)) for x in input()] # Convert string to boolean list (True=1, False=0)

    b = 0
    for i in range(n):
        if s[i]:
            b += 1
        else:
            b -= 1

    # If we have more 0s than 1s, we flip everything to make it easier to process
    if b < 0:
        s = [not x for x in s]
        s.reverse()
        b = -b

    # Convert to array of 1s and -1s for easier prefix sum computation
    cs = [1 if x else -1 for x in s]

    # Compute prefix sums
    pref = [0] * (n + 1)
    for i in range(1, n + 1):
        pref[i] = pref[i - 1] + cs[i - 1]

    prev = findPrevGreater(pref) # Find previous greater element in prefix array

    i = n
    # Skip redundant operations where prefix[i] > prefix[i-1]
    while i > 1 and pref[i] > pref[i - 1]:
        i -= 1

    j = i
    # Find first position with same prefix as i that has no previous greater element
    for k in range(i, -1, -1):
        if pref[k] == pref[i] and prev[k] == -1:
            j = k
            break

    ans = 0
    # Main loop to perform operations
    while i != 1:
        ans += 1 # Increment cost

        if pref[i] <= 0:
            break # If prefix sum is non-positive, no more operation needed

        # Modify segment from j+1 to (i+j)//2 to be 0 (False)
        for k in range(j + 1, (i + j) // 2 + 1):
            s[k - 1] = False
            pref[k] = pref[j] - (k - j)

        # Modify segment from (i+j)//2+1 to i to be 1 (True)
        for k in range((i + j) // 2 + 1, i + 1):
            s[k - 1] = True
            pref[k] = pref[j] + (k - ((i + j) // 2))

        i -= 1
        # Update i to find where prefix starts decreasing
        while i > 1 and pref[i] > pref[i - 1]:
            i -= 1

        # Update j to find new base index for next operation
        for k in range(j - 1, -1, -1):
            if pref[k] == pref[i] and prev[k] == -1:
                j = k
                break

    print(ans)

if __name__ == "__main__":
    test_cases = int(input())
    for _ in range(test_cases):
        solve()


# https://github.com/VaHiX/CodeForces/
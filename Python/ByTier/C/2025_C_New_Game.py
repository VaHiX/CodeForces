# Problem: CF 2025 C - New Game
# https://codeforces.com/contest/2025/problem/C

# C. New Game
# Algorithm: Two Pointers + Sliding Window
# Time Complexity: O(n log n) due to sorting; O(n) for the sliding window part
# Space Complexity: O(1) excluding input storage

R = lambda: map(int, input().split())
(t,) = R()
while t:
    t -= 1
    n, k = R()  # Read number of cards and max distinct numbers allowed
    a = sorted(R())  # Sort the array to enable efficient sliding window approach
    r = j = p = 0  # r: max cards taken, j: right pointer, p: previous card value + 1
    while j < n:
        if a[j] > p:  # If current card is more than one greater than previous, start new sequence
            i = j  # i: left pointer of window
        while a[j] - a[i] >= k:  # Shrink window until difference between ends is < k
            i += 1
        p = a[j] + 1  # Update p to next possible value after current card
        j += 1  # Move right pointer
        r = max(r, j - i)  # Update maximum count of cards in valid window
    print(r)


# https://github.com/VaHiX/codeForces/
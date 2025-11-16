# Problem: CF 1765 D - Watch the Videos
# https://codeforces.com/contest/1765/problem/D

"""
Algorithm: Two Pointers with Greedy Strategy
Purpose: To minimize the total time to watch all videos given a hard disk size constraint.
Technique: 
- Sort videos by size.
- Use two pointers to pair smallest and largest videos optimally.
- If pair fits, download both together; otherwise, download the larger one separately.
- Add the sum of all video sizes as the total watching time.

Time Complexity: O(n log n) due to sorting, where n is the number of videos.
Space Complexity: O(1) as we use only a constant amount of extra space.
"""

n, m = list(map(int, input().split()))
nums = list(map(int, input().split()))
nums.sort()  # Sort the video sizes in ascending order
ans = 1  # Initialize result with 1 since at least one download will be needed
l = 0  # Left pointer, pointing to smallest available video
r = n - 1  # Right pointer, pointing to largest available video

# Two-pointer approach to pair videos optimally
while l < r:
    if nums[r] + nums[l] <= m:  # If the smallest and largest can fit together
        r -= 1  # Move right pointer to the next smaller video
        l += 1  # Move left pointer to the next larger video
    else:
        r -= 1  # Download the largest video separately
        ans += 1  # Increment the number of downloads needed

# Add the total time required to watch all videos (sum of all sizes)
print(ans + sum(nums))


# https://github.com/VaHiX/CodeForces/
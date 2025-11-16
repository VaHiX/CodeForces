# Problem: CF 863 B - Kayaking
# https://codeforces.com/contest/863/problem/B

"""
Algorithm: 
- This problem involves selecting pairs of people to form tandem kayaks such that the total instability (sum of absolute differences between paired people) is minimized.
- Since we have n-1 tandem kayaks and 2 single kayaks, we must choose 2 people to be in single kayaks, and form n-1 pairs from the remaining 2n-2 people.
- A brute-force approach is used:
  1. Try all possible pairs of people to assign to single kayaks.
  2. For each such pair, remove those two people from the list.
  3. Sort the remaining 2n-2 people.
  4. Pair them consecutively (i.e., 0 and 1, 2 and 3, etc.), compute the instability as sum of differences.
  5. Keep track of the minimum instability found.

Time Complexity: O(n^2 * (2n log 2n)) = O(n^2 * n) = O(n^3)
Space Complexity: O(2n) = O(n)

Techniques: Brute-force with sorting and greedy pairing
"""

N = int(input())
nums = [int(x) for x in input().split()]
nums.sort()

answer = 10000000
for i in range(len(nums)):  # Try all possible first person for single kayak
    for j in range(i + 1, len(nums)):  # Try all possible second person for single kayak
        temp = nums.copy()  # Create a copy to avoid modifying original list
        count = 0
        temp.pop(i)  # Remove first person for single kayak
        temp.pop(j - 1)  # Remove second person for single kayak (adjust index due to previous pop)
        for k in range(0, len(temp) - 1, 2):  # Iterate through pairs in sorted list
            count += temp[k + 1] - temp[k]  # Add instability of this pair
        answer = min(answer, count)  # Update minimum instability
print(answer)


# https://github.com/VaHiX/CodeForces/
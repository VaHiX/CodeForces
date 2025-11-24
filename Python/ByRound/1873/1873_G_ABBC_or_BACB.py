# Problem: CF 1873 G - ABBC or BACB
# https://codeforces.com/contest/1873/problem/G

"""
Algorithm: Greedy approach using string splitting
Techniques: 
  - Split string by 'B' to get segments of consecutive 'A's
  - For each segment, we can convert all 'A's to 'B's by using AB->BC operations
  - But we can only perform one operation per segment (because all A's in a segment
    can be reduced to B's with one operation per A)
  - The key insight is that for each group of consecutive A's, we can form at most 
    (length of group - 1) operations, unless there's a B between them.
  - So, we split the string by 'B', and for each group of A's, we count how many
    operations we can get from that group. However, we must process the entire
    string greedily to avoid overcounting.

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(n) for storing the split segments.
"""

t = int(input())
answers = [""] * t
for _ in range(t):
    s = input()
    l = 0
    r = 0
    ans = 0
    # Split the string by 'B' to get counts of consecutive 'A's
    s = list(map(len, s.split("B")))
    # The total number of operations is sum of lengths minus minimum length
    # This works because we can reduce all but one A in each continuous segment
    ans = sum(s) - min(s)
    answers[_] = ans
for answer in answers:
    print(answer)


# https://github.com/VaHiX/CodeForces/
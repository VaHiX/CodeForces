# Problem: CF 2123 D - Binary String Battle
# https://codeforces.com/contest/2123/problem/D

"""
D. Binary String Battle

Algorithm/Technique: Game Theory, Greedy Strategy

Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(1), as we only use a constant amount of extra space.

The problem involves a game between Alice and Bob on a binary string:
- Alice goes first and can choose any subsequence of length k to set to '0'.
- Bob moves second and can choose any substring of length k to set to '1'.
- Alice wins if the string becomes all zeros at any point.
- The key observation is that Alice must be able to cover all '1's in the string
  with subsequences of size k, but Bob can interfere by setting substrings of size k to '1'.

The logic:
- If there are at most k ones or if k > n/2, then Alice wins because either:
  - There aren't enough ones to prevent her from covering all of them (when k >= number of ones),
  - Or it's impossible for Bob to block her from turning all into zeros due to limited interference.
- Otherwise, Bob has sufficient opportunity to counteract.

"""

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    s = input()
    
    # Count number of '1's in the string
    ones_count = s.count("1")
    
    # Alice wins if:
    # 1. There are at most k ones (so she can cover all with one move), or
    # 2. k is greater than half the length (she has too much freedom to win)
    if ones_count <= k or k > n // 2:
        print("Alice")
    else:
        print("Bob")


# https://github.com/VaHiX/codeForces/
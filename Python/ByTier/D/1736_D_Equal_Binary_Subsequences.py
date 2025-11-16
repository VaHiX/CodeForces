# Problem: CF 1736 D - Equal Binary Subsequences
# https://codeforces.com/contest/1736/problem/D

"""
Problem: Equal Binary Subsequences

Algorithms/Techniques:
- Greedy approach to partition the string into two equal subsequences
- For a valid partition, we need to ensure that the count of '1's is even
- If the count of '1's is odd, it's impossible to split them equally, return -1
- Otherwise, we try to find a way to rotate some subsequence such that we can form two equal subsequences
- The core idea is to pair up characters at even and odd indices, and identify mismatches that can be resolved by rotation

Time Complexity: O(n), where n is the length of the string (excluding the input parsing part)
Space Complexity: O(n), to store the indices to rotate

"""
for _ in range(int(input())):
    n = int(input())
    s = input()
    x = 0
    for i in s:
        if i == "1":
            x += 1
    if x % 2 == 1:
        print(-1)
    else:
        a = []  # Not used in this implementation
        b = []  # Not used in this implementation
        k = 0   # Toggle variable to alternate between 0 and 1
        l = []  # List to store indices to rotate
        for i in range(n):
            # Compare characters at even index and odd index (2*i and 2*i+1)
            if s[2 * i] != s[2 * i + 1]:
                # If they are different and s[2*i] equals the current expected value (k),
                # then we add the index of s[2*i+1] to be rotated
                if s[2 * i] == str(k):
                    l.append(2 * i + 1)
                else:
                    # Else add the index of s[2*i] to be rotated
                    l.append(2 * i + 2)
                # Toggle the expected value
                k = 1 - k
        print(len(l), *l)
        # Print indices 1, 3, 5, ... from the original string as the first subsequence
        print(*range(1, 2 * n + 1, 2))


# https://github.com/VaHiX/CodeForces/
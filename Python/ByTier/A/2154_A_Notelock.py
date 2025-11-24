# Problem: CF 2154 A - Notelock
# https://codeforces.com/contest/2154/problem/A

"""
Algorithm: Greedy
Time Complexity: O(n * k) where n is the length of string s and k is the given parameter
Space Complexity: O(n) for the protected array

The algorithm uses a greedy approach to determine the minimum number of positions to protect.
For each position i in the string, if s[i] is '1' and it's not already protected,
we check whether there's a '1' within the previous k-1 positions.
If not, we protect this position to prevent Teto from changing it to '0'.
This greedy strategy ensures we protect the minimal number of positions necessary.
"""

t = int(input())
lst = []
for _ in range(t):
    m, n = map(int, input().split())
    s = input()
    protected = [False] * m  # Array to track which positions are protected
    counter = 0  # Counter for the number of protected positions
    for i in range(m):
        min_pos = max(0, i - n + 1)  # Calculate the start of the window of previous k-1 elements
        if s[i] == "1" and not protected[i]:  # If current element is '1' and not yet protected
            has_1_before = False  # Flag to check if any '1' exists in the previous k-1 positions
            for j in range(min_pos, i):  # Iterate through the previous k-1 positions
                if s[j] == "1":
                    has_1_before = True
                    break
            if not has_1_before:  # If no '1' is found in the previous k-1 positions
                protected[i] = True  # Protect this position
                counter += 1  # Increment the counter
    lst.append(counter)

for i in range(t):
    print(lst[i])


# https://github.com/VaHiX/CodeForces/
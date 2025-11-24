# Problem: CF 1926 A - Vlad and the Best of Five
# https://codeforces.com/contest/1926/problem/A

"""
Problem: A. Vlad and the Best of Five
Algorithm: Counting characters in a string
Time Complexity: O(n) where n is the length of the string (5 in this case)
Space Complexity: O(1) - only using a constant amount of extra space

The solution counts occurrences of 'A' and 'B' in each string and prints the character with higher count.
"""

testcases = int(input())
for _ in range(testcases):
    s = input()
    count_a = 0
    count_b = 0
    for i in range(len(s)):
        if s[i] == "A":
            count_a += 1
        elif s[i] == "B":
            count_b += 1
    if count_a > count_b:
        print("A")
    else:
        print("B")


# https://github.com/VaHiX/CodeForces/
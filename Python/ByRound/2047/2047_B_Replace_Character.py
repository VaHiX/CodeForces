# Problem: CF 2047 B - Replace Character
# https://codeforces.com/contest/2047/problem/B

"""
Replace Character Problem

Algorithm:
- For each string, we want to minimize the number of distinct permutations.
- The number of distinct permutations is minimized when we have as many repeated characters as possible.
- To do this, we find the character with the minimum frequency and replace it with the character with maximum frequency.
- This ensures that we increase the frequency of the most common character and reduce the frequency of the least common, leading to fewer distinct permutations.

Time Complexity: O(n) where n is the length of the string. We iterate through the string twice (once to count frequencies, once to perform the replacement).
Space Complexity: O(1) since the dictionary size is at most 26 (for 26 lowercase letters), which is constant.
"""

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


def lcm(a, b):
    return (a * b) // gcd(a, b)


MAXINT = float("inf")
MININT = -float("inf")
MOD = 10**9 + 7


def helper(n, s):
    st = list(s)
    d = {}
    for i in range(n):
        if st[i] not in d:
            d[st[i]] = 1
        else:
            d[st[i]] += 1

    maximumFrequency = MININT
    minimumFrequency = MAXINT
    maximumKey = ""
    minimumKey = ""
    for key in d.keys():
        if d[key] > maximumFrequency:
            maximumFrequency = d[key]
            maximumKey = key
    for key in d.keys():
        if d[key] <= minimumFrequency:
            minimumFrequency = d[key]
            minimumKey = key

    # Replace the character with minimum frequency with the one with maximum frequency
    for i in range(n):
        if st[i] == minimumKey:
            st[i] = maximumKey
            break
    st = "".join(st)
    return st


def main():
    t = int(input())
    while t:
        n = int(input())
        s = input()
        print(helper(n, s))
        t -= 1


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
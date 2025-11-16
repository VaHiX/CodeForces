# Problem: CF 1922 A - Tricky Template
# https://codeforces.com/contest/1922/problem/A

"""
Problem: Tricky Template

Algorithm/Technique: Greedy approach
Time Complexity: O(n) per test case, where n is the length of the strings
Space Complexity: O(1) - only using a constant amount of extra space

The solution works by iterating through each character position and checking
if there exists a valid template that satisfies the conditions:
1. Both a and b match the template
2. c does not match the template

For each character position i:
- If sa[i] == sb[i], then:
  * If sa[i] != sc[i], we can use a lowercase template that matches the character
  * Otherwise, we cannot distinguish a and b from c using this position
- If sa[i] != sb[i], then:
  * We can use a template that makes a and b match while making c not match
  * For example, if sa[i] = 'a', sb[i] = 'b', sc[i] = 'c',
    * We can use template 'a' (lowercase) to match a, 'B' (uppercase) to match b,
      and 'c' would not match (since template 'B' excludes 'b')
"""

def solve_test_case():
    sn = int(input())
    sa = input()
    sb = input()
    sc = input()
    for i in range(sn):
        if sa[i] == sb[i]:
            # If a and b have the same character at position i
            # Check if c is different from this character
            # If yes, we can use a lowercase template to match a and b 
            # but not match c
            if sa[i] != sc[i]:
                print("YES")
                return
        elif sa[i] != sc[i] and sb[i] != sc[i]:
            # If a and b have different characters at position i
            # And both a and b are different from c at this position
            # We can use a template that allows a and b to match but not c
            print("YES")
            return
    print("NO")


def main():
    cases = int(input())
    for _ in range(cases):
        solve_test_case()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/
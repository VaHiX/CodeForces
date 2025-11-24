# Problem: CF 1709 C - Recover an RBS
# https://codeforces.com/contest/1709/problem/C

"""
Problem: Recover an RBS
Algorithm/Technique: Greedy simulation with stack-like tracking
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) as we only use a few variables regardless of input size

The approach simulates a stack to track balance of brackets. 
When we encounter a '?', we consider it as a potential '(' or ')', 
and track how many unmatched '(' we might need to balance. 
If at any point the number of unmatched '(' exceeds the number of ')' 
we have seen, we know it's ambiguous, hence we output NO.
Otherwise, if we can uniquely assign all '?' to make a valid RBS, output YES.

Key logic:
- 'c' tracks the balance of the current bracket sequence.
- 'x' keeps track of unknowns ('?') that could be either '(' or ')'.
- When balance becomes negative, we check if it's due to too many ')' or too many '?'.
- At the end, if all '?' are used up in making a valid sequence, then 'YES' else 'NO'.
"""

for t in range(int(input())):
    s = input()
    c = 0  # balance counter for brackets
    x = 0  # count of unmatched '(' that could be resolved by '?' or ')' later
    for i in s:
        if i == "(":
            c += 1
        elif i == ")":
            c -= 1
        else:  # i == "?"
            x += 1
        # If we have more unmatched '(' than available '?', then ambiguity arises
        if 1 - c == x:
            x = 0  # Reset x since we are treating one of '?' as '('
            c = 1  # Reset c to reflect that one '(' was taken from x
    # Check if all '?' are consumed in a unique way to maintain valid RBS
    if x == c:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/
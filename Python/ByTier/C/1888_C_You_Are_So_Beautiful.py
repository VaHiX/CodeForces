# Problem: CF 1888 C - You Are So Beautiful
# https://codeforces.com/contest/1888/problem/C

"""
Algorithm: Two Pointers + Set + Hash Map
Time Complexity: O(n)
Space Complexity: O(n)

This problem asks to count the number of subarrays that appear as a unique subsequence in the array.
The key insight is:
1. For each element, we store its last occurrence index in `last` dictionary.
2. As we iterate through the array, we maintain a set `s` of unique elements seen so far.
3. When we encounter an element that is the last occurrence of itself (i.e., `last[v] == i`), 
   we add the count of unique elements seen so far (`uc`) to the answer.
   This is because all subarrays ending at current position with unique elements up to this point
   will form a valid subsequence with exactly one occurrence.
"""

def solve():
    input()
    a = list(map(int, input().split()))
    last = dict()
    # Preprocessing: store the last occurrence index of each element
    for i, v in enumerate(a):
        last[v] = i
    s = set()
    uc = 0  # Count of unique elements seen so far
    ans = 0
    # Iterate through the array
    for i, v in enumerate(a):
        # If current element is not seen before, add it to the set and increment unique count
        if v not in s:
            s.add(v)
            uc += 1
        # If current element is the last occurrence of itself
        if last[v] == i:
            ans += uc  # Add the number of unique elements to the result
    print(ans)
    return


if __name__ == "__main__":
    t = 1
    t = int(input())
    while t > 0:
        t -= 1
        solve()


# https://github.com/VaHiX/CodeForces/
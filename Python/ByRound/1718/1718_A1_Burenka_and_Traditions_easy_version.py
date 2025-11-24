# Problem: CF 1718 A1 - Burenka and Traditions (easy version)
# https://codeforces.com/contest/1718/problem/A1

"""
Purpose: 
This code solves the problem of finding the minimum time needed to reduce all elements of an array to zero using XOR operations on segments. 
The key insight is that the cumulative XOR (prefix XOR) of the array helps determine the number of operations required. 
Each unique prefix XOR value indicates a segment that needs to be processed. 
The algorithm mimics a greedy approach: if we encounter a prefix XOR that has appeared before, 
it implies that a segment from the previous occurrence to current position can be XORed with a specific value to zero out that segment.
This results in fewer operations than the naive approach.

Algorithms/Techniques:
- Prefix XOR technique
- Set-based tracking of unique prefix XORs
- Greedy selection of segments

Time Complexity: O(n) where n is the length of the array. Each element is processed once in the loop and set operations are O(1) average.
Space Complexity: O(n) for storing prefix XORs and the set structure.
"""

t = int(input())
for i in range(t):
    n = int(input())
    lst = list(map(int, input().split()))
    res = n  # Initially assume each element requires one operation
    for i in range(1, n):
        lst[i] ^= lst[i - 1]  # Compute prefix XOR
    st = set()
    st.add(0)
    for i in lst:
        if i in st:
            res -= 1  # Found a segment that can be cleared in less time
            st.clear()  # Reset set to start fresh
        st.add(i)
    print(res)


# https://github.com/VaHiX/CodeForces/
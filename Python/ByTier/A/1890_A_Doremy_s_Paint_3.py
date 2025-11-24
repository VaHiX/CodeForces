# Problem: CF 1890 A - Doremy's Paint 3
# https://codeforces.com/contest/1890/problem/A

"""
Algorithm: 
    - Sort the array first.
    - Count the frequency of each element using a hashmap.
    - Check if the number of unique elements is less than 3.
    - Also check if the difference between the maximum and minimum frequencies is less than 2.
    
Time Complexity: O(n log n) due to sorting, where n is the length of the array.
Space Complexity: O(n) for storing the frequency map.
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()
    mp = {}
    for i in a:
        if i not in mp:
            mp[i] = 0
        mp[i] += 1
    print("YES" if len(mp) < 3 and abs(mp[a[0]] - mp[a[-1]]) < 2 else "NO")


# https://github.com/VaHiX/CodeForces/
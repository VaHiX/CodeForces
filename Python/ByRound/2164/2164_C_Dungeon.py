# Problem: CF 2164 C - Dungeon
# https://codeforces.com/contest/2164/problem/C

import sys

input = lambda: sys.stdin.readline().strip()
inp = lambda: list(map(int, input().split()))

"""
A simpler SortedList implementation with O(n) insert/pop but O(n log n) for building the list.
Good for when you want predictable O(n log n) behavior overall.
"""

from bisect import bisect_left, bisect_right, insort


class SortedList:
    def __init__(self, iterable=()):
        self._list = sorted(iterable)

    def insert(self, x):
        """O(n) insertion using bisect.insort"""
        insort(self._list, x)

    def pop(self, k=-1):
        """O(n) pop from arbitrary position"""
        if k < 0:
            k += len(self._list)
        return self._list.pop(k)

    def __getitem__(self, k):
        """O(1) access"""
        if isinstance(k, slice):
            return SortedList(self._list[k])
        return self._list[k]

    def count(self, x):
        """O(log n) count using binary search"""
        left = bisect_left(self._list, x)
        right = bisect_right(self._list, x)
        return right - left

    def __contains__(self, x):
        """O(log n) membership test"""
        index = bisect_left(self._list, x)
        return index < len(self._list) and self._list[index] == x

    def lower_bound(self, x):
        """O(log n) - returns first index where element >= x"""
        return bisect_left(self._list, x)

    def upper_bound(self, x):
        """O(log n) - returns first index where element > x"""
        return bisect_right(self._list, x)

    def __len__(self):
        return len(self._list)

    def __iter__(self):
        return iter(self._list)

    def __repr__(self):
        return repr(self._list)


outs = []
for __ in range(int(input())):
    n, m = inp()
    a = inp()
    gain = []
    b = inp()
    c = inp()
    no_ret = []

    ans = 0
    for i in range(m):
        if c[i] > 0:
            gain.append((b[i], c[i]))  # Collect monsters that give a new sword
        else:
            no_ret.append(b[i])  # Collect monsters that don't give a new sword

    Sor = SortedList(a)  # Sort swords in ascending order for efficient access

    gain.sort(key=lambda x: x[0])  # Sort gaining monsters by their health (ascending)
    no_ret.sort()  # Sort monsters that don't give new swords
    ans = 0

    # Process monsters that can give new swords
    for ne, ga in gain:
        ind = Sor.lower_bound(ne)  # Find smallest sword that can kill monster 'ne'
        if ind < len(Sor):
            ans += 1
            sw = Sor[ind]
            if ga > sw:
                Sor.pop(ind)  # Remove the used sword
                Sor.insert(ga)  # Insert the new sword with damage max(sw, ga)

    # Process monsters that do not give a new sword
    t = len(Sor) - 1  # Start from largest sword
    while no_ret and t >= 0:
        ne = no_ret.pop()  # Get monster with highest health among those that do not give new sword
        if Sor[t] >= ne:  # Check if current largest sword can kill this monster
            ans += 1
            t -= 1  # Move to next largest sword

    outs.append(ans)
print("\n".join(map(str, outs)))

# ### Time and Space Complexity:

# - **Time Complexity**: O((n + m) * log(n + m))
#   - Sorting `gain` and `no_ret`: O(m * log m)
#   - Loop processing `gain`: O(m * log n)
#   - Loop processing `no_ret`: O(m)
#   - Overall: O((n + m) * log(n + m))
  
# - **Space Complexity**: O(n + m)
#   - Storing sorted swords (`Sor`), gain list, and no_ret list.

# https://github.com/VaHiX/CodeForces/
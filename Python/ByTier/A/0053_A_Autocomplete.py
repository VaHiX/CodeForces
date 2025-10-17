# Contest 53, Problem A: Autocomplete
# URL: https://codeforces.com/contest/53/problem/A

lst = [w.rstrip() for w in open(0).readlines()]
target = lst[0]
lst = [x for x in lst[2:] if x[0 : len(target)] == target]
print(min(lst) if len(lst) else target)

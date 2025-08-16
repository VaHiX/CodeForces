# Contest 690, Problem B1: Recover Polygon (easy)
# URL: https://codeforces.com/contest/690/problem/B1

def check_cell(i, j, n):
	k = 0
	if i > 1 and field[i-1][j]: k += 1
	if i < n-1 and field[i+1][j]: k += 1
	if j > 1 and field[i][j-1]: k += 1
	if j < n-1 and field[i][j+1]: k += 1
	if k<2:
	    return 0
	elif k<4:
	    return k-1
	else:
	    return 4
n = int(input())
field = []
for i in range(n):
	temp = [int(x) for x in input()]
	field.append(temp)
def main():
	for i in range(n):
		for j in range(n):
			if field[i][j] and not field[i][j] == check_cell(i, j, n):
				print('No')
				return 0
	print('Yes')
main()
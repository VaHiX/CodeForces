// Problem: CF 2115 A - Gellyfish and Flaming Peony
// https://codeforces.com/contest/2115/problem/A

/*
 * Problem: Gellyfish and Flaming Peony
 * Purpose: Find the minimum number of operations to make all elements in an array equal,
 *          where each operation replaces one element with gcd of that element and another.
 *
 * Algorithm: 
 *   - Reduce the problem by dividing all elements by their global GCD to simplify values.
 *   - If any element is 1, return count of non-ones (as all can become 1).
 *   - Else, use BFS-like DP on GCD values from max value down to 1:
 *     - For each value x, try combining it with all array elements using gcd,
 *       updating distance to new GCD value.
 *   - Final result is minimum steps to reach 1 plus original array size minus 1.
 *
 * Time Complexity: O(n * max(a) + max(a) * n)
 * Space Complexity: O(max(a))
 */
private fun solve(): Int {
	readInt()
	val a = readInts().toIntArray()
	val g = a.reduce(::gcd) // Compute global GCD of the array
	for (i in a.indices) a[i] /= g // Normalize all elements by dividing with global GCD
	if (1 in a) return a.count { it != 1 } // If any element is 1, answer is count of non-ones
	
	val aMax = a.max() // Maximum value in normalized array
	val inf = Int.MAX_VALUE / 2 // Sentinel for infinity
	val dist = IntArray(aMax + 1) { inf } // Distance array to store min steps to reach each GCD value
	
	for (value in a) dist[value] = 0 // All original values can be reached in 0 operations
	
	// Process from max down to 1: dynamic programming on possible GCDs
	for (x in aMax downTo 1) {
		if (dist[x] == inf) continue // Skip unreachable values
		
		for (value in a) {
			val z = gcd(x, value) // Compute new GCD
			dist[z] = minOf(dist[z], dist[x] + 1) // Update minimum steps to reach z
		}
	}
	
	return dist[1] + a.size - 1 // Steps to reduce to 1 plus initial non-1 elements
}

fun main() = repeat(readInt()) { println(solve()) }

private tailrec fun gcd(a: Int, b: Int): Int = if (a == 0) b else gcd(b % a, a)
private fun readInt() = readln().toInt()
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }


// https://github.com/VaHiX/CodeForces/
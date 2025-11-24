// Problem: CF 1958 I - Equal Trees
// https://codeforces.com/contest/1958/problem/I

/**
 * Problem: Equal Trees
 * 
 * Given two rooted trees with n vertices each, find the minimum number of operations
 * to make them equal. An operation involves removing a non-root vertex and connecting
 * its children to its parent.
 * 
 * Algorithm:
 * - Preprocess the trees to build parent arrays
 * - For each pair of vertices (a,b), determine if a and b are in the same subtree
 *   in both trees, which helps compute compatibility
 * - Use dynamic programming with bitmasks to compute minimum operations needed
 * - State: for each subset of vertices, compute minimal operations required to make
 *   them equal; transitions based on compatibility and bitmask operations
 * 
 * Time Complexity: O(n^3 + 2^n * n)
 * Space Complexity: O(n^2 + 2^n)
 */
fun readTree(n: Int): List<BooleanArray> {
    val p = listOf(null) + readInts().map { it - 1 } // Parent array for each node (0-indexed)
    return List(n) { a -> BooleanArray(n) { b -> a in generateSequence(b) { p[it] } } }
        // Precompute subtree relationships: t1[a][b] = true if a is in subtree of b in tree 1
}

fun main() {
    val n = readInt()
    val t1 = readTree(n)
    val t2 = readTree(n)
    
    // masks[a] stores a bitmask of all nodes b such that:
    // - a != b
    // - a and b are in same subtree in both trees (t1[a][b] == t2[a][b])
    // - parent relationships match between trees (t1[b][a] == t2[b][a])
    val masks =
        LongArray(n) { a ->
        (0 until n)
            .filter { b -> a != b && t1[a][b] == t2[a][b] && t1[b][a] == t2[b][a] }
            .sumOf { 1L shl it } // Build bitmask of compatible nodes
        }
    
    val data = mutableMapOf<Long, Int>() // Memoization for DP
    data[0] = 0 // Base case: no operations needed for empty set
    
    // Recursive DP function to compute minimum operations for a given mask
    fun compute(mask: Long): Int =
        data.getOrPut(mask) {
            val index = mask.countTrailingZeroBits() // Find first unset bit in mask
            maxOf(
                compute(mask xor (1L shl index)), // Option 1: ignore node at index
                compute(mask and masks[index]) + 1 // Option 2: merge compatible nodes
            )
        }
    
    // Result = 2 * (n - max operations to make trees equal with current DP logic)
    println(2 * (n - compute((1L shl n) - 1)))
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }


// https://github.com/VaHiX/codeForces/
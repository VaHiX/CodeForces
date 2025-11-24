// Problem: CF 2115 B - Gellyfish and Camellia Japonica
// https://codeforces.com/contest/2115/problem/B

/*
 * Problem: B. Gellyfish and Camellia Japonica
 *
 * Purpose:
 *   Given a final array 'b' after applying a series of operations on an unknown initial array 'a',
 *   determine if there exists a valid initial array 'a' such that the transformations match.
 *   Each operation sets c[z] = min(c[x], c[y]), where c starts as a copy of a.
 *
 * Algorithms/Techniques:
 *   - Reverse simulation to reconstruct lower bounds for values in 'a'
 *   - Forward simulation to validate that constructed 'a' produces final array 'b'
 *   - Graph-based propagation or order-dependent processing
 *
 * Time Complexity: O(n + q)
 *   - Each element is processed once during reverse pass and once during forward pass.
 *   - The operations are linear in the total size of input arrays.
 *
 * Space Complexity: O(n + q)
 *   - Storage for input arrays, queries, and temporary arrays of size n.
 */

private fun solve() {
    val (_, queriesCount) = readInts()
    val b = readInts().toIntArray() // Final state array
    val a = b.clone() // Copy to simulate operations (initially equal to b)
    val queries = List(queriesCount) { readInts().map { it - 1 } } // Convert indices to 0-based
    
    // Process queries in reverse order to determine min required values at each index
    for ((x, y, z) in queries.reversed()) {
        val res = a[z] // Current value at z after reverse operation
        if (z != x && z != y) {
            a[z] = 0 // If z is not x or y, then it will be overwritten in forward pass
        }
        a[x] = maxOf(a[x], res) // Ensure that x has at least res as value to make z = min(x,y)
        a[y] = maxOf(a[y], res)
    }
    
    val ans = a.clone() // Save a copy of the reconstructed array
    
    // Forward simulation: compute what the actual final values should be given current 'a'
    for ((x, y, z) in queries) {
        a[z] = minOf(a[x], a[y]) // Simulate c[z] = min(c[x], c[y])
    }
    
    // Check if resulting array matches original 'b'
    if (!a.contentEquals(b)) {
        println(-1)
        return
    }
    
    println(ans.joinToString(" "))
}

fun main() = repeat(readInt()) { solve() }

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2131 G - Wafu!
// https://codeforces.com/contest/2131/problem/G

/**
 * Problem: G. Wafu!
 * Purpose: Computes the final score after performing k operations on a set of integers.
 *          Each operation removes the minimum element, multiplies the score by that element,
 *          and adds all values from 1 to (m-1) back to the set.
 *
 * Algorithms/Techniques:
 * - Dynamic Programming with Memoization
 * - Precomputed Tree Product for efficiency
 * - Bit manipulation for key packing
 * - Greedy selection based on sorted array
 *
 * Time Complexity: O(n * log n + k * log k) where n is the size of input set and k is number of operations.
 * Space Complexity: O(LIMIT^2 + 2^16) where LIMIT = 31, for memoization and precomputed values.
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.min

private const val MOD = 1_000_000_007L
private const val LIMIT = 31

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val testCases = reader.readLine().toInt()
    
    // Precompute layer sizes (2^(i-1)) for each i from 1 to LIMIT
    val layerSizes = LongArray(LIMIT + 1)
    for (i in 1..LIMIT) {
        layerSizes[i] = 1L shl (i - 1)
    }
    
    // Precompute treeProduct where treeProduct[i] represents the product of all treeProduct[j] for j < i
    val treeProduct = LongArray(LIMIT + 1) { 1 }
    treeProduct[1] = 1
    for (i in 2..LIMIT) {
        var value = i.toLong() % MOD
        for (j in 1 until i) {
            value = (value * treeProduct[j]) % MOD
        }
        treeProduct[i] = value
    }
    
    // Memoization map to store results of computeValue function
    val memo = HashMap<Long, Long>(1 shl 16)
    
    // Packs x and p into a single long key for memoization
    fun packKey(x: Int, p: Int): Long {
        return (x.toLong() shl 32) or (p.toLong() and 0xffffffffL)
    }
    
    // Recursive function to compute value using memoization
    fun computeValue(nodes: Int, depth: Int): Long {
        if (depth == 0 || nodes == 1) return 1
        val key = packKey(nodes, depth)
        memo[key]?.let { return it } // Return cached result if exists
        
        var result = nodes.toLong() % MOD // Base case multiplication
        var remaining = depth.toLong() - 1
        val upper = min(nodes - 1, LIMIT) // Upper bound to prevent overflow
        
        for (i in 1..upper) {
            if (remaining <= 0) break
            if (remaining >= layerSizes[i]) {
                result = (result * treeProduct[i]) % MOD // Multiply by precomputed product for layer i
                remaining -= layerSizes[i]
            } else {
                result = (result * computeValue(i, remaining.toInt())) % MOD // Recursive call with remaining depth
                remaining = 0
            }
        }
        
        memo[key] = result // Store computed value in memo
        return result
    }
    
    // Process each test case
    repeat(testCases) {
        val (n, k) = reader.readLine().split(" ").map { it.toLong() }
        val tokenizer = StringTokenizer(reader.readLine())
        val arr = LongArray(n.toInt()) { tokenizer.nextToken().toLong() }
        arr.sort() // Sort the array for greedy processing
        
        var answer = 1L
        var remaining = k // Number of operations left to perform
        
        for (value in arr) {
            if (remaining <= 0) break
            val capacity = if (value <= LIMIT) layerSizes[value.toInt()] else (1L shl 62) // Max possible capacity
            if (capacity <= remaining) {
                answer = if (value <= LIMIT) {
                    (answer * treeProduct[value.toInt()]) % MOD // Use precomputed value if within limit
                } else {
                    (answer * computeValue(value.toInt(), (capacity % (1L shl 31)).toInt())) % MOD // Use recursion for larger values
                }
                remaining -= capacity // Decrease remaining operations count
            } else {
                answer = (answer * computeValue(value.toInt(), remaining.toInt())) % MOD // Final recursive step
                remaining = 0 // All operations done
            }
        }
        println(answer % MOD)
    }
}


// https://github.com/VaHiX/CodeForces/
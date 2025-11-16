// Problem: CF 2114 F - Small Operations
// https://codeforces.com/contest/2114/problem/F

/**
 * Problem: F. Small Operations
 *
 * Purpose:
 * Given integers x, y, and k, compute the minimum number of operations to transform x into y,
 * where each operation allows multiplying or dividing x by an integer in range [1, k], as long
 * as the result remains an integer.
 *
 * Algorithms & Techniques:
 * - Prime factorization + Dynamic Programming on divisors
 * - For a given number N, find all its divisors and build DP to represent minimum operations
 *   to reach each divisor from 1 using multipliers up to k.
 * - Uses GCD for reducing x and y to coprime form before processing.
 *
 * Time Complexity:
 * - For each test case: O(√max(x,y) * d(max(x,y)) * log(d(max(x,y))))
 *   where d(n) is the number of divisors of n. In practice, it is fast due to constraints.
 * Space Complexity:
 * - O(√max(x,y)) for storing divisors and DP arrays.
 */

const val INF = 0x3f3f3f3f

class TrieNode {
    val children: MutableMap<Char, TrieNode> = mutableMapOf()
    var isEndOfWord = false
}

class Trie(private val k : Int) {
    val root = TrieNode()
    private var deep: MutableMap<TrieNode, Int> = mutableMapOf()
    
    fun insert(word: String) {
        var node = root
        for (c in word) {
            node = node.children.getOrPut(c) { TrieNode() } // Build trie path
        }
        node.isEndOfWord = true // Mark end of word
    }
    
    private fun dfs(node: TrieNode) : Int {
        val maxChildDepth = node.children.values.maxOfOrNull { dfs(it) } ?: 0
        return when {
            node.children.size < k -> 1 // If fewer than k children, depth is 1
            else -> maxChildDepth + 1 // Else, add depth of max child
        }.also { deep[node] = it } // Store computed depth
    }
    
    fun query(word: String) : Int {
        val node = word.fold(root) { currentNode, c ->
            currentNode.children[c] ?: return 0 // Return 0 if character not found
        }
        return deep[node] ?: 0 // Return stored value or 0 if not found
    }
    
    fun buildDepths() {
        dfs(root)
    }
}

fun gcd(x: Int, y: Int) : Int{
    return if (y == 0) x else gcd(y, x % y) // Euclidean GCD
}

fun cf2104E() {
    val (n, k) = readln().split(" ").map { it.toInt() }
    val s = readln()
    val nxt = Array(n + 1) { IntArray(26) { n } } // Preprocessing array for string
    val f = IntArray(n + 2).apply { this[n] = 1 } // Count for suffixes
    var mask = 0
    
    (n - 1 downTo 0).forEach { i ->
        nxt[i] = nxt[i + 1].copyOf() // Copy previous prefix
        val charIndex = s[i] - 'a'
        nxt[i][charIndex] = i // Record the last occurrence of character
        mask = mask or (1 shl charIndex) // Mark presence of character
        f[i] = f[i + 1]
        
        if (mask == (1 shl k) - 1) { // All K characters present in window
            f[i]++
            mask = 0 // Reset for next segment
        }
    }
    
    repeat(readln().toInt()) {
        val result = readln().fold(-1) { i, c ->
            if (i == n) n else nxt[i + 1][c - 'a'] // Find next position of character in string
        }
        println(f[result + 1]) // Output count for that suffix
    }
}

fun Int.getDivisors(): List<Int> {
    val sqrt = kotlin.math.sqrt(this.toDouble()).toInt()
    return (1..sqrt)
        .filter { this % it == 0 } // Find divisors up to square root
        .flatMap { divisor ->
            when {
                divisor * divisor == this -> listOf(divisor) // Perfect square, avoid duplicates
                else -> listOf(divisor, this / divisor) // Include both divisor and quotient
            }
        }
        .sorted() // Sort final list of divisors
}

fun Int.solveForPrime(k: Int): Int {
    val divisors = this.getDivisors() // Get all divisors of current number
    val dp = IntArray(divisors.size) { INF }.apply { this[0] = 0 } // DP array initialized with infinity, base case is 0
    
    divisors.indices.forEach { i ->
        (i downTo 0).takeWhile { j ->
            divisors[i] / divisors[j] <= k // Ensure divisor ratio fits in [1,k]
        }.filter { j ->
            divisors[i] % divisors[j] == 0 // Check if j divides i-th divisor
        }.forEach { j ->
            dp[i] = minOf(dp[i], dp[j] + 1) // Update minimum steps using previous divisor
        }
    }
    
    return dp.last() // Return minimum steps for largest divisor (i.e., the number itself)
}

fun cf2114f() {
    repeat(readln().toInt()) {
        val (x, y, k) = readln().split(" ").map(String::toInt)
        val g = gcd(x, y) // Reduce to coprime fraction
        val (xReduced, yReduced) = (x / g) to (y / g)
        
        (xReduced.solveForPrime(k) + yReduced.solveForPrime(k)).let { result ->
            println(if (result >= INF) -1 else result) // Print overall minimum steps or -1 if impossible
        }
    }
}

fun main() {
    cf2114f()
}


// https://github.com/VaHiX/CodeForces/
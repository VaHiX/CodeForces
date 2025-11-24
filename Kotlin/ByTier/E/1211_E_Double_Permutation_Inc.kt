// Problem: CF 1211 E - Double Permutation Inc.
// https://codeforces.com/contest/1211/problem/E

/**
 * Problem: Double Permutation Inc.
 * 
 * Algorithm: Binary search on the answer + greedy assignment
 * 
 * Time Complexity: O(n * log(max_value)) where max_value <= 2*10^5
 * Space Complexity: O(max_value) for counting array and other auxiliary arrays
 * 
 * Approach:
 * 1. First, we count occurrences of each number in the input array.
 * 2. Then, we binary search for the maximum possible size of the permutation P.
 *    For a given size k, we check if it's possible to form two copies of a permutation
 *    of size k from the array (each element of P must appear exactly twice).
 * 3. After finding the maximum size of P, we greedily assign colors:
 *    - First occurrence of each element in P gets 'R'
 *    - Second occurrence of each element in P gets 'G'
 *    - All other elements get 'B'
 */
private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readDouble() = readLn().toDouble()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }

fun main(args: Array<String>) {
    var n = readInt()
    var a = readInts()
    val MAX = 200010
    var cnt = IntArray(MAX)
    
    // Count occurrences of each number
    for (x in a) cnt[x]++
    
    // Binary search on the answer - maximum size of permutation P
    var low = 0
    var high = n
    while (low < high) {
        var mid = (low + high + 1) / 2
        var ok = true
        
        // Check if we can form a permutation of size mid
        // Each number from 1 to mid must appear exactly twice
        for (i in 1..mid) {
            if (cnt[i] != 2) {
                ok = false
                break
            }
        }
        
        if (ok) {
            // Validate that we can actually form two copies of the permutation
            var x = ArrayList<Int>() // to store the order of elements
            var y = 0 // current position in the first permutation
            var cc = IntArray(mid + 1) // count for each element so far
            
            for (v in a) {
                if (v <= mid) {
                    if (cc[v] == 0) {
                        x.add(v)
                    } else {
                        // Second time seeing this number
                        // It should be equal to the expected number in the permutation
                        if (x[y] != v) {
                            ok = false
                            break
                        }
                        y += 1
                    }
                    cc[v] += 1
                }
            }
        }
        
        if (ok) {
            low = mid
        } else {
            high = mid - 1
        }
    }
    
    // Assign colors based on the maximum possible permutation size
    var res = CharArray(n)
    var mid = low
    var x = ArrayList<Int>()
    var y = 0
    var cc = IntArray(mid + 1)
    
    for (it in 0..n - 1) {
        var v = a[it]
        if (v <= mid) {
            // Element belongs to permutation P
            if (cc[v] == 0) {
                // First occurrence -> red
                res[it] = 'R'
            } else {
                // Second occurrence -> green
                res[it] = 'G'
            }
            cc[v] += 1
        } else {
            // Element not in P -> blue
            res[it] = 'B'
        }
    }
    
    println(res.joinToString(""))
}


// https://github.com/VaHiX/CodeForces/
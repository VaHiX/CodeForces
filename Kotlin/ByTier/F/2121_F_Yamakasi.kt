// Problem: CF 2121 F - Yamakasi
// https://codeforces.com/contest/2121/problem/F

/**
 * Problem: Count subsegments with sum equal to s and maximum element equal to x.
 * 
 * Algorithm:
 * - Use prefix sums and a map to store indices of each prefix sum.
 * - For each element, update prefix sum and check if (current_sum - s) exists in the map,
 *   which indicates a valid subsegment ending at current index.
 * - Track maximum value in subsegments to ensure it equals x.
 * - Binary search on stored indices to count valid ranges efficiently.
 *
 * Time Complexity: O(n log n) per test case, due to binary search operations.
 * Space Complexity: O(n), for storing prefix sums and indices.
 */

import kotlin.math.*
class MapOfList<K, V> () {
    var m = hashMapOf<K, Int>()      // Maps prefix sum to index in v
    var v = mutableListOf<MutableList<V>>()  // Stores lists of indices for each prefix sum
    var n = 0                        // Counter for number of distinct prefix sums
    fun add(i : K, x : V) {
        if (m.containsKey(i)) v[m[i]!!].add(x)  // If prefix sum exists, add index to list
        else {
            m[i] = n++                    // New prefix sum, assign new index
            v.add(mutableListOf(x))       // Add new list with current index
        }
    }
    fun get(i : K) : MutableList<V> {
        if (!m.containsKey(i)) {          // If no list for this sum exists,
            m[i] = n++                    // create a new one
            v.add(mutableListOf())        // and add empty list
        }
        return v[m[i]!!]                  // Return the list of indices
    }
}

/**
 * Counts number of elements in this list that are in range [l, r]
 */
fun MutableList<Int>.cnt(l : Int, r : Int) : Int {
    var l1 = -1         // Left boundary for upper bound binary search ( > r )
    var r1 = this.size  // Right boundary for upper bound binary search
    while (r1 - l1 > 1) {
        val m = (l1 + r1) / 2
        if (this[m] > r) r1 = m     // Move left if element > r
        else l1 = m                 // Move right if element <= r
    }
    var l2 = -1         // Left boundary for lower bound binary search ( >= l )
    var r2 = this.size  // Right boundary for lower bound binary search
    while (r2 - l2 > 1) {
        val m = (l2 + r2) / 2
        if (this[m] >= l) r2 = m     // Move left if element >= l
        else l2 = m                  // Move right if element < l
    }
    return max(0, r1 - r2)   // Difference gives count in range [l, r]
}

fun main() {
    var t = readLine()!!.toInt()
    repeat(t) {
        var (n, s, x) = readLine()!!.split(' ').map{it.toLong()}
        var a = readLine()!!.split(' ').map{it.toLong()}.toMutableList()
        var v = MapOfList<Long, Int>()   // Map prefix sums to list of indices
        v.add(0, 0)                      // Add base case: prefix sum 0 at index 0
        var p = 0L                       // Current prefix sum
        var l = -1                       // Rightmost index where a[i] > x
        var r = -1                       // Leftmost index where a[i] == x
        var ans = 0L                     // Final answer
        for (i in 0 until n.toInt()) {
            p += a[i]                    // Update prefix sum
            
            if (a[i] > x) l = i          // Update rightmost index with value > x
            if (a[i] == x) r = i         // Update leftmost index with value == x
            
            ans += v.get(p - s).cnt(l + 1, r)   // Count valid subsegments ending here
            v.add(p, i + 1)              // Record current prefix sum and its index
        }
        println(ans)
    }
}


// https://github.com/VaHiX/CodeForces/
// Problem: CF 2103 F - Maximize Nor
// https://codeforces.com/contest/2103/problem/F

/*
 * Problem: F. Maximize Nor
 *
 * Task Description:
 * For each index i in an array of k-bit integers, find the maximum bitwise nor among all subarrays containing that index.
 *
 * Algorithms/Techniques:
 * - Segment Tree with Lazy Propagation for range maximum queries
 * - Bit manipulation using OR and NOT operations
 * - Dynamic programming-like approach maintaining possible values at each step
 *
 * Time Complexity: O(n * k * log n) per test case, where n is the size of array and k is number of bits.
 * Space Complexity: O(n) for segment tree storage and auxiliary arrays.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter

fun main(){
    val r=BufferedReader(InputStreamReader(System.`in`))
    val w=PrintWriter(System.out)
    val t=r.readLine().toInt()
    repeat(t){
        val (n,k)=r.readLine().split(" ").map{it.toInt()}
        val arr=r.readLine().split(" ").map{it.toInt()}
        val m=(1 shl k)-1  // Mask to keep only k bits
        val sm=SM(n)
        var aS=mutableListOf<Pair<Int,Int>>()
        for(i in 0 until n){
            val nS=mutableListOf<Pair<Int,Int>>()
            nS.add(Pair(arr[i],i))  // Start new subarray with current element
            for((c,l) in aS){
                // Calculate (c or arr[i]) inverted and masked to k bits
                val x=((c or arr[i]).inv()) and m
                var f=false
                for(j in nS.indices){
                    if(nS[j].first==x){
                        if(l<nS[j].second) nS[j]=Pair(x,l)
                        f=true
                        break
                    }
                }
                if(!f) nS.add(Pair(x,l))  // Add new value to list
            }
            for((v,l) in nS) sm.aU(l,i,v)  // Update segment tree with value v at range [l, i]
            aS=nS  // Overwrite old list with new one
        }
        val res=IntArray(n)
        sm.gR(1,0,n-1,res)  // Get results from segment tree
        w.println(res.joinToString(" "))
    }
    w.flush()
}

class SM(val s:Int){
    val seg=IntArray(s*4)  // Segment tree array
    val pen=IntArray(s*4)  // Lazy propagation array

    fun prop(x:Int,v:Int){
        if(v>seg[x]) seg[x]=v  // Propagate max value to node
        if(v>pen[x]) pen[x]=v  // Propagate lazy value
    }

    fun push(x:Int){
        if(pen[x]!=0){
            prop(x shl 1,pen[x])  // Push lazy to left child
            prop(x shl 1 or 1,pen[x])  // Push lazy to right child
            pen[x]=0  // Clear the lazy marker
        }
    }

    fun upd(x:Int,l:Int,r:Int,i:Int,j:Int,v:Int){
        if(i>r||j<l)return  // Out of range
        if(i<=l&&r<=j){ prop(x,v); return }  // Fully covered
        push(x)  // Push down lazy
        val mid=(l+r) ushr 1  // Midpoint
        upd(x shl 1,l,mid,i,j,v)  // Update left child
        upd(x shl 1 or 1,mid+1,r,i,j,v)  // Update right child
        seg[x]=if(seg[x shl 1]>=seg[x shl 1 or 1]) seg[x shl 1] else seg[x shl 1 or 1]  // Re-compute max
    }

    fun aU(l:Int,r:Int,v:Int){ upd(1,0,s-1,l,r,v) }  // Update range [l,r] with value v

    fun gR(x:Int,l:Int,r:Int,res:IntArray){
        if(l==r){ res[l]=seg[x]; return }  // Leaf node
        push(x)  // Push down lazy
        val mid=(l+r) ushr 1  // Midpoint
        gR(x shl 1,l,mid,res)  // Traverse left
        gR(x shl 1 or 1,mid+1,r,res)  // Traverse right
    }
}


// https://github.com/VaHiX/CodeForces/
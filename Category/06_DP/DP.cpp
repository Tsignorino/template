/*----------------------------------------- 入门 DP -----------------------------------------

爬楼梯：
> 【爬楼梯】(https://leetcode.cn/problems/climbing-stairs/)
> 【使用最小花费爬楼梯】(https://leetcode.cn/problems/min-cost-climbing-stairs/)
> 【组合总和 IV】(https://leetcode.cn/problems/combination-sum-iv/)
> 【统计构造好字符串的方案数】(https://leetcode.cn/problems/count-ways-to-build-good-strings/)
    · 从"可能得到的字符串长度"进行优化
> 【统计打字方案数】(https://leetcode.cn/problems/count-number-of-texts/)


打家劫舍：
> 【打家劫舍】(https://leetcode.cn/problems/house-robber/)
> 【删除并获得点数】(https://leetcode.cn/problems/delete-and-earn/)
> 【统计放置房子的方案数】(https://leetcode.cn/problems/count-number-of-ways-to-place-houses/)
> 【打家劫舍 II】(https://leetcode.cn/problems/house-robber-ii/)
> 【施咒的最大伤害】(https://leetcode.cn/problems/maximum-total-damage-with-spell-casting/)


最大子数组(子段)和：
> 【最大子数组和】(https://leetcode.cn/problems/maximum-subarray/)
> 【找到最大开销的子字符串】(https://leetcode.cn/problems/find-the-substring-with-maximum-cost/)
> 【任意子数组和的绝对值的最大值】(https://leetcode.cn/problems/maximum-absolute-sum-of-any-subarray/)
> 【K 次串联后最大子数组之和】(https://leetcode.cn/problems/k-concatenation-maximum-sum/)
> 【环形子数组的最大和】(https://leetcode.cn/problems/maximum-sum-circular-subarray/)
> 【乘积最大子数组】(https://leetcode.cn/problems/maximum-product-subarray/)
   子序列：https://leetcode.cn/problems/maximum-strength-of-a-group/

解法：
    1> Kadane 算法：定义状态 f[i] 表示以 a[i] 结尾的最大子数组和，不和 i 左边拼起来就是 f[i] = a[i]，反之就是
    f[i] = f[i-1] + a[i]，取最大值就得到了状态转移方程 f[i] = max(f[i−1], 0) + a[i]，答案为 max(f)。

    2> 前缀和：用前缀和减去最小前缀和
       维护当前的前缀和，更新答案（用当前的前缀和减去维护的最小前缀和），更新最小前缀和

    3> 线段树

class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)
        f = [0] * n
        f[0] = nums[0]
        for i in range(1, n):
            f[i] = max(f[i - 1], 0) + nums[i]
        return max(f)

        # 空间优化：
        ans = -inf  # 可以不选，ans = 0；必须选，ans = -inf（或者考虑数组第一项）
        f = 0
        for v in nums:
            f = max(f, 0) + v
            ans = max(ans, f)
        return ans

# 最大和的绝对值（额外维护一个最小即可）
class Solution:
    def maxAbsoluteSum(self, nums: List[int]) -> int:
        ans = fx = fn = 0
        for v in nums:
            fx = max(fx, 0) + v
            fn = min(fn, 0) + v
            ans = max(ans, fx, -fn)
        return ans

        # 前缀和解法（用前缀和最大值减去最小值即可）
        s = list(accumulate(nums, initial=0))
        return max(s) - min(s)

*/

/*----------------------------------------- 线性 DP -----------------------------------------

最长公共子序列（LCS）
最长递增子序列（LIS）

Problems:
> https://codeforces.com/contest/2061/problem/C

*/

/*----------------------------------------- 背包 DP -----------------------------------------

01背包：
下标从0开始，外层枚举物品，内层枚举背包容量

> 恰好装满型：【和为目标值的最长子序列的长度】(https://leetcode.cn/problems/length-of-the-longest-subsequence-that-sums-to-target/)

class Solution:
    def lengthOfLongestSubsequence(self, nums: List[int], target: int) -> int:
        f = [0] + [-inf] * target
        s = 0
        for v in nums:
            s = min(s + v, target)  # 优化
            for j in range(s, v - 1, -1):
                f[j] = max(f[j], f[j - v] + 1)
        return f[-1] if f[-1] > 0 else -1

    # 求最长长度： f[i] = max(f[i], f[i-v] + 1)
    # 求方案数：   f[i] += f[i-v]
    # 求是否有解： f[i] |= f[i-v]


分组背包：
下标从0开始，外层枚举组，中层枚举背包容量，内层枚举组内物品
（由于背包容量中层枚举，此时不清楚物品体积，所以应该在内层枚举物品时判断体积大小）


Problems：
> https://codeforces.com/contest/1862/problem/F    1800
> https://atcoder.jp/contests/abc383/tasks/abc383_f

*/

/*----------------------------------------- 区间 DP -----------------------------------------

枚举区间长度（从小区间到大区间），注意初始化

*/

/*----------------------------------------- 树形 DP -----------------------------------------

*/

/*----------------------------------------- 数位 DP -----------------------------------------

vector memo(m, vector<int>(1 << 10, -1));
auto dfs = [&](auto&& dfs, int i, int mask, bool isLimit, bool isNum) -> int {
    if (i == m) {
        return isNum;
    }
    if (!isLimit && isNum && memo[i][mask] != -1) {
        return memo[i][mask];
    }
    int res = 0;
    if (!isNum) { // 可以跳过当前位
        res = dfs(dfs, i + 1, mask, false, false);
    }
    int up = isLimit ? s[i] - '0' : 9;
    for (int k = isNum ? 0 : 1; k <= up; ++k) {
        if (mask >> k & 1) {
            continue;
        }
        res += dfs(dfs, i + 1, mask | (1 << k), isLimit && k == up, true);
    }
    if (!isLimit && isNum) {
        memo[i][mask] = res;
    }
    return res;
};
return dfs(dfs, 0, 0, true, false);

*/

/*----------------------------------------- 其他 DP -----------------------------------------

//// 划分型 DP

> 判定能否划分
> 最优划分
一般定义 f[i] 表示长为 i 的前缀 a[:i] 在题目约束下，分割出的最少（最多）子数组的个数（或者定义成分割方案数）。
枚举最后一个子数组的左端点，从 `f[i−1][L]` 转移到 `f[i][j]`，并考虑 a[L:j] 对最优解的影响。。
将数组分成（恰好/至多）k 个连续子数组，计算与这些子数组有关的最优值。
一般定义 `f[i][j]` 表示将长为 j 的前缀 a[:j] 分成 i 个连续子数组所得到的最优解。

*/

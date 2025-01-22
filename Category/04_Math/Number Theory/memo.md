# 数论


## 一些结论

> 第 k 个不是完全平方数的数字  $n = \lfloor k + \sqrt k + 0.5 \rfloor$。
> 


## 费马小定理

除法取模：
前提：1> 每步除法必须整除  2> mod 是质数  3> 除数和 mod 互质
        (a / b) % mod  <==> (a % mod * (b ^ -1)) % mod

p 为素数，gcd(a, p) = 1, 则 a^(p-1) = 1 (mod p)

-----------------------------------------------------------------------------------------------
Define: 如果一个线性同余方程 ax = 1(mod b)，则称 x 为 a mod b 的逆元

```cpp []
// 连续数字的逆元 从左往右 线性递推
vector<int> inv;
auto Inv(int n, int p = MOD) {
    inv.resize(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = p - inv[p % i] * 1ll * (p / i) % p;
    }
    return inv;
}
```
-----------------------------------------------------------------------------------------------


## 平方数之和

一个正整数 n 能表示为两个平方数之和的充要条件是：n 的所有形如 4k+3 的素数因子的幂次均为偶数。


## 约瑟夫环

```cpp []
ans = (ans + k - 1) % n + 1 // ans 表示旧环编号，n 表示旧环大小
```


## 四平方和定理
> 任意一个正整数都可以表示为至多四个整数的平方和
>
> 当且仅当 $n \ne 4^k(8m+7)$ 时，n 可以被表示为至多三个整数的平方和
> 因此，当 $n \ne 4^k(8m+7)$ 时，n 只能表示为四个整数的平方和


## 正因数个数

> 正整数的正因数的个数可以通过质因数分解来确定。
> 
> 如果一个正整数 n 的质因数分解是： $n={p_1}^{e_1}{p_2}^{e_2}\cdots{p_k}^{e_k}$ ，那么 n 的正因数的数量为  $(e_1+1)(e_2+1)\cdots(e_k+1)$。
>
> 题目：https://atcoder.jp/contests/abc383/tasks/abc383_d


## 素数

> 在 OI 领域具有完全正确性的做法，即当值域 V ≤ 2^78 时，我们可以通过固定底数为前 12 个素数 （2,3,5,7,11,13,17,19,23,29,31,37），来实现确定性判素。

> 所有大于 3 的素数都能够表示成 6n±1
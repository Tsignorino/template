namespace Sqrt {
    // x * x <= n，返回最大的 x
    ll mSqrt(ll n) {
        ll x = sqrt(n);
        while (x * x > n) {
            x--;
        }
        while ((x + 1) * (x + 1) <= n) {
            x++;
        }
        return x;
    }
    // x * (x+1) / 2 >= n，返回最小的 x
    ll mget(ll n) {
        ll x = sqrt(2.0L * n);
        while (x * (x + 1) / 2 < n) {
            x++;
        }
        while (x * (x - 1) / 2 + 1 > n) {
            x--;
        }
        return x;
    }
    // x * (x+1) / 2 > n，返回最小的 x
    ll mGet(ll n) {
        ll x = sqrt(2.0L * n);
        while (x * (x + 1) <= 2 * n) {
            x++;
        }
        return x;
    }
} // namespace Sqrt
using namespace Sqrt;

// 练习题：
// https://codeforces.com/contest/1862/problem/D    1300
// https://codeforces.com/contest/1857/problem/F    1600
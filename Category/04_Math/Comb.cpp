// 自动扩容类 （Mint）
//
struct Combinatorics {
    int n;
    vector<Mint> _fac, _ifac, _inv;

    explicit Combinatorics() : n {0}, _fac {1}, _ifac {1}, _inv {0} {}
    explicit Combinatorics(int n) : Combinatorics() { init(n); }

    void init(int m) {
        if (m <= n) {
            return;
        }
        _fac.resize(m + 1);
        _ifac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _ifac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _ifac[i - 1] = _ifac[i] * i;
            _inv[i] = _ifac[i] * _fac[i - 1];
        }
        n = m;
    }

    Mint fac(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _fac[m];
    }
    Mint ifac(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _ifac[m];
    }
    Mint inv(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _inv[m];
    }
    Mint binom(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fac(n) * ifac(m) * ifac(n - m);
    }
    Mint perm(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fac(n) * ifac(n - m);
    }
    Mint catalan(int n) {
        if (n <= 0) {
            return 0;
        }
        return binom(2 * n, n) - binom(2 * n, n - 1);
    }
} C;


// 预处理
//
namespace Combinatorics {
    i64 qpow(i64 a, i64 b, int p) {
        i64 res = 1;
        a = (a % p + p) % p;
        for (; b; b >>= 1, a = a * a % p) {
            if (b & 1) {
                res = a * res % p;
            }
        }
        return res;
    }

    const int MX = 2e5 + 1;

    vector<i64> Fac, iFac;
    auto init = [] {
        Fac.resize(MX); // Fac[i] = i!
        iFac.resize(MX); // iFac[i] = i!^-1

        Fac[0] = 1;
        for (int i = 1; i < MX; i++) {
            Fac[i] = Fac[i - 1] * i % MOD;
        }
        // 连续阶乘的逆元 从右往左 线性递推
        iFac[MX - 1] = qpow(Fac[MX - 1], MOD - 2, MOD);
        for (int i = MX - 1; i; i--) {
            iFac[i - 1] = iFac[i] * i % MOD;
        }
        return 0;
    }();

    i64 binom(int n, int m) {
        return n < m || m < 0 ? 0 : Fac[n] * iFac[m] % MOD * iFac[n - m] % MOD;
    }
    i64 perm(int n, int m) {
        return n < m || m < 0 ? 0 : Fac[n] * iFac[n - m] % MOD;
    }
    i64 catalan(int n) {
        return n < 0 ? 0 : binom(2 * n, n) - binom(2 * n, n - 1);
    }
};
using namespace Combinatorics;


// 操作次数较少，直接实现
//
namespace Combinatorics {
    // 小范围，不取模
    i64 binom_not_MOD(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        i64 ans = 1;
        for (int i = 0; i < m; i++) {
            ans = ans * (n - i) / (i + 1);
        }
        return ans;
    }


    // 求连续一组数的逆元
    vector<int> inv;
    auto Inv = [](int n = 2E5, int p = MOD) {
        inv.resize(n + 1);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i) {
            inv[i] = p - inv[p % i] * 1ll * (p / i) % p;
        }
        return inv;
    }();
    i64 qpow(i64 a, i64 b, int p) {
        i64 res = 1;
        a = (a % p + p) % p;
        for (; b; b >>= 1, a = a * a % p) {
            if (b & 1) {
                res = a * res % p;
            }
        }
        return res;
    }
    i64 binom(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        i64 ans = 1;
        for (int i = 1, j = n - m + 1; i <= m; i++, j++) {
            // ans = ans * j % MOD * qpow(i, MOD - 2, MOD) % MOD;
            ans = ans * j % MOD * inv[i] % MOD;
        }
        return ans;
    }
}; // namespace Combinatorics
using namespace Combinatorics;


// 逆元：
// https://www.cnblogs.com/zjp-shadow/p/7773566.html

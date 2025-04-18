// Manacher:
//
// 扩展回文串结尾下标和真实回文串终止位置的对应：真实回文串终止位置 = 扩展回文串结尾下标 / 2
// （真实回文串终止位置指不能满足条件的第一个字符）

// Manacher 应用：
//   · 求回文子串长度
//   · 求回文子串数量

auto Manacher(const string& s) {
    int m = s.size() * 2 + 1;
    string t(m, ' ');
    for (int i = 0, j = 0; i < m; i++) {
        t[i] = i & 1 ? s[j++] : '#';
    }

    vector<int> ans(m);
    for (int i = 0, c = 0, r = 0; i < m; i++) {
        int len = r > i ? min(ans[2 * c - i], r - i) : 1;
        while (i + len <= m && i - len >= 0 && t[i - len] == t[i + len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len, c = i;
        }
        ans[i] = len - 1;
    }
    return ans;
}

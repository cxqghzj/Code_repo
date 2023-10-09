#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <cmath>
#define int long long
using namespace std;
#ifdef ONLINE_JUDGE

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf;

#endif
int read() {
	int p = 0, flg = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		p = p * 10 + c - '0';
		c = getchar();
	}
	return p * flg;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
const int mod = 1e9 + 7;
void Mod(int &x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}
void solve() {
	int n = read(), m = read();
	int ans = 0;
	for (int i = 1; i <= min(n, (int)sqrt(m)); i++) {
		int len = m / i - 1, tp0, tp1;
		ans += ((tp0 = (1 + len) * len / 2)) % mod, Mod(ans);
		write(ans), putchar(32);
		ans += ((i + m) * (m - i + 1) / 2 - i * (len + 2) * (len + 1) / 2 + (m - i - len) * (i - 2) % mod + mod) % mod, Mod(ans);
		write(ans), puts("");
	}
	for (int i = 1; i <= min(m, (int)sqrt(n)); i++) {
		int len = n / i - 1, tp0, tp1;
		ans += ((tp0 = (1 + len) * len / 2)) % mod, Mod(ans);
		ans += ((i + n) * (n - i + 1) / 2 - i * (len + 2) * (len + 1) / 2 + (n - i - len) * (i - 2) % mod + mod) % mod, Mod(ans);
		write(ans), puts("");
	}
	ans += ((n - (int)sqrt(n)) * ((int)sqrt(n) + 1) / 2)
	write(ans), puts("");
}
signed main() {
	/* freopen("game.in", "r", stdin); */
	/* freopen("game.out", "w", stdout); */
	int T = read();
	while (T--) solve();
	return 0;
}

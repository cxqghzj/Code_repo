#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
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
const int N = 1e6 + 5, mod = 998244353;
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
array <int, N> fac, inv;
void init() {
	int n = 1e6;
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = pow_(fac[n], mod - 2, mod);
	for (int i = n; i; i--)
		inv[i - 1] = inv[i] * i % mod;
}
void Mod(int &x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}
int C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
array <int, N> idx;
signed main() {
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
	init();
	int T = read();
	while (T--) {
		int n = read(), m = read();
		for (int i = 1; i <= n; i++)
			idx[i] = pow_(pow_(2, i, mod) - 1, m, mod);
		if (n <= 1e6) {
			int sum = idx[n];
			for (int i = 1; i < n; i++) {
				sum -= pow_(-1, i + 1, mod) * C(n, i) * idx[n - i] % mod, Mod(sum);
			}
			write(sum), puts("");
		}
	}
	return 0;
}

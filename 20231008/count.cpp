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
const int N = 5005, M = 1e5 + 5, mod = 998244353;
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
array <int, M> fac, idx;
array <int, M> s, f;
/* array <array <int, N>, N> f, g; */
void Mod(int &x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}
signed main() {
	int n = read(), m = read();
	fac[0] = idx[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i % mod;
		idx[i] = idx[i - 1] * m % mod;
	}
	int maxn = 0;
	for (int i = 1; i <= m; i++) {
		int x = read();
		s[x + 1]++;
		maxn = max(maxn, x + 1);
	}
	/* for (int i = 1; i <= n; i++) */
		/* s[i] += s[i - 1]; */
	/* for (int i = n; i >= 1; i--) { */
		/* for (int j = i + 1; j <= n; j++) { */
			/* s[j] += pow_(-1, (j - i) & 1, mod) * s[i] % mod; */
			/* Mod(s[j]); */
		/* } */
	/* } */
	for (int i = 1; i <= n; i++)
		write(s[i]), putchar(32);
	puts("");
	int ans = 0;
	/* for (int i = 1; i <= n; i++) { */
		/* f[i] = fac[n - i + 1] % mod * idx[n - i] % mod - f[n - i] + mod % mod; */
		/* write(i), putchar(32); */
		/* write(f[i]), puts(""); */
		/* ans += f[i], Mod(ans); */
		/* for (int j = 1; j <= i; j++) { */
			/* f[i][j] = (s[j] * idx[i - j] % mod * fac[i - j + 1] % mod - g[i - j][i - j] + mod) % mod; */
			/* f[i][j] += f[i][j - 1], Mod(f[i][j]); */
			/* write(f[i][j]), putchar(32); */
		/* } */
		/* g[i][i] = g[i - 1][i - 1] + 2 * f[i][i] % mod; */
		/* Mod(g[i][i]); */
		/* g[i][i] = g[i][i] + g[i - 1][i - 1]; */
		/* write(g[i][i]); */
		/* puts(""); */
	/* } */
	/* for (int i = 1; i <= n; i++) { */
		/* for (int j = i + 1; j <= n; j++) */
			/* f[n][i] += ((i & 1) == (j & 1) ? 1 : -1) * f[n][j]; */
		/* write(i), putchar(32); */
		/* write(f[i]), puts(""); */
		/* ans += f[i], Mod(ans); */
		/* write(~(i & 1)), puts(""); */
		/* ans += pow_(-1, !(i & 1), mod) * f[i][i] % mod; */
		/* Mod(ans); */
	/* } */
	for (int i = 1; i <= n; i++) {
		f[i] = s[i] * fac[n - i + 1] % mod * idx[n - i] % mod;
		for (int j = 1; i + j - 1 <= n; j++) {
			int l1 = j - 1, l2 = n - (i + j - 1);
			write(i), putchar(32);
			write(j), putchar(32);
			write(l1), putchar(32);
			write(l2), puts("");
			f[i] -= f[l1] * pow_(fac[n - l1 + 1], mod - 2, mod) % mod, Mod(f[i]);
			f[i] -= f[l2] * pow_(fac[n - l2 + 1], mod - 2, mod) % mod, Mod(f[i]);
		}
		/* write(f[i]), puts(""); */
	}
	puts("");
	for (int i = 1; i <= n; i++)
		/* ans += f[i]; */
		write(f[i]), putchar(32);
	write(ans);
	puts("");
	write((idx[n] - ans + mod) % mod), puts("");
	return 0;
}

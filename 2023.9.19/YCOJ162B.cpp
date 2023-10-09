#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>
#define int long long
using namespace std;
#ifdef ONLINE_JUDGE

/* #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++) */
/* char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf; */

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
const int N = 405, mod = 1e9 + 7;
vector <vector <int> > f(N, vector <int> (N, 0));
char strbuf[N];
array <int, N> fac, inv;
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = pow_(fac[n], mod - 2, mod);
	for (int i = n; i; i--)
		inv[i - 1] = inv[i] * i % mod;
}
int C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
signed main() {
	int n = read();
	scanf("%s", strbuf);
	string s = strbuf;
	s = " " + s;
	init(n);
	f[n][n] = 1;
	for (int i = 1; i < n; i++)
		f[i][i] = s[i] != s[i + 1];
	for (int l = 1; l < n; l++) {
		for (int i = 1; i + l <= n; i++) {
			int j = i + l;
			f[i][j] = f[i + 1][j] * (s[i] != s[j + 1]) + f[i][j - 1] * (s[j] != s[j + 1]);
			if (f[i][j] >= mod) f[i][j] -= mod;
			for (int k = i + 1; k < j; k++) {
				if (s[k] == s[j + 1])
					continue;
				f[i][j] += f[i][k - 1] * f[k + 1][j] % mod * C(l, k - i) % mod;
				if (f[i][j] >= mod) f[i][j] -= mod;
			}
		}
	}
	write(f[1][n]), puts("");
	return 0;
}

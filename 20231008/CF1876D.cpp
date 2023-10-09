#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#define int long long
#define pii pair <int, int>
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
#define fi first
#define se second
const int N = 1e5 + 5, M = 2e6 + 5, mod = 998244353;
/* array <int, N> isl, f, idx; */
array <int, N> s;
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}

/*
signed main() {
	int n = read();
	for (int i = 1; i <= n; i++)
		s[i].fi = read(), s[i].se = i;
	sort(s.begin() + 1, s.begin() + 1 + n);
	for (int i = 1; i <= n; i++)
		idx[s[i].se] = i;
	int inv = pow_(2, mod - 2, mod);
	for (int i = n; i; i--) {
		bool flg = false;
		for (int j = 1; j * j <= s[i].se; j++) {
			if (i % j) continue;
			if (s[idx[j]].fi > s[i].fi) {
				flg = true;
				break;
			}
		}
		if (flg) continue;
		for (int j = 1; j * j <= s[i].se; j++) {
			if (i % j || isl[j] > s[i].fi) continue;
			isl[j] = s[i].fi;
			f[i] = (f[i] + inv - f[i] * inv % mod + mod) % mod;
		}
	}
	int ans = 0, fac = pow_(2, n, mod);
	for (int i = 1; i <= n; i++) {
		ans += fac * s[i].fi % mod * f[i] % mod;
		write(s[i].fi), putchar(32);
		write(fac * s[i].fi % mod * f[i] % mod), puts("");
		if (ans >= mod) ans -= mod;
	}
	write(ans), puts("");
	write(ans), puts("");
	return 0;
}
*/
signed main() {
	int n = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	/* sort(s.begin() + 1, s.begin() + 1 + n); */
		for (int i = 1; i <= n; i++)
		for (int j = i + i; j <= n; j += i)
			s[i] = max(s[i], s[j]);
	sort(s.begin() + 1, s.begin() + 1 + n);
	int ans = 0, k = 1;
	for (int i = 1; i <= n; i++) {
		ans = (ans + k * s[i] % mod) % mod;
		k = 2 * k % mod;
	}
	write(ans), puts("");


	return 0;
}

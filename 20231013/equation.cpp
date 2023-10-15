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
int _mod;
void Mod(int &x) {
	if (x >= _mod) x -= _mod;
	if (x < 0) x += _mod;
}
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}

void solve() {
	int a = read(), d = read(), n = read();
	int t = a, ans = 1;
	for (int i = 0; i < _mod && n; i++, n--) {
		ans = ans * t % _mod;
		t += d, Mod(t);
		if (t == 0) break;
	}
	/* for (int i = 0; i < n; i++) { */
		/* ans = ans * t % _mod; */
		/* t += d, Mod(t); */
	/* } */
	/* write(ans), puts(""); */
	if (!t && n) puts("0");
	else write(ans), puts("");
}
signed main() {
	freopen("equation.in", "r", stdin);
	freopen("equation.out", "w", stdout);
	int T = read(), p = read();
	_mod = p;
	while (T--) solve();
	return 0;
}

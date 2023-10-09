#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <set>
#define int long long
#define pii pair <int, int>
using namespace std;
#ifdef ONLINE_JUDGE

/* #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1+) */
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
void solve() {
	int n = read(), m = read(), k = read();
	if (k > 3) puts("0");
	else if (k == 1) puts("1");
	else if (k == 2) {
		if (m < n) write(m), puts("");
		else write(n - 1 + m / n), puts("");
	}
	else {
		if (m < n) puts("0");
		else write((m - n) / n * (n - 1) + (m - n) % n), puts("");
	}
}
signed main() {
	int T = read();
	while (T--) solve();
	return 0;
}

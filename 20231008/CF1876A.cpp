#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
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
void solve() {
	int n = read() - 1, sum = 0;
	for (int i = 1; i <= n; i++)
		sum += read();
	write(-sum), puts("");
}
int main() {
	int T = read();
	while (T--) solve();
	return 0;
}

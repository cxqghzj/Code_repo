#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <bitset>
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
const int N = 5005;
array <int, N> s;
bitset <N> vis;
int main() {
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	while (m--) {
		int op = read(), l = read(), r = read();
		if (op == 1) {
			s[l] = r;
			continue;
		}
		vis = 0;
		int minn = 0x7f7f7f7f, maxn = -1;
		bool flg = true;
		for (int i = l; i <= r; i++) {
			vis[s[i]] = 1;
			minn = min(minn, s[i]);
			maxn = max(maxn, s[i]);
		}
		for (int i = minn; i <= maxn; i++) {
			if (vis[i]) continue;
			flg = false;
		}
		if (flg && maxn - minn + 1 == r - l + 1) puts("damushen");
		else puts("yuanxing");
	}
	return 0;
}

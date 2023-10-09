#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
using namespace std;
/* #ifdef ONLINE_JUDGE */

/* #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++) */
/* char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf; */

/* #endif */
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
	int res = 0;
	array <int, 5> isl;
	isl.fill(4);
	for (int i = 1; i <= 8; i++) {
		string s;
		getline(cin, s);
		for (auto x : s) {
			if (x == 'A') isl[4]--;
			if (x == 'K') isl[3]--;
			if (x == 'Q') isl[2]--;
			if (x == 'J') isl[1]--;
		}
	}
	int ans1 = 0, ans2 = 0;
	int tp = 4;
	for (int k = 13; k; k--) {
		while (!isl[tp]) tp--;
		if (!tp) break;
		ans2 += tp;
		isl[tp]--;
	}
	for (int i = 1; i <= 4; i++)
		ans1 += i * isl[i];
	write(ans1), putchar(32);
	write(ans2), puts("");
}
int main() {
	freopen("bridge.in", "r", stdin);
	freopen("bridge.out", "w", stdout);
	int T = read();
	while (T--) solve();
	return 0;
}

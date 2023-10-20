#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <random>
#include <ctime>
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
signed main() {
	mt19937 rnd('N' + 'y' + 'a' + 'r' + 'u' + 'k' + 'o');
	int n = 5005, m = 5005;
	write(n), putchar(32);
	write(m), puts("");
	for (int i = 1; i <= n; i++)
		write((rnd() * rnd() * rnd()) % (int)(n)), putchar(32);
	for (int i = 1; i <= m; i++) {
		write((rnd() & 1) + 1), putchar(32);
		write(rnd() % n + 1), putchar(32);
		write(rnd() % n + 1), puts("");
	}

	return 0;
}

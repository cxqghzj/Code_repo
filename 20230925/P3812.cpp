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
const int N = 1e5 + 5;
namespace Bas {

array <int, N> prl;

void insert(int x) {
	for (int i = 63; ~i; i--) {
		if (~x & (1ll << i)) continue;
		if (!prl[i]) {
			prl[i] = x;
			return;
		}
		else x ^= prl[i];
	}
}
bool check(int x) {
	for (int i = 63; ~i; i--) {
		if (x & (1 << i)) {
			if (!prl[i]) return false;
			else x ^= prl[i];
		}
	}
	return true;
}
int query() {
	int ans = 0;
	for (int i = 63; ~i; i--)
		ans = max(ans ^ prl[i], ans);

	return ans;
}
}
signed main() {
	int n = read();
	for (int i = 1; i <= n; i++) {
		int x = read();
		Bas::insert(x);
	}
	write(Bas::query()), puts("");
	return 0;
}

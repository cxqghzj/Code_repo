#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <string>
using namespace std;
/* #ifdef ONLINE_JUDGE */

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf;

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
string read_() {
	string ans;
	char c = getchar();
	while (c < 'a' || c > 'z')
		c = getchar();
	while (c >= 'a' && c <= 'z') {
		ans += c;
		c = getchar();
	}
	return ans;
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
const int N = 5e5 + 5;
array <string, N> isl;
array <int, N> prl;
char strbuf[N];
int main() {
	/* freopen("reverse.in", "r", stdin); */
	/* freopen("reverse.out", "w", stdout); */
	int n = read(), m = read();
	string s = read_();
	prl[0] = 0;
	for (int i = 1; i <= m; i++) {
		prl[i] = read();
		isl[i] = s.substr(prl[i - 1], prl[i] - prl[i - 1]);
		/* printf("%s ", isl[i].c_str()); */
	}
	string ans;
	for (int i = m; i >= 1; i -= 2) {
		reverse(isl[i].begin(), isl[i].end());
		ans += isl[i];
	}
	for (int i = (m & 1) + 1; i <= m; i += 2)
		ans += isl[i];
	if (prl[m] != n) ans += s.substr(prl[m], n - prl[m] + 1);
	printf("%s\n", ans.c_str());
	return 0;
}

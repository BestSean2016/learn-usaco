/*
ID: stonegu1
LANG: C
PROG: crypt1
*/

#include <stdio.h>
char hash[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int check(int);
int main(void) {
    int n, i, j, tmp, s = 0;
    FILE *in = freopen("crypt1.in", "r", stdin);
    FILE *out = freopen("crypt1.out", "w", stdout);
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &tmp);
        hash[tmp] = 1;
    }

    for (i = 111; i < 1000; i++) {
        if (check(i)) continue;
        for (j = 11; j < 100; j++) {
            int fm, sm, m = i * j;
            if ((m > 9999)) break;
            if (check(j)||check(m)) continue;
            fm = i * (j % 10);
            if ((fm < 100)||(fm > 999)) continue;
            sm = i * (j / 10);
            if ((sm < 100)||(sm > 999)) continue;
            if (check(fm)||check(sm)) continue;
            s++;
        }
    }

    printf("%d\n", s);
    fclose(in);
    fclose(out);
    return 0;
}

int check(int x) {
    while (x) {
        if (!hash[x % 10]) return 1;
        x /= 10;
    }
    return 0;
}

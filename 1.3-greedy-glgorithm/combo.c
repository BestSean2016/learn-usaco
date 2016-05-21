/*
ID: stonegu1
LANG: C
PROG: crypt1
*/

#include <stdio.h>


int main(void) {
    int n, d[6], i;
    FILE *in = freopen("combo.in", "r", stdin);
    FILE *out = freopen("combo.out", "w", stdout);

    {//read input
        scanf("%d", &n);
        for (i = 0; i < 6; i++)
            scanf("%d", d + i);
    }



    fclose(in);
    fclose(out);
    return 0;
}


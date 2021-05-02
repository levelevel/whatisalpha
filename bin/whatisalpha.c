#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "ja_JP.UTF-8");
    wchar_t st = L'\x0000';
    wchar_t en = L'\x2ffff';
    char buf[8];
    for (wchar_t wc=st; wc<en; wc++) {
        int match = 0;
        if (wctomb(buf, wc)<0) {
            printf("U+%04x\tillegal\n", wc);
            continue;
        }
        printf("U+%04x\t", wc);
        if (iswcntrl(wc)) printf("0x%x", wc);
        else              printf("%C", wc);
        if (iswalpha (wc)) { fputs("\talpha", stdout); match = 1; }
        if (iswalnum (wc)) { fputs("\talnum", stdout); match = 1; }
        if (iswupper (wc)) { fputs("\tupper", stdout); match = 1; }
        if (iswlower (wc)) { fputs("\tlower", stdout); match = 1; }
        if (iswdigit (wc)) { fputs("\tdigit", stdout); match = 1; }
        if (iswxdigit(wc)) { fputs("\txdigit",stdout); match = 1; }
        if (iswpunct (wc)) { fputs("\tpunct", stdout); match = 1; }
        if (iswblank (wc)) { fputs("\tblank", stdout); match = 1; }
        if (iswspace (wc)) { fputs("\tspace", stdout); match = 1; }
        if (iswcntrl (wc)) { fputs("\tcntrl", stdout); match = 1; }
        if (iswdigit (wc)) { fputs("\tgraph", stdout); match = 1; }
        if (iswdigit (wc)) { fputs("\tprint", stdout); match = 1; }
        if (!match) fputs("\tNone", stdout);
        putchar('\n');
    }
    return 0;
}

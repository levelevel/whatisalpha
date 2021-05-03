#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <errno.h>
#include <assert.h>

#define DATSIZE 14
typedef struct {
    wchar_t wc;
    char *data[DATSIZE];
} UnicodeData_t;

const char UnicodeData[]  = "UnicodeData.txt";
const char UnicodeData2[] = "UnicodeData_ext.csv";

#define BUFLEN 1024
#define DELIM   ';'
// UnicodeData.txtから1行分を読み込む
int read_line(FILE *fp, UnicodeData_t *udata) {
    static char buf[BUFLEN];
    char *p = buf;
    if (fgets(buf, BUFLEN, fp)==NULL) return 0;
    udata->data[0] = buf;
    for (int i=1; i<DATSIZE && *p; p++) {
        if (*p==DELIM) {
            *p = '\0';
            udata->data[i++] = p+1;
        }
    }
    errno = 0;
    udata->wc = (wchar_t)strtol(buf, &p, 16);
    assert(errno==0);
    return 1;
}

int write_line(wchar_t wc) {
    int match = 0;
    char buf[8];
    if (wctomb(buf, wc)<0) {
        printf("U+%04x\tillegal\n", wc);
        return 0;
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
    return 1;
}

// UnicodeData_ext.txtに1行分を書き込む
// 2項目目に該当する文字をUTF-8で追加する。
void write_udata(FILE *fp2, UnicodeData_t *udata) {
    fputs(udata->data[0], fp2);
    if (iswcntrl(udata->wc)) fprintf(fp2, ";");
    else                     fprintf(fp2, ";%C", udata->wc);
    for (int i=1; i<DATSIZE; i++) fprintf(fp2, ";%s", udata->data[i]);
}

int main(void) {
    setlocale(LC_ALL, "ja_JP.UTF-8");
    UnicodeData_t udata;
    FILE *fp  = fopen(UnicodeData, "r");
    FILE *fp2 = fopen(UnicodeData2, "w");
    if (fp==NULL) {
        fprintf(stderr, "file open error: %s\n", UnicodeData);
        return 1;
    }
    if (fp2==NULL) {
        fprintf(stderr, "file open error: %s\n", UnicodeData2);
        return 1;
    }

    while (read_line(fp, &udata)) {
        wchar_t wc = udata.wc;
        write_udata(fp2, &udata);
        if (strstr(udata.data[1], ", First>")) {
            wchar_t st, en;
            st = wc;
            read_line(fp, &udata);
            en = udata.wc;
            if (st>=L'\xF0000' && strstr(udata.data[1], "Private Use")) {
                write_line(st);
                write_line(en);
            } else {
                for (wc=st; wc<=en; wc++) write_line(wc);
            }
        } else write_line(wc);
    }
    return 0;
}

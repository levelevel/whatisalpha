# whatisalpha どの文字がアルファベット？

Unicodeの[全文字](http://www.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt)に対してどれがアルファベットでどれが数値なのかを調べてみた。

glibcの[iswxxxxx](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/iswctype.3.html#lbAI)の結果で分類すると各クラスの総数は以下のようになる。
Noneはどのクラスにも属さないもの。

```text
alpha 127876
alnum 127886
upper 1939
lower 2344
digit 10
xdigit 22
punct 16431
blank 15
space 21
cntrl 67
graph 10
print 10
None 5930
```

- 漢字や仮名はalphaに分類されている。
- digitはASCIIコードのみの[0-9]に限られている。xdigitも同じ。
漢数字はもちろん全角数字は実はalphaに分類されている。
- 絵文字😊はpunctに分類されている。

## サンプル

```text
U+03a3	Σ	GREEK CAPITAL LETTER SIGMA	alpha	alnum	upper
U+03b2	β	GREEK SMALL LETTER BETA	alpha	alnum	lower
U+3041	ぁ	HIRAGANA LETTER SMALL A	alpha	alnum
U+3042	あ	HIRAGANA LETTER A	alpha	alnum
U+767e	百	CJK Ideograph	alpha	alnum
U+ff11	１	FULLWIDTH DIGIT ONE	alpha	alnum
U+ff21	Ａ	FULLWIDTH LATIN CAPITAL LETTER A	alpha	alnum	upper
U+ff41	ａ	FULLWIDTH LATIN SMALL LETTER A	alpha	alnum	lower
U+1f600	😀	GRINNING FACE	punct
```

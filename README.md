# whatisalpha どの文字がアルファベット？

[Unicode](https://ja.wikipedia.org/wiki/Unicode%E4%B8%80%E8%A6%A7%E8%A1%A8)の全文字（U+0000～U+2FFFF）に対してどれがアルファベットでどれが数値なのかを調べてみた。

glibcの[iswxxxxx](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/iswctype.3.html#lbAI)の結果で分類すると各クラスの総数は以下のようになる。
(Noneはどのクラスにも属さないもの。
ただし[wctomb](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/wctomb.3.html)関数が-1を返す文字は母数から除外してある。）

```text
alpha 127876
alnum 127886
upper 1939
lower 2344
digit 10
xdigit 22
punct 16090
blank 15
space 21
cntrl 67
graph 10
print 10
None 50502
```

- 漢字や仮名はalphaに分類されている。
- digitはASCIIコードのみの[0-9]に限られている。xdigitも同じ。
漢数字はもちろん全角数字は実はalphaに分類されている。
- 絵文字😊はpunctに分類されている。

## サンプル

```text
U+03a3	Σ	alpha	alnum	upper
U+03b2	β	alpha	alnum	lower
U+3041	ぁ	alpha	alnum
U+3042	あ	alpha	alnum
U+767e	百	alpha	alnum
U+ff10	０	alpha	alnum
U+ff11	１	alpha	alnum
U+ff12	２	alpha	alnum
U+ff21	Ａ	alpha	alnum	upper
U+1f600	😀	punct
U+1f601	😁	punct
U+1f602	😂	punct
```

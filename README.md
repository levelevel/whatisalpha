# whatisalpha どの文字がアルファベット？

[Unicode 13.0](https://unicode.org/versions/Unicode13.0.0/)の[全文字](http://www.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt)に対してどれがアルファベットでどれが数値なのかを調べてみた。

glibcの[iswxxxxx](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/iswctype.3.html#lbAI)の結果で分類すると各クラスの総数は以下のようになる。
Noneはどのクラスにも属さないもの。

```text
alpha 127876
alnum 127886
upper 1939
lower 2344
digit 10
xdigit 22
punct 10027
blank 15
space 21
cntrl 67
graph 137913
print 137927
None 5930
```

- 漢字や仮名はalphaに分類されている。仮名にupper/lowerの区別はない。
- digitはASCIIコードのみの[0-9]に限られている。xdigitも同じ。
漢数字はもちろん、全角数字はdigitではなくalphaに分類されている。
- 絵文字😊はpunctに分類されている。

## class_xxxxx.txt

UTF-8のテキストファイルだが、タブ区切りのcsvとして扱うことができる。

|カラム|内容|
|----|----|
|1|文字コード|
|2|文字|
|3|character name|
|4以降|該当する文字クラス|

### サンプル

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

## bin/UnicodeData_ext.csv

すべてのUnicode文字の情報を網羅した[UnicodeData.txt](http://www.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt)はASCII文字だけのファイルであるが、それにUTF-8でエンコードした文字を追加したのがbin/UnicodeData_ext.csvだ。
コードだけではなく実物の文字も併せて参照できたほうが検索もできるし何かと便利だろう。

区切り文字はオリジナルを踏襲して;のままとした。

UnicodeData.txtの仕様は[tr44/#UnicodeData.txt](http://www.unicode.org/reports/tr44/#UnicodeData.txt)にある。

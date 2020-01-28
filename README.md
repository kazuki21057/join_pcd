# 概要

指定フォルダ内にあるpcdファイルを結合するパッケージです．


# 要求仕様

- Ubuntu
- C++11

# インストール方法

```
$ git clone https://github.com/kazuki21057/join_pcd.git
$ cd join_pcd
$ mkdir build 
$ cd build
$ cmake ..
$ make
```

# 使い方

join_pcdがあるディレクトリパスを`JOIN_PCD_PATH`とします．

```
$ JOIN_PCD_PATH/build/join_pcd -i <input file name 1> <input file name 2> ... -d <directory path> -o <output file name>
```

### 引数

指定キーワード（`-i`, `-o`, `-d`）の後に，それぞれの情報を入力します．
引数の指定順番はバラバラで問題ありません．  
指定キーワードの説明は下記．

- -i: 結合したいpcdファイル名
    - 拡張子の有無は関係ありません．
    - ”\*”または”\*.pcd”を指定した場合は，指定ディレクトリ内にあるすべてのpcdファイルを入力とします．
- -o: 結合後の出力pcdファイル名
    - 拡張子の有無は関係ありません．
- -d: pcdファイルがあるディレクトリパス
    - 相対パス，絶対パスどちらも指定可能です．

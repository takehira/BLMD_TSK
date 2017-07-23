# macOS上での実行時の問題とその回避について
問題なさそうなコードなのに、macOS上で単純に`gcc main.c *.c`でビルドすると、`Segmentation fault: 11`でした。
せっかくなので追ってみることに。main.cにハント用のコードを追加しました。

## 問題
どうやら、Factoryで変数に代入する時点で、おかしなアドレスが代入されているようです。
Algo1、2に対して2回Factoryが呼ばれますが、同じアドレスになっているのはおかしいですね。
```sh
$ make test
./a.out
@Factory algo: 0xd3c1249 0x5caf8890
@Factory algo: 0xd3c1249 0x5caf8890
@main.algo1: 0xd3c1249 0x5caf8890
@main.test1: 0x3107e70 0x3107e90
@main.test1.pre_calc(100, 200): 300
@main.test1.post_calc(100, 200): -100
make: *** [test] Segmentation fault: 11
```

## 原因
変数スコープが原因でした。Factoryの中で下記のようになっていましたが、変数`algo`が被っていて、結果的にちゃんとnewが伝わりませんでした。
```c
lAlgo Factory(int algo_type){
	lAlgo algo;
	if(algo_type == ALGO1_TYPE){
		lAlgo algo = new_Algo1();
	}else if(algo_type == ALGO2_TYPE){
		lAlgo algo = new_Algo2();
	}else{
  :
```
そこで、`algo`に正しくコピーされるよう、下記のように変更することで解決しました。
```c
lAlgo Factory(int algo_type){
	lAlgo algo;
	if(algo_type == ALGO1_TYPE){
		lAlgo algo1 = new_Algo1();
		algo = algo1;
	}else if(algo_type == ALGO2_TYPE){
		lAlgo algo2 = new_Algo2();
		algo = algo2;
	}else{
  :
```
修正後の実行結果。
```
@Factory algo: 0xb9cee70 0xb9cee90
@Factory algo: 0xb9ceeb0 0xb9ceed0
@main.algo1: 0xb9cee70 0xb9cee90
@main.test1: 0xb9cee70 0xb9cee90
@main.test1.pre_calc(100, 200): 300
@main.test1.post_calc(100, 200): -100
algo1: -70
algo2: -1000
```

## まとめ
変数スコープ、ツールは誰も警告してくれませんでしたね。
気をつけるための知恵を考えていきましょう。

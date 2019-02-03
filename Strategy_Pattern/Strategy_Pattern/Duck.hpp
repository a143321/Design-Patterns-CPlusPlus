#pragma once
#include <iostream>
#include <assert.h>

// 鳴き声ふるまいインターフェース
class QuackBehavior
{
public:
	virtual ~QuackBehavior() = default;
	virtual void sound() const = 0;
};

// 静かな(アヒルなどの)ガーガー鳴き声クラス
class SmallQuack : public QuackBehavior
{
public:
	// 派生クラス側のオーバーライドメソッドにはoverride指定子を付ける (オーバーライド元の基底クラスを継承していない場合、コンパイルエラーとなる)
	void sound() const override
	{
		std::cout << "Normal sound : kua! kua!" << std::endl;
	}
};

// (アヒルなどの)ガーガー鳴き声クラス
class Quack : public QuackBehavior
{
public:
	void sound() const override
	{
		std::cout << "Noisy Sound : !!!!gua-gua!!!!" << std::endl;
	}
};

// キュッキュッ鳴る鳴き声クラス
class Squeak : public QuackBehavior
{
public:
	void sound() const override
	{
		std::cout << "Cute sound : kyu-kyu" << std::endl;
	}
};


// 無音鳴き声クラス
class MuteQuack : public QuackBehavior
{
public:
	void sound() const override
	{
		std::cout << "No sound : <<mute>>" << std::endl;
	}
};

// Duck（基底クラス)
// QuackBehaviorのインスタンスの解放は、基底クラスであるDuckクラスが受け持つ
class Duck
{
private:
	const QuackBehavior * quackBehavior = nullptr;

public:
	// 引数なしのコンストラクタは使用させない
	Duck() = delete;

	// インスタンス変数をコンストラクタで初期化する場合は、コンストラクタ初期化子を使用しましょう
	// 引数を1個とるコンストラクタの暗黙呼び出しを禁止するには，コンストラクタを“explicit”と宣言しておく． explicit宣言したコンストラクタは，明示的呼び出し（C obj(10);）でしか呼び出せなくなり， 暗黙呼び出しを記述するとコンパイル時エラーになる． 
	explicit Duck(QuackBehavior* behavior) : quackBehavior(behavior)
	{
		// コンストラクト時に渡される behaviorがnullptrであると、メンバ関数quack()呼び出すと落ちるため、assert文を追加する
		assert(behavior != nullptr);
	}

	// ポリモーフィズムを利用すべく作った基底クラスのデストラクタはvirtualが必要である
	// でないと、派生クラスのデストラクタが呼ばれない
	virtual ~Duck()
	{
		delete quackBehavior;
		std::cout << "Duck Destructed" << std::endl;
	};

	// quack関数は、派生クラスで、overrideさせないことを明示する
	// finalを指定した仮想メンバ関数は、派生クラスにてオーバーライドされたとき、文法違反として扱われる
	virtual void quack() const final
	{
		quackBehavior->sound();
	}
};

class RedHeadDuck : public Duck
{
public:
	RedHeadDuck(QuackBehavior* behavior) : Duck(behavior) {}

	~RedHeadDuck()
	{
		std::cout << "RedHeadDuck Destructed" << std::endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck(QuackBehavior* behavior) : Duck(behavior) {}

	~RubberDuck()
	{
		std::cout << "RubberDuck Destructed" << std::endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck(QuackBehavior* behavior) : Duck(behavior) {}

	~DecoyDuck()
	{
		std::cout << "DecoyDuck Destructed" << std::endl;
	}
};
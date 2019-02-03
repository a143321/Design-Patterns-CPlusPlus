#pragma once
#include <iostream>
#include <assert.h>

// �����ӂ�܂��C���^�[�t�F�[�X
class QuackBehavior
{
public:
	virtual ~QuackBehavior() = default;
	virtual void sound() const = 0;
};

// �Â���(�A�q���Ȃǂ�)�K�[�K�[�����N���X
class SmallQuack : public QuackBehavior
{
public:
	// �h���N���X���̃I�[�o�[���C�h���\�b�h�ɂ�override�w��q��t���� (�I�[�o�[���C�h���̊��N���X���p�����Ă��Ȃ��ꍇ�A�R���p�C���G���[�ƂȂ�)
	void sound() const override
	{
		std::cout << "Normal sound : kua! kua!" << std::endl;
	}
};

// (�A�q���Ȃǂ�)�K�[�K�[�����N���X
class Quack : public QuackBehavior
{
public:
	void sound() const override
	{
		std::cout << "Noisy Sound : !!!!gua-gua!!!!" << std::endl;
	}
};

// �L���b�L���b������N���X
class Squeak : public QuackBehavior
{
public:
	void sound() const override
	{
		std::cout << "Cute sound : kyu-kyu" << std::endl;
	}
};


// ���������N���X
class MuteQuack : public QuackBehavior
{
public:
	void sound() const override
	{
		std::cout << "No sound : <<mute>>" << std::endl;
	}
};

// Duck�i���N���X)
// QuackBehavior�̃C���X�^���X�̉���́A���N���X�ł���Duck�N���X���󂯎���
class Duck
{
private:
	const QuackBehavior * quackBehavior = nullptr;

public:
	// �����Ȃ��̃R���X�g���N�^�͎g�p�����Ȃ�
	Duck() = delete;

	// �C���X�^���X�ϐ����R���X�g���N�^�ŏ���������ꍇ�́A�R���X�g���N�^�������q���g�p���܂��傤
	// ������1�Ƃ�R���X�g���N�^�̈ÖٌĂяo�����֎~����ɂ́C�R���X�g���N�^���gexplicit�h�Ɛ錾���Ă����D explicit�錾�����R���X�g���N�^�́C�����I�Ăяo���iC obj(10);�j�ł����Ăяo���Ȃ��Ȃ�C �ÖٌĂяo�����L�q����ƃR���p�C�����G���[�ɂȂ�D 
	explicit Duck(QuackBehavior* behavior) : quackBehavior(behavior)
	{
		// �R���X�g���N�g���ɓn����� behavior��nullptr�ł���ƁA�����o�֐�quack()�Ăяo���Ɨ����邽�߁Aassert����ǉ�����
		assert(behavior != nullptr);
	}

	// �|�����[�t�B�Y���𗘗p���ׂ���������N���X�̃f�X�g���N�^��virtual���K�v�ł���
	// �łȂ��ƁA�h���N���X�̃f�X�g���N�^���Ă΂�Ȃ�
	virtual ~Duck()
	{
		delete quackBehavior;
		std::cout << "Duck Destructed" << std::endl;
	};

	// quack�֐��́A�h���N���X�ŁAoverride�����Ȃ����Ƃ𖾎�����
	// final���w�肵�����z�����o�֐��́A�h���N���X�ɂăI�[�o�[���C�h���ꂽ�Ƃ��A���@�ᔽ�Ƃ��Ĉ�����
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
#include "Duck.hpp"
#include <vector>
#include <memory>
#include <iostream>

void use_shared_ptr()
{
	std::unique_ptr<Duck> duck(new Duck(new SmallQuack()));
	std::unique_ptr<Duck> redHead(new RedHeadDuck(new Quack()));
	std::unique_ptr<Duck> rubber(new RubberDuck(new Squeak()));
	std::unique_ptr<Duck> decoy(new DecoyDuck(new MuteQuack()));

	duck->quack();
	redHead->quack();
	rubber->quack();
	decoy->quack();
}

void use_shared_ptr_list()
{
	std::unique_ptr<Duck> duck(new Duck(new SmallQuack()));
	std::unique_ptr<Duck> redHead(new RedHeadDuck(new Quack()));
	std::unique_ptr<Duck> rubber(new RubberDuck(new Squeak()));
	std::unique_ptr<Duck> decoy(new DecoyDuck(new MuteQuack()));

	std::vector<std::unique_ptr<Duck>> ducks;

	ducks.push_back(std::move(duck));
	ducks.push_back(std::move(redHead));
	ducks.push_back(std::move(rubber));
	ducks.push_back(std::move(decoy));

	// �Ȃ��Afor (auto f : v) �Ƃ���� f �� std::unique_ptr�̃R�s�[�ɂȂ�A�R���p�C���G���[�ƂȂ�܂�
	for (const auto& item : ducks)
	{
		item->quack();
	}
}

void use_shared_ptr_list_using_emplace_back()
{
	std::vector<std::unique_ptr<Duck>> ducks;

	ducks.emplace_back(new Duck(new SmallQuack()));
	ducks.emplace_back(new RedHeadDuck(new Quack()));
	ducks.emplace_back(new RubberDuck(new Squeak()));
	ducks.emplace_back(new DecoyDuck(new MuteQuack()));

	// �Ȃ��Afor (auto f : v) �Ƃ���� f �� std::unique_ptr�̃R�s�[�ɂȂ�A�R���p�C���G���[�ƂȂ�܂�
	for (const auto& item : ducks)
	{
		item->quack();
	}
}

int main()
{
	Duck* duck = new Duck(new SmallQuack());
	Duck* redHead = new RedHeadDuck(new Quack());
	Duck* rubber = new RubberDuck(new Squeak());
	Duck* decoy = new DecoyDuck(new MuteQuack());

	duck->quack();
	redHead->quack();
	rubber->quack();
	decoy->quack();

	// new���Ă���̂ŁAdelete��Y�ꂸ�ɂ��邱��
	delete duck;
	delete redHead;
	delete rubber;
	delete decoy;

	std::cout << "---- using std::unique_ptr----" << std::endl;
	use_shared_ptr();

	std::cout << "---- using std::unique_ptr with list ----" << std::endl;
	use_shared_ptr_list();

	std::cout << "---- using std::unique_ptr with list & vector::emplace_back ----" << std::endl;
	use_shared_ptr_list_using_emplace_back();

	return 0;
}

// NOLINTBEGIN

#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "IMateriaSource.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include <iostream>

int main()
{
	{
		std::cout << "*** SUBJECT TEST CASE: ***\n" << '\n';
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		ICharacter* me = new Character("me");
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);
		delete bob;
		delete me;
		delete src;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** FULL INVENTORY: ***\n" << '\n';
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		ICharacter* me = new Character("me");
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		tmp = src->createMateria("ice");
		me->equip(tmp);
		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		std::cout << "\nOut of range:" << '\n';
		me->use(4, *bob);
		me->use(4, *bob);
		me->use(42, *bob);
		me->use(100, *bob);
		me->use(-1, *bob);
		me->use(-100, *bob);
		std::cout << "\nUse again:" << '\n';
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		delete bob;
		delete me;
		delete src;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** EQUIP UNKNOWN MATERIAS: ***\n" << '\n';
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		ICharacter* me = new Character("me");
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		tmp = src->createMateria("icee");
		me->equip(tmp);
		tmp = src->createMateria("");
		me->equip(tmp);
		tmp = src->createMateria("ICE");
		me->equip(tmp);
		tmp = src->createMateria("CURE");
		me->equip(tmp);
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		std::cout << "\nOut of range:" << '\n';
		me->use(4, *bob);
		me->use(4, *bob);
		me->use(42, *bob);
		me->use(100, *bob);
		me->use(-1, *bob);
		me->use(-100, *bob);
		std::cout << "\nReuse:" << '\n';
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		delete bob;
		delete me;
		delete src;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** UNEQUIP MATERIAS: ***\n" << '\n';
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		ICharacter* me = new Character("me");
		AMateria* ice;
		ice = src->createMateria("ice");
		me->equip(ice);
		AMateria* tmp;
		tmp = src->createMateria("cure");
		me->equip(tmp);
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		std::cout << "\nUnequip 1 and 3:" << '\n';
		me->unequip(1);
		me->unequip(3);
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		std::cout << "\nRe-equip first ice:" << '\n';
		me->equip(ice);
		me->equip(ice);
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		std::cout << "\nUnequip all:" << '\n';
		me->unequip(0);
		me->unequip(1);
		me->unequip(2);
		me->unequip(3);
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		std::cout << "\nUnequip out of range:" << '\n';
		me->unequip(4);
		me->unequip(42);
		me->unequip(100);
		me->unequip(-1);
		me->unequip(-100);
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		delete bob;
		delete me;
		delete src;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** EMPTY MATERIA SOURCE: ***\n" << '\n';
		IMateriaSource* src = new MateriaSource();
		ICharacter* me = new Character("me");
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		delete bob;
		delete me;
		delete src;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** MULTIPLE CHARACTERS: ***\n" << '\n';
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		ICharacter* me = new Character("me");
		ICharacter* cloud = new Character("Cloud");
		ICharacter* tifa = new Character("Tifa");
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		cloud->equip(tmp);
		tmp = src->createMateria("ice");
		tifa->equip(tmp);
		tmp = src->createMateria("cure");
		tifa->equip(tmp);
		me->use(0, *cloud);
		cloud->use(0, *tifa);
		tifa->use(0, *me);
		tifa->use(1, *cloud);
		delete me;
		delete cloud;
		delete tifa;
		delete src;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** ONE MATERIA OWNED BY MULTIPLE CHARACTERS: ***\n"
		          << '\n';
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		ICharacter* me = new Character("me");
		ICharacter* cloud = new Character("Cloud");
		ICharacter* tifa = new Character("Tifa");
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		cloud->equip(tmp);
		me->use(0, *cloud);
		cloud->use(0, *me);
		delete me;
		cloud->use(0, *tifa);
		delete cloud;
		delete tifa;
		delete src;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** LEARN SAME MATERIA MULTIPLE TIMES: ***\n" << '\n';
		IMateriaSource* src1 = new MateriaSource();
		IMateriaSource* src2 = new MateriaSource();
		AMateria* ice = new Ice();
		AMateria* cure = new Cure();
		src1->learnMateria(ice);
		src1->learnMateria(ice);
		src1->learnMateria(cure);
		src2->learnMateria(ice);
		src2->learnMateria(cure);
		ICharacter* cloud = new Character("Cloud");
		AMateria* tmp;
		tmp = src1->createMateria("ice");
		cloud->equip(tmp);
		tmp = src1->createMateria("cure");
		cloud->equip(tmp);
		tmp = src2->createMateria("ice");
		cloud->equip(tmp);
		tmp = src2->createMateria("cure");
		cloud->equip(tmp);
		cloud->use(0, *cloud);
		cloud->use(1, *cloud);
		cloud->use(2, *cloud);
		cloud->use(3, *cloud);
		delete cloud;
		delete src1;
		delete src2;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** SAME MATERIA FOR LEARNING AND EQUIPPING: ***\n"
		          << '\n';
		IMateriaSource* src1 = new MateriaSource();
		AMateria* ice = new Ice();
		AMateria* cure = new Cure();
		src1->learnMateria(ice);
		src1->learnMateria(ice);
		src1->learnMateria(cure);
		ICharacter* cloud = new Character("Cloud");
		AMateria* tmp;
		cloud->equip(ice);
		tmp = src1->createMateria("ice");
		cloud->equip(tmp);
		tmp = src1->createMateria("cure");
		cloud->equip(tmp);
		cloud->equip(cure);
		cloud->equip(tmp);
		cloud->equip(ice);
		cloud->equip(cure);
		cloud->use(0, *cloud);
		cloud->use(1, *cloud);
		cloud->use(2, *cloud);
		cloud->use(3, *cloud);
		delete cloud;
		delete src1;
	}
	std::cout << '\n';
}

// NOLINTEND

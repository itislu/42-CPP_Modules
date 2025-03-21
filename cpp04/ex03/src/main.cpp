// NOLINTBEGIN

#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "IMateriaSource.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include "RcList.hpp"
#include <iostream>

RcList<AMateria*> g_ref_counter;

int main()
{
	{
		/* Call pure virtual function: */

		// Ice* ice = new Ice();
		// ice->~Ice();
		// ice->clone();

		// Ice derived;
		// AMateria* base = &derived;
		// base->~AMateria();
		// base->clone();
	}
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
	g_ref_counter.clear();
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
		std::cout << "\nEquip what doesn't fit in another:" << '\n';
		AMateria* full;
		full = src->createMateria("ice");
		me->equip(full);
		bob->equip(full);
		me->use(3, *bob);
		bob->use(0, *me);
		delete bob;
		delete me;
		delete src;
	}
	g_ref_counter.clear();
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
	g_ref_counter.clear();
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
	g_ref_counter.clear();
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
	g_ref_counter.clear();
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
	g_ref_counter.clear();
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
	g_ref_counter.clear();
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
	g_ref_counter.clear();
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
	g_ref_counter.clear();
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** COPY CHARACTER: ***\n" << '\n';
		MateriaSource src1;
		AMateria* ice = new Ice();
		AMateria* cure = new Cure();
		src1.learnMateria(ice);
		src1.learnMateria(cure);
		Character cloud("Cloud");
		Character tifa("Tifa");
		ICharacter* me = new Character("me");
		ICharacter* lea = new Character("Lea");
		cloud.equip(ice);
		tifa.equip(src1.createMateria("cure"));
		me->equip(new Ice());
		std::cout << "Before copying:" << '\n';
		cloud.use(0, tifa);
		tifa.use(0, cloud);
		me->use(0, *lea);
		lea->use(0, *me);
		std::cout << "\nAfter copying:" << '\n';
		cloud = tifa;
		*dynamic_cast<Character*>(lea) = *me;
		cloud.use(0, tifa);
		tifa.use(0, cloud);
		me->use(0, *lea);
		lea->use(0, *me);
		delete me;
		delete lea;
	}
	g_ref_counter.clear();
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** COPY MATERIA: ***\n" << '\n';
		MateriaSource src1;
		AMateria* ice = new Ice();
		AMateria* cure = new Cure();
		*cure = *ice;
		src1.learnMateria(ice);
		src1.learnMateria(cure);
		Character tifa("Tifa");
		tifa.equip(cure);
		tifa.equip(ice);
		std::cout << cure->getType() << '\n';
		std::cout << ice->getType() << '\n';
		tifa.use(0, tifa);
		tifa.use(1, tifa);
	}
	g_ref_counter.clear();
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** COPY MATERIASOURCE: ***\n" << '\n';
		IMateriaSource* src_ice = new MateriaSource();
		IMateriaSource* src_cure = new MateriaSource();
		MateriaSource src_empty(*src_cure);
		src_ice->learnMateria(new Ice());
		src_cure->learnMateria(new Cure());
		Character cloud("Cloud");
		cloud.equip(src_ice->createMateria("ice"));
		cloud.equip(src_cure->createMateria("ice"));
		cloud.equip(src_empty.createMateria("ice"));
		std::cout << "Before copying:" << '\n';
		cloud.use(0, cloud);
		cloud.use(1, cloud);
		cloud.use(2, cloud);
		cloud.unequip(0);
		cloud.unequip(1);
		cloud.unequip(2);
		std::cout << "\nAfter copying:" << '\n';
		src_empty = *src_cure;
		*dynamic_cast<MateriaSource*>(src_ice) = *src_cure;
		cloud.equip(src_ice->createMateria("cure"));
		cloud.equip(src_cure->createMateria("cure"));
		cloud.equip(src_empty.createMateria("cure"));
		cloud.use(0, cloud);
		cloud.use(1, cloud);
		cloud.use(2, cloud);
		delete src_ice;
		delete src_cure;
	}
	g_ref_counter.clear();
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** STACK ONLY: ***\n" << '\n';
		MateriaSource src;
		Ice ice;
		Cure cure;
		src.learnMateria(&ice);
		src.learnMateria(&cure);
		Character kamilla("Kamilla");
		Character me("me");
		kamilla.equip(&ice);
		kamilla.equip(&ice);
		kamilla.equip(&cure);
		kamilla.equip(&ice);
		kamilla.equip(&ice);
		kamilla.use(0, me);
		kamilla.use(2, me);
		me.equip(src.createMateria("ice"));
		(void)src.createMateria("cure");
		(void)src.createMateria("ice");
		(void)src.createMateria("cure");
	}
	g_ref_counter.clear();
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** NOT DELETING MATERIA: ***\n" << '\n';
		MateriaSource src;
		src.learnMateria(new Ice());
		(void)src.createMateria("ice");
		new Ice();
		new Ice();
		new Cure();
		new Cure();
	}
	g_ref_counter.clear();
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** DELETE SOURCE AND CHARACTER EARLY: ***\n" << '\n';
		IMateriaSource* src = new MateriaSource();
		AMateria* ice = new Ice();
		AMateria* cure = new Cure();
		src->learnMateria(ice);
		src->learnMateria(cure);
		AMateria* created = src->createMateria("ice");
		delete src;
		ICharacter* kamilla = new Character("Kamilla");
		ICharacter* me = new Character("me");
		kamilla->equip(created);
		kamilla->use(0, *kamilla);
		delete kamilla;
		me->equip(created);
		me->use(0, *me);
		delete me;
	}
	g_ref_counter.clear();
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
	{
		std::cout << "*** DELETE MATERIA MANUALLY: ***\n" << '\n';
		IMateriaSource* src = new MateriaSource();
		AMateria* ice = new Ice();
		src->learnMateria(ice);
		AMateria* created = src->createMateria("ice");
		delete src;
		delete ice;
		ICharacter* kamilla = new Character("Kamilla");
		kamilla->equip(created);
		kamilla->use(0, *kamilla);
		delete kamilla;
		delete created;
	}
	std::cout << "\n\n--------------------------------------------\n\n" << '\n';
}

// NOLINTEND

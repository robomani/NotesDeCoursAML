#include "Vector.h"

#include <cassert>
#include <iostream>

std::string elements[]{
	"First element",
	"Second element",
	"Third element",
	"Fourth element",
	"Fifth element",
	"Sixth element",
	"Seventh element",
	"Eighth element",
	"Ninth element"
};

void printVector(Vector& vector)
{
	std::cout << "Contenu du vecteur:" << std::endl;
	for (int i = 0; i < vector.size(); ++i)
	{
		std::cout << "  vector[" << i << "]=\"" << vector.get(i) << "\"" << std::endl;
	}
}

void test()
{
	Vector vector;

	assert(vector.size() == 0); // taille initiale devrait être 0
	assert(vector.capacity() == 1); // capacité initiale devrait être 1

	vector.add(elements[0]);
	printVector(vector);

	assert(vector.size() == 1); // taille devrait être 1
	assert(vector.capacity() == 1); // capacité devrait être encore 1
	assert(&vector.get(0) == &elements[0]); // premier élément

	vector.add(elements[1]);
	printVector(vector);

	assert(vector.size() == 2); // taille devrait être 2
	assert(vector.capacity() == 2); // capacité devrait être maintenant 2
	assert(&vector.get(0) == &elements[0]); // premier élément
	assert(&vector.get(1) == &elements[1]); // deuxième élément

	vector.insert(0, elements[2]);
	printVector(vector);

	assert(vector.size() == 3); // taille devrait être 3
	assert(vector.capacity() == 4); // capacité devrait être maintenant 4
	assert(&vector.get(0) == &elements[2]); // troisième élément
	assert(&vector.get(1) == &elements[0]); // premier élément
	assert(&vector.get(2) == &elements[1]); // deuxième élément

	vector.insert(1, elements[3]);
	printVector(vector);

	assert(vector.size() == 4); // taille devrait être 4
	assert(vector.capacity() == 4); // capacité devrait être encore 4
	assert(&vector.get(0) == &elements[2]); // troisième élément
	assert(&vector.get(1) == &elements[3]); // quatrième élément
	assert(&vector.get(2) == &elements[0]); // premier élément
	assert(&vector.get(3) == &elements[1]); // deuxième élément

	vector.insert(2, elements[4]);
	printVector(vector);

	assert(vector.size() == 5); // taille devrait être 5
	assert(vector.capacity() == 8); // capacité devrait être maintenant 8
	assert(&vector.get(0) == &elements[2]); // troisième élément
	assert(&vector.get(1) == &elements[3]); // quatrième élément
	assert(&vector.get(2) == &elements[4]); // cinquième élément
	assert(&vector.get(3) == &elements[0]); // premier élément
	assert(&vector.get(4) == &elements[1]); // deuxième élément

	vector.insert(vector.size(), elements[5]);
	printVector(vector);

	assert(vector.size() == 6); // taille devrait être 6
	assert(vector.capacity() == 8); // capacité devrait être encore 8
	assert(&vector.get(0) == &elements[2]); // troisième élément
	assert(&vector.get(1) == &elements[3]); // quatrième élément
	assert(&vector.get(2) == &elements[4]); // cinquième élément
	assert(&vector.get(3) == &elements[0]); // premier élément
	assert(&vector.get(4) == &elements[1]); // deuxième élément
	assert(&vector.get(5) == &elements[5]); // sixième élément

	vector.insert(0, elements[6]);
	printVector(vector);

	assert(vector.size() == 7); // taille devrait être 7
	assert(vector.capacity() == 8); // capacité devrait être encore 8
	assert(&vector.get(0) == &elements[6]); // septième élément
	assert(&vector.get(1) == &elements[2]); // troisième élément
	assert(&vector.get(2) == &elements[3]); // quatrième élément
	assert(&vector.get(3) == &elements[4]); // cinquième élément
	assert(&vector.get(4) == &elements[0]); // premier élément
	assert(&vector.get(5) == &elements[1]); // deuxième élément
	assert(&vector.get(6) == &elements[5]); // sixième élément

	vector.remove(0);
	printVector(vector);

	assert(vector.size() == 6); // taille devrait être 6
	assert(vector.capacity() == 8); // capacité devrait être encore 8
	assert(&vector.get(0) == &elements[2]); // troisième élément
	assert(&vector.get(1) == &elements[3]); // quatrième élément
	assert(&vector.get(2) == &elements[4]); // cinquième élément
	assert(&vector.get(3) == &elements[0]); // premier élément
	assert(&vector.get(4) == &elements[1]); // deuxième élément
	assert(&vector.get(5) == &elements[5]); // sixième élément

	vector.remove(vector.size() - 1);
	printVector(vector);

	assert(vector.size() == 5); // taille devrait être 5
	assert(vector.capacity() == 8); // capacité devrait être encore 8
	assert(&vector.get(0) == &elements[2]); // troisième élément
	assert(&vector.get(1) == &elements[3]); // quatrième élément
	assert(&vector.get(2) == &elements[4]); // cinquième élément
	assert(&vector.get(3) == &elements[0]); // premier élément
	assert(&vector.get(4) == &elements[1]); // deuxième élément

	vector.remove(vector.size() / 2);
	printVector(vector);

	assert(vector.size() == 4); // taille devrait être 4
	assert(vector.capacity() == 8); // capacité devrait être encore 8
	assert(&vector.get(0) == &elements[2]); // troisième élément
	assert(&vector.get(1) == &elements[3]); // quatrième élément
	assert(&vector.get(2) == &elements[0]); // premier élément
	assert(&vector.get(3) == &elements[1]); // deuxième élément

	vector.insert(vector.size() / 2, elements[7]);
	printVector(vector);

	assert(vector.size() == 5); // taille devrait être 5
	assert(vector.capacity() == 8); // capacité devrait être encore 8
	assert(&vector.get(0) == &elements[2]); // troisième élément
	assert(&vector.get(1) == &elements[3]); // quatrième élément
	assert(&vector.get(2) == &elements[7]); // huitième élément
	assert(&vector.get(3) == &elements[0]); // premier élément
	assert(&vector.get(4) == &elements[1]); // deuxième élément

	vector.clear();
	printVector(vector);

	assert(vector.size() == 0); // taille devrait être 0
	assert(vector.capacity() == 8); // capacité devrait être encore 8

	vector.add(elements[8]);
	printVector(vector);

	assert(vector.size() == 1); // taille devrait être 1
	assert(vector.capacity() == 8); // capacité devrait être encore 8
	assert(&vector.get(0) == &elements[8]); // neuvième élément
}

int main()
{
	test();
}

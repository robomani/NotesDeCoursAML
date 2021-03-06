#include "stdafx.h"
#include "Laboratoire3.h"

#include <Windows.h>

#include <iostream>
#include <string>

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	float total = 0;
	std::string reponse;
	do
	{
		std::string operation;
		while (!Laboratoire3::question("Choisissez une opération (+, -, * ou /): ", operation, "+", "-", "*", "/"))
		{
			std::cout << "Opération inconnue." << std::endl;
		}

		const float valeur = std::stof(Laboratoire3::question("Choisissez une valeur: "));
		switch (operation.front())
		{
			case '+': total += valeur; break;
			case '-': total -= valeur; break;
			case '*': total *= valeur; break;
			case '/': total /= valeur; break;
		}
		std::cout << "Le nouveau résultat est " << total << "." << std::endl;

		while (!Laboratoire3::question("Veux-tu continuer? (oui/non) ", reponse, "oui", "non"))
		{
			std::cout << "Réponse inconnue." << std::endl;
		}

	} while (reponse == "oui");
}


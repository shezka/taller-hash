#define DEBUG
#define TAM_TABLA_INI 100
#define UMBRAL_FC	  0.75

#include "DiccHashCerrado.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace aed2;

TEST(DiccHashCerrado, Vacio) {
	DiccHashCerrado<int> dh;
	ASSERT_EQ( dh.CantClaves(), 0);
}

TEST(DiccHashCerrado, Definido) {
	DiccHashCerrado<int> dh;

	ASSERT_FALSE(dh.Definido(""));
	ASSERT_FALSE(dh.Definido(" ") );
	ASSERT_FALSE(dh.Definido("hola") );

	dh.Definir("hola", 100);
	ASSERT_TRUE(dh.Definido("hola") );
	ASSERT_FALSE(dh.Definido("holas") );
	ASSERT_FALSE(dh.Definido("hol") );
}

TEST(DiccHashCerrado, Definir) {
	DiccHashCerrado<char> dhc;
	ASSERT_FALSE(dhc.Definido(""));

	dhc.Definir("a",'a');
	dhc.Definir("ab",'a');

	ASSERT_FALSE(dhc.Definido(""));
	ASSERT_TRUE(dhc.Definido("a"));
	ASSERT_TRUE(dhc.Definido("ab"));
	ASSERT_FALSE(dhc.Definido("abc"));
	ASSERT_FALSE(dhc.Definido("ab "));
	ASSERT_FALSE(dhc.Definido(" ab"));
}

TEST(DiccHashCerrado, StringVacio) {
	DiccHashCerrado<char> dhc;
	ASSERT_FALSE(dhc.Definido(""));

	dhc.Definir("",'a');
	ASSERT_TRUE(dhc.Definido(""));
	ASSERT_FALSE(dhc.Definido(" "));

	ASSERT_TRUE(dhc.Significado("") == 'a');

	dhc.Borrar("");
	ASSERT_FALSE(dhc.Definido(""));
}

TEST(DiccHashCerrado, Significado) {
	DiccHashCerrado<char> dhc;
	ASSERT_FALSE(dhc.Definido("a"));

	dhc.Definir("a",'a');
	dhc.Definir("ab",'a');

	ASSERT_TRUE( dhc.Significado("a") == 'a');
	ASSERT_TRUE( dhc.Significado("a") != 'b');
}

TEST(DiccHashCerrado, Borrar) {
	DiccHashCerrado<int> dhi;

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);

	ASSERT_TRUE( dhi.Definido("juanca") );
	ASSERT_TRUE( dhi.Definido("moncho")  );

	dhi.Borrar("juanca");
	ASSERT_FALSE(dhi.Definido("juanca") );
	dhi.Borrar("moncho");
	ASSERT_FALSE(dhi.Definido("moncho") );
}

TEST(DiccHashCerrado, CantClaves) {
	DiccHashCerrado<int> dhi;
	ASSERT_EQ( dhi.CantClaves(), 0);

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);
	ASSERT_EQ( dhi.CantClaves(), 2 );

	dhi.Definir("moncho",56);
	ASSERT_EQ( dhi.CantClaves(), 2);

	dhi.Borrar("juanca");
	ASSERT_EQ( dhi.CantClaves(), 1);

	dhi.Borrar("moncho");
	ASSERT_EQ( dhi.CantClaves(), 0);
}

TEST(DiccHashCerrado, Claves) {
	DiccHashCerrado<int> dhi;
	Lista<String> claves;

	claves = dhi.Claves();
	ASSERT_EQ( dhi.CantClaves(), 0);

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);

	claves = dhi.Claves();
	ASSERT_EQ( dhi.CantClaves(), 2);

	dhi.Definir("moncho",56);

	claves = dhi.Claves();
	ASSERT_EQ( dhi.CantClaves(), 2);

	dhi.Borrar("juanca");
	claves = dhi.Claves();

	ASSERT_EQ( dhi.CantClaves(), 1);

	dhi.Borrar("moncho");
	claves = dhi.Claves();

	ASSERT_EQ( dhi.CantClaves(), 0);
}


TEST(DiccHashCerrado, Colisiones_Unif) {
	DiccHashCerrado<int> dh;

	char delim = '\n';
	std::string archnom = "../data/uniforme.txt";
	
	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT_TRUE(archin.good());

	while(getline(archin,str,delim) && archin.good()) {
		//cout << "Definiendo: " << str << endl;
		dh.Definir(str, val);
		val++;

		if (val == 50)
			break;
	}
	archin.close();

	cout << endl;
	cout << "Cantidad de elementos definidos: ";
	cout << dh.CantClaves() << endl;
	ASSERT_EQ(dh.CantClaves(),val);

	cout << "Factor de carga: " << dh.factorCarga() << endl;
	cout << "Colisiones: " << dh.colisiones() << endl;
	ASSERT_TRUE(dh.colisiones() < 20);
}

TEST(DiccHashCerrado, Colisiones_Gauss) {
	DiccHashCerrado<int> dh;

	char delim = '\n';
	std::string archnom = "../data/gauss.txt";
	
	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT_TRUE(archin.good());

	while(getline(archin,str,delim) && archin.good()) {
		//cout << "Definiendo: " << str << endl;
		dh.Definir(str, val);
		val++;

		if (val == 50)
			break;
	}
	archin.close();

	cout << endl;
	cout << "Cantidad de elementos definidos: ";
	cout << dh.CantClaves() << endl;
	ASSERT_EQ(dh.CantClaves(),val);

	cout << "Factor de carga: " << dh.factorCarga() << endl;
	cout << "Colisiones: " << dh.colisiones() << endl;
	ASSERT_TRUE(dh.colisiones() < 30);
}

TEST(DiccHashCerrado, Colisiones_libretas) {
	DiccHashCerrado<int> dh;

	char delim = '\n';
	std::string archnom = "../data/libretas.txt";

	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT_TRUE(archin.good());

	while(getline(archin,str,delim) && archin.good()) {
		//cout << "Definiendo: " << str << endl;
		dh.Definir(str, val);
		val++;

		if (val == 50)
			break;
	}
	archin.close();

	cout << endl;
	cout << "Cantidad de elementos definidos: ";
	cout << dh.CantClaves() << endl;
	ASSERT_EQ(dh.CantClaves(), val);

	cout << "Factor de carga: " << dh.factorCarga() << endl;
	cout << "Colisiones: " << dh.colisiones() << endl;
	ASSERT_TRUE(dh.colisiones() < 26);
}

TEST(DiccHashCerrado, Redimensionado) {
	DiccHashCerrado<int> dh;

	// Podr�a ser con cualquier conjunto de datos
	std::string archnom = "../data/uniforme.txt"; // "../data/gauss.txt", "../data/libretas.txt"
	
	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT_TRUE(archin.good());

	while(getline(archin,str) && archin.good()) {
		dh.Definir(str, val);
		val++;
	}
	archin.close();

	ASSERT_EQ(dh.CantClaves(),val);

	Nat eval = 0;
	archin.open(archnom.c_str());
	while(getline(archin,str) && archin.good()) {
		ASSERT_TRUE(dh.Definido(str));
		ASSERT_EQ(dh.Significado(str),eval);
		eval++;
	}
	archin.close();

	ASSERT_EQ(eval,val);
}

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// KMC.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <direct.h> // WINDOWS ONLY

using namespace std;

void readKeys(string path, long *key1, long *key2, long *key3) {

	ifstream ParamFile;
	ParamFile.open(path);
	string line;

	
	if (ParamFile.is_open())
	{
		getline(ParamFile, line);
		long temp = ::atof(line.c_str());
		*key1 = temp;

		getline(ParamFile, line);
		temp = ::atof(line.c_str());
		*key2 = temp;

		getline(ParamFile, line);
		temp = ::atof(line.c_str());
		*key3 = temp;

		ParamFile.close();

	}

	else
		cout << "Unable to open file"; 
}

void generateKeys(string opath, int n) {

	ofstream keyFile;
	
	keyFile.open(opath);

	srand(time(0));
	long key1 = (rand() % 100000 + rand()% 321544 )* 33 * 7;
	keyFile << key1 << endl;

	srand(time(0)*2);
	long key2 = (rand() % 100000 + rand() % 32154) * 27 * 3;
	keyFile << key2 << endl;

	srand(time(0)*3);
	long key3 = (rand() % 1000 + rand() % 321544) * 33 * 7;
	keyFile << key3 << endl;

	keyFile << n << endl;

	keyFile.close();
}



void fixBug(string path , string path_fixed) {

	ofstream file2;
	file2.open(path_fixed);
	ifstream file;
	file.open(path);
	char chr = ' ';

	while (file.get(chr)) { file2 << chr; }

	file2 << endl << "                     ";
}

void fix_D_file(string path, string path_fixed) {

	ofstream file2;
	file2.open(path_fixed);
	ifstream file;
	file.open(path);
	char chr = ' '; string tmp;

	int nb_lignes = 0;
	while (getline(file, tmp)) { nb_lignes++; }

	file.close();
	file.open(path);

	for (int v=0;v<nb_lignes-1;v++)	{ 

			getline(file, tmp);
			file2 << tmp << endl;

	}

}



void read_Config_File(string path, int* n, int*  generate_Keys, int* profondeur_de_la_regen , int* remove_status) {

	ifstream ParamFile;
	ParamFile.open(path);
	string line;


	if (ParamFile.is_open())
	{
		getline(ParamFile, line);
		getline(ParamFile, line);
		int temp = ::atof(line.c_str());
		*n = temp;

		getline(ParamFile, line);
		getline(ParamFile, line);
		temp = ::atof(line.c_str());
		*generate_Keys = temp;

		getline(ParamFile, line);
		getline(ParamFile, line);
		temp = ::atof(line.c_str());
		*profondeur_de_la_regen = temp;

		getline(ParamFile, line);
		getline(ParamFile, line);
		temp = ::atof(line.c_str());
		*remove_status = temp;

		ParamFile.close();

	}

	else
		cout << "Unable to open CONFIG file";


}



void Cphase1(int key1, string path, string opath){

	string printable = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";
	int it = 0;
	string newPrintable = "";
	string newC= "a";

	for (int a = 0; a <= printable.length(); a++) {

		it = ((a + key1) % printable.length());
		//it = ((a + 2) % printable.length());
		//cout << it << endl;
		newC = printable[it];
		newPrintable.append(newC);

	}
	
	//cout << newPrintable << endl;

	ofstream temp;
	temp.open(opath);

	ifstream cible;
	cible.open(path);

	string line;

	if (cible.is_open())
	{
		int cibleLenght = 0;
		char chr = '0';
		int v = 0;

		while (cible.get(chr)) {
			
			if (chr == '\n') { temp << chr; }
			else {
				while (chr != printable[v]) { v++; if (v>printable.length()) { break; } }
				
				if (v <= printable.length()) {
					temp << newPrintable[v];
				}
				else { temp << chr; }

			}

			
			v = 0;

		}

		cible.close();
	}

	else
		cout << "Unable to open file a.txt";

}

void Cphase2(int key2, string path, string opath) {

	char chr = '0';

	ifstream cible;
	cible.open(path);

	int longeurFichier = 0;
	while (cible.get(chr)) { longeurFichier++; }

	ofstream temp3;
	temp3.open(opath);

	cible.close();
	cible.open(path);

	int currentChunck = 0;
	int chunck = key2 % 5;
	if (chunck == 0 || chunck == 1) { chunck = 2; }
    int arret = (longeurFichier / chunck);  

	if (cible.is_open()){
		
		for (int a = 1; a <= arret ; a++) {

			string method = "";

			for (int b = 0; b < chunck; b++){

				cible.get(chr);
				method.push_back(chr);
				
			}

			currentChunck++;

			string temp;
			temp = method;
			method[0] = temp[chunck-1];
			method[chunck-1] = temp[0];

			temp3 << method;

		}

				
			cible.close();
	}

	else
		cout << "Unable to open file temp in CPHASE 2" << endl;
		
}

void Cphase3(int key3, string path, string opath) {

	char chr = '0';

	ifstream cible;
	cible.open(path);

	int longeurFichier = 0;
	while (cible.get(chr)) { longeurFichier++; }

	ofstream Output;
	Output.open(opath);

	cible.close();
	cible.open(path);


	int saut = key3 % 6;
	//saut = 11;
	if (saut == 0 || saut == 1 || saut == 2 || saut == 3) { saut = 4; }

	int sautIt = saut;
	int fix=0;
	
	if (cible.is_open()) {

		for (int a = 0 ; a < longeurFichier; a++ ) {
			
			cible.get(chr);
			Output << chr;
			if ((sautIt == saut) && (chr != 'a' && chr != 'b' && chr != 'c' && chr != 'd') && (fix < longeurFichier-5 ) ) { Output << "abcd"; sautIt = 0; }
			sautIt++; fix++;

		}


		cible.close();
	}

	else
		cout << "Unable to open file temp in CPHASE 3" << endl;

}

void Dphase1(int key1, string path, string opath) {

	string printable = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ";
	int it = 0;
	string newPrintable = "";
	string newC = "a";

	for (int a = 0; a <= printable.length(); a++) {

		it = ((a + key1) % printable.length());
		//it = ((a + 2) % printable.length());
		//cout << it << endl;
		newC = printable[it];
		newPrintable.append(newC);

	}
	

	ofstream temp;
	temp.open(opath);

	ifstream cible;
	cible.open(path);
	string line;

	if (cible.is_open())
	{
		int cibleLenght = 0;
		char chr = '0';
		int v = 0;

		while (cible.get(chr)) {

			if (chr == '\n') { temp << chr; }
			else {
				while (chr != newPrintable[v]) { v++; }
					
					if (v <= printable.length()) {
						temp << printable[v];
					}
					else { temp << chr; }
			}

			
			v = 0;

		}

		cible.close();
	}

	else
		cout << "Unable to open file";

}

void Dphase2(int key2, string path, string opath) {


	char chr = '0';

	ifstream cible;
	cible.open(path);

	int longeurFichier = 0;
	while (cible.get(chr)) { longeurFichier++; }

	ofstream temp4;
	temp4.open(opath);

	cible.close();
	cible.open(path);

	int currentChunck = 0;
	int chunck = key2 % 5;
	if (chunck == 0 || chunck == 1) { chunck = 2; }
	int arret = (longeurFichier / chunck);

	if (cible.is_open()) {

		for (int a = 1; a <= arret; a++) {

			string method = "";

			for (int b = 0; b < chunck; b++) {

				cible.get(chr);
				method.push_back(chr);

			}
			currentChunck++;

			string temp;
			temp = method;
			method[0] = temp[chunck - 1];
			method[chunck - 1] = temp[0];

			temp4 << method;

		}


		cible.close();
	}

	else
		cout << "Unable to open file temp in DPHASE 2" << endl;

}

void Dphase3(int key3, string path, string opath) {

	char chr = '0';

	string tmp = "";
	string toFind = "abcd";

	ifstream cible;
	cible.open(path);

	int longeurFichier = 0;
	while (cible.get(chr)) { longeurFichier++; }

	ofstream Output;
	Output.open(opath);

	cible.close();
	cible.open(path);
	

	if (cible.is_open()) {

		int reset = 0;

		for (int v = 0; v < longeurFichier; v++) {

			if(v < (longeurFichier-200)){

				reset++;

				cible.get(chr);
				tmp.push_back(chr);

				if(reset==200){


					for (int b = 0; b < 60; b++) {

					string::size_type i = tmp.find(toFind);

					if (i != string::npos)
						tmp.erase(i, toFind.length());
					}
					reset = 0;
					Output << tmp ;
					tmp = "";
				}

			}

			else {
				if(cible.get(chr))tmp.push_back(chr);
			}

		}


		for (int b = 0; b < 60; b++) {

			string::size_type i = tmp.find(toFind);

			if (i != string::npos)
				tmp.erase(i, toFind.length());
		}


		Output << tmp;
		 

		cible.close();
	}

	else
		cout << "Unable to open file temp in DPHASE 3" << endl;

}



void Crypter(string path_to_crypt_file, string path_to_keys, string output_path) {

	long key1 = 0, key2, key3, key4;
	readKeys(path_to_keys, &key1, &key2, &key3);

	if ((key1 != 0) && (key2 != 0) && (key3 != 0) ) {

		string tmp1 = "tmp/Ctemp1.txt";
		Cphase1(key1, path_to_crypt_file, tmp1);
		string tmp2 = "tmp/Ctemp2.txt";
		Cphase3(key3, tmp1, tmp2);
		Cphase2(key2, tmp2, output_path);
		

	}

	else {
		cout << "unable to open keys" << endl;
	}



}

void DeCrypter(string path_to_decrypte_file, string path_to_keys, string output_path) {

	long key1 = 0, key2 = 0, key3 = 0, key4 = 0;
	readKeys(path_to_keys, &key1, &key2, &key3);
	int profondeurCryptage = 5;

	if ((key1 != 0) && (key2 != 0) && (key3 != 0)) {

		string dtmp1 = "tmp/dtmp1.txt";
		string dtmp2 = "tmp/dtmp2.txt";
		Dphase2(key2, path_to_decrypte_file, dtmp1);
		Dphase3(key3, dtmp1, dtmp2);
		Dphase1(key1, dtmp2, output_path);

	}

	else {
		cout << "unable to open keys" << endl;
	}



}



void clean() {

	remove("tmp/Ctemp1.txt");
	remove("tmp/Ctemp2.txt");
	remove("tmp/dtmp1.txt");
	remove("tmp/dtmp2.txt");

}


int Verify(string Original, string Dfile) {

	ifstream Original_file;
	Original_file.open(Original);
	ifstream Decrypted_file;
	Decrypted_file.open(Dfile);
	string temp, temp2;

	int nb_lignes = 0; char chr;

	while (getline(Original_file, temp)) { nb_lignes++; }
	//cout << nb_lignes << endl;
	Original_file.close();
	Original_file.open(Original);

	if(Original_file.is_open() && Decrypted_file.is_open()){

		for (int k = 0; k < nb_lignes - 1; k++) {

		getline(Original_file, temp);  getline(Decrypted_file, temp2);
		//cout << temp << endl << temp2 << endl;
		if (temp != temp2) { k = nb_lignes; return 0; }
	
	}

	return 1;
	}

	else { cout << "unable to open the original and decrypted file in the vErify phase" << endl;  }


}

int main()
{

	cout << "KMC Chiper V.02" << endl << endl;


	int a,b;
	string path = "a.txt";
	string path_fixed = "toCrypt.txt";
	string C_output_path = "C_Output.txt";
	string D_output_path = "D_Output_temp.txt";
	string D_output_path_fixed = "D_Output.txt";

	fixBug(path, path_fixed);

	int n = 1;	int generate_keys = 0;  int step = 1; int if_too_long = 0; int profondeur_de_la_regen;
	int remove_status;

	string path_to_config = "config.txt"; string path_to_keys = "pass.mkey";
	read_Config_File(path_to_config, &n, &generate_keys, &profondeur_de_la_regen, &remove_status);

	

	cout << "Debut du cryptage ....." << endl << endl;
	cout << "Profondeur du Cryptage chosie : " << n << endl;
	cout << "Generation de cle : " << generate_keys << endl;
	cout << "Limite de regeneration : " << n << endl << endl;


	while (step == 1 && if_too_long < profondeur_de_la_regen){

	if (generate_keys == 1) { generateKeys(path_to_keys, n); }

	for (a = 0; a <= n; a++) {
		if (a == 0) {Crypter(path_fixed, path_to_keys, C_output_path);}
		else {Crypter(C_output_path, path_to_keys, C_output_path);}
		if(a%3 == 0)cout << "Cryptage - Pronfondeur actuelle : " << a << endl ;
	}


	cout <<  endl << endl;


	for (b = 0; b <= n; b++) {
		if (b == 0) { DeCrypter(C_output_path, path_to_keys, D_output_path); }
		else { DeCrypter(D_output_path, path_to_keys, D_output_path); }
		if (b % 3 == 0)cout << "Decryptage - Pronfondeur actuelle : " << b << endl ;
	}
	

	//Apply the fix 
	fix_D_file(D_output_path, D_output_path_fixed);

	//clean temp files

	const char * c = D_output_path.c_str();
	remove(c);
	if(remove_status == 1)clean();
	
	int veri = 1;
	veri = Verify(path_fixed, D_output_path_fixed);
	
	if (veri == 0) {
		cout << " !-! Attention ! - ! Cle de cryptage invalide pour ce fichier !-! Activer la generation automatique" << endl;
		cout << " Generation de nouvelles cles........" << endl; int veri = 1; step = 1; generate_keys = 1; if_too_long++;
		if (if_too_long == profondeur_de_la_regen - 1) { cout << " Arret de la tentative .... limite atteinte ....." << endl; }
	}

	else {
	cout << "Cryptage complet " << endl; step = 0;
	}

	}

	cin >> a;

    return 0;
}



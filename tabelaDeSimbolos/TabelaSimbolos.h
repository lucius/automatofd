#ifndef TABELADESIMBOLOS_H_
#define TABELADESIMBOLOS_H_

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "StructSimbolo.h"



class TabelaSimbolos
{
	public:
		static TabelaSimbolos
		getInstance( );

	private:
		std::vector<std::string>
		mPrimeiroParser;

		std::list<StructSimbolo>
		simbolos;

		TabelaSimbolos( );
		
		void
		carregaArquivoConfiguracao( );
		
		void
		criaTabelaHash( );
};

#endif /*TABELADESIMBOLOS_H_*/

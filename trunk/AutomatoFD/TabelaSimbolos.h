#ifndef TABELADESIMBOLOS_H_
#define TABELADESIMBOLOS_H_

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "StructSimbolo.h"



class TabelaSimbolos
{
	public:
		static TabelaSimbolos
		getInstance( );

		const std::string 
		procuraSimbolo( std::string );

	private:
		std::vector<std::string>
		mPrimeiroParser;

		std::map<std::string, std::string>
		simbolos;

		TabelaSimbolos( );
		
		void
		carregaArquivoConfiguracao( );
		
		void
		criaTabelaHash( );
};

#endif /*TABELADESIMBOLOS_H_*/

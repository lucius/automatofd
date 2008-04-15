#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "StructSimbolo.h"
#include "TabelaSimbolos.h"



TabelaSimbolos::TabelaSimbolos( )
{
	this->carregaArquivoConfiguracao( );
	this->criaTabelaHash( );
}

TabelaSimbolos
TabelaSimbolos::getInstance( )
{
	static TabelaSimbolos
	tabela;

	return tabela;
}

const std::string
TabelaSimbolos::procuraSimbolo( std::string tokenProcurado )
{
	static TabelaSimbolos
	tabela;

	std::map<std::string, std::string>::iterator
	iteradorBusca;

	iteradorBusca = tabela.simbolos.find( tokenProcurado );
	
	if ( iteradorBusca != tabela.simbolos.end() )
	{
		return iteradorBusca->second;
	}
	else
	{
		return "IDENTIFICADOR";
	}
}

void
TabelaSimbolos::carregaArquivoConfiguracao( )
{
	std::ifstream
	arquivoConfiguracao ( "./data/pascal.conf", std::ifstream::in );
	
	std::string
	_buffer;
	
	if ( !arquivoConfiguracao.is_open() ) throw ( "Fuma um cigarro! configurationFile não pode ser aberto!! Sucesso;;" );
	
	arquivoConfiguracao.seekg( 0, std::ios::beg );
	
	while ( !arquivoConfiguracao.eof() )
	{
		arquivoConfiguracao >> _buffer;
		this->mPrimeiroParser.push_back( _buffer );
	}

	arquivoConfiguracao.close( );
}

void
TabelaSimbolos::criaTabelaHash( )
{
	size_t
	posicao;
	
	std::vector<std::string>::iterator
	iteradorPrimeiroParser;
	
	std::list<StructSimbolo>::iterator
	iteradorSimbolos;
	
	std::string
	caracterProcurado = "@";
	
	std::string
	tipoTemporario;
	
	/*StructSimbolo
	exemploInsercao;*/

	for (iteradorPrimeiroParser = this->mPrimeiroParser.begin(); iteradorPrimeiroParser != this->mPrimeiroParser.end(); ++iteradorPrimeiroParser)
	{
		posicao = iteradorPrimeiroParser->find( caracterProcurado );

		if ( posicao != std::string::npos )
		{
			tipoTemporario = iteradorPrimeiroParser->substr( posicao+1, iteradorPrimeiroParser->size() );
			++iteradorPrimeiroParser;
		}

		/* Teste de Insercao em uma Lista */
		/*
		exemploInsercao.tipo = tipoTemporario;
		exemploInsercao.nome = *iteradorPrimeiroParser;

		this->simbolos.push_back( exemploInsercao );
		*/

		this->simbolos.insert ( std::pair<const std::string, const std::string> (*iteradorPrimeiroParser, tipoTemporario) );

	}
	
	/* Imprimindo a Lista */
	/*
	for (iteradorSimbolos = simbolos.begin(); iteradorSimbolos != simbolos.end(); ++iteradorSimbolos)
	{
		std::cout << iteradorSimbolos->nome << " - " << iteradorSimbolos->tipo << std::endl;
	}
	*/
}

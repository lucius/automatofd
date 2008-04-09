#include <fstream>
#include <iostream>
#include <list>
#include <regex.h>
#include <string>

#include "AutomatoFD.h"



AutomatoFD::AutomatoFD(std::string caminho)
{
	try
	{
		this->carregaCodigo( caminho );
	}
	catch ( std::string erro )
	{
		std::cout << erro << std::endl;
		exit (1);
	}

	this->token.clear( );
	this->estadoS( );
}

AutomatoFD::~AutomatoFD()
{
}

void
AutomatoFD::carregaCodigo( std::string caminho )
{
	std::ifstream
	arquivoCodigo;

	std::string
	linhaCodigo;

	int
	(*pf) (int) = tolower;

	char
	bufferCaractere;

	arquivoCodigo.open( caminho.c_str(), std::ifstream::in );
	if ( arquivoCodigo.bad() ) throw ( "Fuma um cigarro! O arquivoDeCodigo nao pode ser aberto!! Sucesso;;" );
	arquivoCodigo.seekg ( 0, std::ios::beg );
	
	linhaCodigo.clear( );

	while ( !arquivoCodigo.eof() )
	{
		arquivoCodigo.get( bufferCaractere );

		if ( (bufferCaractere != '\n') && (!arquivoCodigo.eof()) )
		{
			linhaCodigo.push_back( bufferCaractere );
		}
		else
		{
			std::transform(linhaCodigo.begin( ), linhaCodigo.end( ), linhaCodigo.begin( ), pf);

			this->codigoPascal.push_back( linhaCodigo );
			linhaCodigo.clear( );
		}
	}
	arquivoCodigo.close( );
}

int
AutomatoFD::validaCaractereREGEX( char* stringExpressaoRegular, const char* linhaCodigo, std::string transicao )
{
	std::string
	erroExpressaoRegular = "A variável de expressao regular nao pode ser alocada: Transicao " + transicao;

	regex_t
	expressaoRegular;

	int
	status;

	if ( regcomp(&expressaoRegular, stringExpressaoRegular, REG_EXTENDED|REG_ICASE|REG_NOSUB) )	throw ( erroExpressaoRegular );
	status = regexec(&expressaoRegular, linhaCodigo, 0, (regmatch_t *)NULL, 0);
	regfree( &expressaoRegular );
	
	return ( !status );
}

void
AutomatoFD::adicionaCaractereToken( )
{
	std::cout << (*this->codigoPascal.begin()) << std::endl;

	this->token.push_back( (*this->codigoPascal.begin()).at(0) );
	*this->codigoPascal.begin( ) = (*this->codigoPascal.begin()).substr(1);

	if ( (*this->codigoPascal.begin()).empty() )
	{
		this->codigoPascal.pop_front( );
	}
}

void
AutomatoFD::estadoS()
{
	unsigned int
	numeroLinha = 0;

	while( !this->codigoPascal.empty() )
	{
		try
		{
			/* Primeira Transicao */
			if ( this->validaCaractereREGEX("^[A-Z]", (*this->codigoPascal.begin()).c_str(), "SA") )
			{
				this->adicionaCaractereToken( );
			}
			else
			{
				/* Segunda Transicao */
				if ( this->validaCaractereREGEX("^[+|*|~|&|||=|;|.|,|-]", (*this->codigoPascal.begin()).c_str(), "SB") )
				{
					this->adicionaCaractereToken( );
				}
				else
				{
					/* Terceira Transicao */
					if ( this->validaCaractereREGEX("^<", (*this->codigoPascal.begin()).c_str(), "SC") )
					{
						this->adicionaCaractereToken( );
					}
					
					else
					{
						/* Quarta Transicao */
						if ( this->validaCaractereREGEX("^>", (*this->codigoPascal.begin()).c_str(), "SD") )
						{
							this->adicionaCaractereToken( );
						}
						else
						{
							/* Quinta Transicao */
							if ( this->validaCaractereREGEX("^[{]", (*this->codigoPascal.begin()).c_str(), "SE") )
							{
								this->adicionaCaractereToken( );
							}
							else
							{
								/* Sexta Transicao */
								if ( this->validaCaractereREGEX("^\\(", (*this->codigoPascal.begin()).c_str(), "SF") )
								{
									this->adicionaCaractereToken( );
								}
								else
								{
									/* Setima Transicao */
									if ( this->validaCaractereREGEX("^\\)", (*this->codigoPascal.begin()).c_str(), "SG") )
									{
										this->adicionaCaractereToken( );
									}
									else
									{
										/* Oitava Transicao */
										if ( this->validaCaractereREGEX("^[0-9]", (*this->codigoPascal.begin()).c_str(), "SH") )
										{
											this->adicionaCaractereToken( );
										}
	
										else
										{
											/* Nona Transicao */
											if ( this->validaCaractereREGEX("^:", (*this->codigoPascal.begin()).c_str(), "SI") )
											{
												this->adicionaCaractereToken( );
											}
											else
											{
												if ( this->validaCaractereREGEX("^[ ]", (*this->codigoPascal.begin()).c_str(), "ESPACO_BRANCO") )
												{
													this->adicionaCaractereToken( );
												}
												else
												{
													std::cout << numeroLinha << "	* Erro 0 - Caractere inválido" << std::endl;
													this->adicionaCaractereToken( );
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		catch ( std::string erro )
		{
			std::cout << erro << std::endl;
		}
	}
}

void
AutomatoFD::estadoA( )
{
	try
	{
	}
	catch( std::string erro )
	{
		
	}
}

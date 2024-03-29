#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <regex.h>
#include <string>

#include "AutomatoFD.h"
#include "StructToken.h"
#include "TabelaSimbolos.h"



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
	if ( arquivoCodigo.bad() ) throw ( "Fuma um cigarro! O arquivoCodigo nao pode ser aberto!! Sucesso;;" );

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
	
	this->numeroLinha = 1;
	this->numeroToken = 1;
}

int
AutomatoFD::validaCaractereREGEX( char* stringExpressaoRegular, const char* linhaCodigo, std::string transicao )
{
	std::string
	erroExpressaoRegular = "A vari�vel de expressao regular nao pode ser alocada: Transicao " + transicao;

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
	if ( (*this->codigoPascal.begin()).empty() )
	{
		this->codigoPascal.pop_front( );
		this->numeroLinha++;
	}
	else
	{
		this->token.push_back( (*this->codigoPascal.begin()).at(0) );
		*this->codigoPascal.begin( ) = (*this->codigoPascal.begin()).substr(1);
	
		if ( (*this->codigoPascal.begin()).empty() )
		{
			this->codigoPascal.pop_front( );
			this->numeroLinha++;
		}
	}
}

void
AutomatoFD::adicionaTokenArrayAssociativo( )
{
	StructToken
	bufferToken;
	
	bufferToken.token = this->token;

	bufferToken.classificacao = TabelaSimbolos::getInstance( ).procuraSimbolo( this->token );

	bufferToken.linha = this->numeroLinha;
	bufferToken.coluna = 0;
	
	std::cout << bufferToken.token << " - " << bufferToken.classificacao << std::endl;

	tokensClassificados.insert ( std::pair<const int, const StructToken> (this->numeroToken, bufferToken) );

	++this->numeroToken;

	this->token.clear();
}

void
AutomatoFD::adicionaTokenArrayAssociativo( std::string classificacao )
{
	StructToken
	bufferToken;
	
	bufferToken.token = this->token;

	bufferToken.classificacao = classificacao;

	bufferToken.linha = this->numeroLinha;
	bufferToken.coluna = 0;
	
	std::cout << bufferToken.token << " - " << bufferToken.classificacao << std::endl;

	tokensClassificados.insert ( std::pair<const int, const StructToken> (this->numeroToken, bufferToken) );

	++this->numeroToken;

	this->token.clear();
}

void
AutomatoFD::estadoS()
{
	while( !this->codigoPascal.empty() )
	{
		try
		{
			/* Primeira Transicao */
			if ( this->validaCaractereREGEX("^[A-Z]", (*this->codigoPascal.begin()).c_str(), "SA") )
			{
				this->estadoA( );
			}
			else
			{
				/* Segunda Transicao */
				if ( this->validaCaractereREGEX("^[+|*|~|&|||=|;|.|,|-]", (*this->codigoPascal.begin()).c_str(), "SB") )
				{
					this->estadoB( );
				}
				else
				{
					/* Terceira Transicao */
					if ( this->validaCaractereREGEX("^<", (*this->codigoPascal.begin()).c_str(), "SC") )
					{
						this->estadoC( );
					}
					
					else
					{
						/* Quarta Transicao */
						if ( this->validaCaractereREGEX("^>", (*this->codigoPascal.begin()).c_str(), "SD") )
						{
							this->estadoD( );
						}
						else
						{
							/* Quinta Transicao */
							if ( this->validaCaractereREGEX("^[{]", (*this->codigoPascal.begin()).c_str(), "SE") )
							{
								this->estadoE( );
							}
							else
							{
								/* Sexta Transicao */
								if ( this->validaCaractereREGEX("^\\(", (*this->codigoPascal.begin()).c_str(), "SF") )
								{
									this->estadoF( );
								}
								else
								{
									/* Setima Transicao */
									if ( this->validaCaractereREGEX("^\\)", (*this->codigoPascal.begin()).c_str(), "SG") )
									{
										this->estadoG( );
									}
									else
									{
										/* Oitava Transicao */
										if ( this->validaCaractereREGEX("^[0-9]", (*this->codigoPascal.begin()).c_str(), "SH") )
										{
											this->estadoH( );
										}
	
										else
										{
											/* Nona Transicao */
											if ( this->validaCaractereREGEX("^:", (*this->codigoPascal.begin()).c_str(), "SI") )
											{
												this->estadoI( );
											}
											else
											{
												if ( this->validaCaractereREGEX("^[ ]", (*this->codigoPascal.begin()).c_str(), "ESPACO_BRANCO") )
												{
													*this->codigoPascal.begin( ) = (*this->codigoPascal.begin()).substr(1);
												}
												else
												{
													std::cout << "Linha " << this->numeroLinha << "	* Erro 0 - Caractere inv�lido" << std::endl;
													this->adicionaCaractereToken();
													this->adicionaTokenArrayAssociativo( "CARACTERE_INVALIDO" );
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
	this->adicionaCaractereToken( );

	try
	{
		if ( this->validaCaractereREGEX("^([A-Z]|[0-9]|_)", (*this->codigoPascal.begin()).c_str(), "AA") )
		{
			this->estadoA( );
		}
		else
		{
			this->adicionaTokenArrayAssociativo( );
		}
	}
	catch( std::string erro )
	{
		std::cout << erro << std::endl;
	}
}

void
AutomatoFD::estadoB( )
{
	this->adicionaCaractereToken( );
	this->adicionaTokenArrayAssociativo( );
}

void
AutomatoFD::estadoC( )
{
	this->adicionaCaractereToken( );

	try
	{
		if ( this->validaCaractereREGEX("^(>|=)", (*this->codigoPascal.begin()).c_str(), "CJ") )
		{
			this->estadoJ( );
		}
		else
		{
			this->adicionaTokenArrayAssociativo( );
		}
	}
	catch( std::string erro )
	{
		std::cout << erro << std::endl;
	}
}

void
AutomatoFD::estadoD( )
{
	this->adicionaCaractereToken( );

	try
	{
		if ( this->validaCaractereREGEX("^=", (*this->codigoPascal.begin()).c_str(), "DK") )
		{
			this->estadoK( );
		}
		else
		{
			this->adicionaTokenArrayAssociativo( );
		}
	}
	catch( std::string erro )
	{
		std::cout << erro << std::endl;
	}
}

void
AutomatoFD::estadoE( )
{
	this->adicionaCaractereToken( );

	try
	{
		if ( this->validaCaractereREGEX("^[^}]", (*this->codigoPascal.begin()).c_str(), "EE") )
		{
			this->estadoE( );
		}
		else if ( this->validaCaractereREGEX("^[}]", (*this->codigoPascal.begin()).c_str(), "EL") )
		{
			this->estadoL( );
		}
	}
	catch( std::string erro )
	{
		std::cout << erro << std::endl;
	}
}

void
AutomatoFD::estadoF( )
{
	this->adicionaCaractereToken( );

	try
	{
		if ( this->validaCaractereREGEX("^[*]", (*this->codigoPascal.begin()).c_str(), "FM") )
		{
			this->estadoM( );
		}
		else
		{
			this->adicionaTokenArrayAssociativo( );
		}
	}
	catch( std::string erro )
	{
		std::cout << erro << std::endl;
	}
}

void
AutomatoFD::estadoG( )
{
	this->adicionaCaractereToken( );
	this->adicionaTokenArrayAssociativo( );
}

void
AutomatoFD::estadoH( )
{
	this->adicionaCaractereToken( );

	try
	{
		if ( this->validaCaractereREGEX("^[0-9]", (*this->codigoPascal.begin()).c_str(), "HH") )
		{
			this->estadoH( );
		}
		else
		{
			this->adicionaTokenArrayAssociativo( "DIGITO" );
		}
	}
	catch( std::string erro )
	{
		std::cout << erro << std::endl;
	}
}

void
AutomatoFD::estadoI( )
{
	this->adicionaCaractereToken( );

	try
	{
		if ( this->validaCaractereREGEX("^[=]", (*this->codigoPascal.begin()).c_str(), "IN") )
		{
			this->estadoN( );
		}
		else
		{
			this->adicionaTokenArrayAssociativo( );
		}
	}
	catch( std::string erro )
	{
		std::cout << erro << std::endl;
	}
}

void
AutomatoFD::estadoJ( )
{
	this->adicionaCaractereToken( );
	this->adicionaTokenArrayAssociativo( );
}

void
AutomatoFD::estadoK( )
{
	this->adicionaCaractereToken( );
	this->adicionaTokenArrayAssociativo( );
}

void
AutomatoFD::estadoL( )
{
	this->adicionaCaractereToken( );
	this->adicionaTokenArrayAssociativo( "COMENTARIO" );
}

void
AutomatoFD::estadoM( )
{
	this->adicionaCaractereToken( );

	try
	{
		if ( this->validaCaractereREGEX("^[^*]", (*this->codigoPascal.begin()).c_str(), "MM") )
		{
			this->estadoM( );
		}
		else if ( this->validaCaractereREGEX("^[*]", (*this->codigoPascal.begin()).c_str(), "MO") )
		{
			this->estadoO( );
		}
	}
	catch( std::string erro )
	{
		std::cout << erro << std::endl;
	}
}

void
AutomatoFD::estadoN( )
{
	this->adicionaCaractereToken( );
	this->adicionaTokenArrayAssociativo( );
}

void
AutomatoFD::estadoO( )
{
	this->adicionaCaractereToken( );

	try
	{
		if ( this->validaCaractereREGEX("^[^\\)]", (*this->codigoPascal.begin()).c_str(), "MM") )
		{
			this->estadoM( );
		}
		else if ( this->validaCaractereREGEX("^[\\)]", (*this->codigoPascal.begin()).c_str(), "MO") )
		{
			this->estadoP( );
		}
	}
	catch( std::string erro )
	{
		std::cout << erro << std::endl;
	}
}

void
AutomatoFD::estadoP( )
{
	this->adicionaCaractereToken( );
	this->adicionaTokenArrayAssociativo( "COMENTARIO" );
}

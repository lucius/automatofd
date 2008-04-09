#ifndef AUTOMATOFD_H_
#define AUTOMATOFD_H_

#include <iostream>
#include <list>
#include <string>

/*bogaFlame*/

class AutomatoFD
{
	public:
		AutomatoFD( std::string );

		~AutomatoFD( );

		/*hashTable<tipoDaHash>
		getHashTable( );*/

	protected:
		std::list<std::string>
		codigoPascal;

		std::string
		token;

		void
		carregaCodigo( std::string );

		int
		validaCaractereREGEX( char*, const char*, std::string );

		void
		adicionaCaractereToken(	);

		void
		adicionaTokenHash( );

		void
		estadoS( );

		void
		estadoA( );

		void
		estadoB( );

		void
		estadoC( );

		void
		estadoD( );

		void
		estadoE( );

		void
		estadoF( );

		void
		estadoG( );

		void
		estadoH( );

		void
		estadoI( );

		void
		estadoJ( );

		void
		estadoK( );

		void
		estadoL( );
		
		void
		estadoM( );
		
		void
		estadoN( );

		void
		estadoO( );
		
		void
		estadoP( );
};

#endif /*AUTOMATOFD_H_*/

#ifndef STRUCTTOKEN_H_
#define STRUCTTOKEN_H_

#include <string>



typedef struct 
{
	std::string
	token;

	std::string
	classificacao;
	
	unsigned int
	linha;
	
	unsigned int
	coluna;
} StructToken;

#endif /*STRUCTTOKEN_H_*/

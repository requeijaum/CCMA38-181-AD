#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream assembly;

char dirtyNumToHex(int num)
{
	if( num < 0 || num > 15 )
	{
		cerr << "Erro de operando!";
		exit( -1 );
	}
	else if( num <= 9 ) return num + 48;
	else return num + 55;
}

void checarEOF(void)
{
	if( assembly.eof() )
	{
		cerr << "Fim do arquivo encontrado antes de END!";
		exit( -1 );
	}
}

int main( int argc, char ** argv )
{
	ofstream compilado;
	
	string operacao;
	int operando1, operando2, tipo;
	char virgula;
	
	int protecao = 0;
	
	if( argc == 3 && argv[1] != NULL && argv[2] != NULL )
	{
		assembly.open( argv[1] );
		compilado.open( argv[2] );
		
		if(assembly == NULL || compilado == NULL)
		{
			cerr << "Arquivos nao encontrados!";
			exit( -1 );
		}
		
		while( protecao < 1000 )
		{
			assembly >> operacao;
			
			if(operacao != "END") checarEOF();
			
			if( operacao == "AND" ) 
			{
				compilado << "0";
				tipo = 1;
			}
			else if( operacao == "OR" )
			{
				compilado << "1";
				tipo = 1;
			}
			else if( operacao == "NOT" )
			{
				compilado << "2";
				tipo = 2;
			}
			else if( operacao == "ADD" )
			{
				compilado << "3";
				tipo = 1;
			}
			else if( operacao == "SUB" )
			{
				compilado << "4";
				tipo = 1;
			}
			else if( operacao == "MUL" )
			{
				compilado << "5";
				tipo = 1;
			}
			else if( operacao == "DIV" )
			{
				compilado << "6";
				tipo = 1;
			}
			else if( operacao == "EQ" )
			{
				compilado << "7";
				tipo = 1;
			}
			else if( operacao == "LT" )
			{
				compilado << "8";
				tipo = 1;
			}
			else if( operacao == "LEQ" )
			{
				compilado << "9";
				tipo = 1;
			}
			else if( operacao == "LDA" )
			{
				compilado << "A";
				tipo = 3;
			}
			else if( operacao == "LDI" )
			{
				compilado << "B";
				tipo = 4;
			}
			else if( operacao == "STR" )
			{
				compilado << "C";
				tipo = 3;
			}
			else if( operacao == "MOV" )
			{
				compilado << "D";
				tipo = 1;
			}
			else if( operacao == "JMP" )
			{
				compilado << "E";
				tipo = 3;
			}
			else if( operacao == "HLT" )
			{
				compilado << "F";
				tipo = 5;
			}
			else if( operacao == "END" ) break;
			else
			{
				cerr << "Erro no codigo!";
				exit( -1 );
			}
			
			switch(tipo)
			{
				case 1:
					
					assembly >> operando1;
					checarEOF();
					assembly >> virgula; 
					checarEOF();
					assembly >> operando2;
					checarEOF();
					compilado << dirtyNumToHex( operando1 ) << dirtyNumToHex( operando2 );
					break;
				
				case 2:
				
					assembly >> operando1;
					checarEOF();
					compilado << dirtyNumToHex( operando1 ) << "0";
					break;
				
				case 3:
				case 4:
				
					assembly >> operando1;
					checarEOF();
					if(operando1 < 0 || operando1 > 255)
					{
						cerr << "Erro de operando!";
						exit( -1 );
					}
					else compilado << dirtyNumToHex( ((operando1) >> 4) & 0xF ) << dirtyNumToHex( (operando1) & 0xF );
					break;
				
				case 5:
				
					compilado << "0" << "0";
					break;
			}
			
			protecao++;
		}
		
		if( protecao >= 1000 )
		{
			cerr << "END nao encontrado, arquivo muito grande!";
			exit( -1 );
		}
	}
	else
	{
		cerr << "Erro nos argumentos!";
		exit( -1 );
	}
	
	assembly.close();
	compilado.close();
	
	return 0;
}
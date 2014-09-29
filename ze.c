void escritor(){

	while(int vezesProcessoTotal = 0; vezesProcessoTotal <=	5120; vezesProcessoTotal++){
		char nomeDoFicheiro = escolheFicheiroRandom()
		
		while(int numeroDeEscritas = 0; numeroDeEscritas <= 1024; numeroDeEscritas++){
			char stringAserEscrita = fazString(escolheCaracter());
			escreve(stringAserEscrita, NomeDoFicheiro);
		}
	}
}

int leitor(){ //nao sei o que fazer se o ficheiro escolhido nao existir, vou optar por fazer print para alem do return da incoerencia
	char nomeDoFicheiro = escolheFicheiroRandom();
	if(existe(nomeDoFicheiro)){
		return (verificaConteudo(nomeDoFicheiro));
	else{
		printf("Nao existe ficheiro escolhido.\n");
		return -1;
	}
}


//=============================================================================================================


	
char fazString(char caracter){
	while(int i = 0; i <= 9; i++){
		char string = string + caracter;
	}
	return string;
}

char escolheCaracter(){
	int caracterASCII = 97 + rand() * 25; //obter inteiro entre 97 e 122 inclusive
	//transformar em char
	return x;
}

char escolheFicheiroRandom(){  //funciona quase como o escolhe Caracter
	int numeroDoFicheiro = rand() * 5; //ha 5 ficheiros
	char nomeDoFicheiro = "SO2014-" + numeroDoFicheiro + ".txt";
	verificaOuCriaFicheiro(nomeDoFicheiro);  //acho melhor chamar a funcao aqui, pois assim so sera chamada a partir do loop exterior, eficiencia
	return (nomeDoFicheiro);
}
	
void verificaOuCriaFicheiro(char nomeDoFicheiro){
	if(existe(nomeDoFicheiro)){
		return;
	}
	else{
		cria(nomeDoFicheiro);
	}
	return;
}
	
void escreve(char string, char ficheiro){ //a implementar
}

int existe(nomeDoFicheiro){ //funcao age como boolean
}

int verificaConteudo(nomeDoFicheiro){ //retorna 0 se o ficheiro contiver as strings
}
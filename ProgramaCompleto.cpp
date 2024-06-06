/*

Nome: Felipe Martins de Medeiros
Unidade: Méier
	
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<ctype.h>

using namespace std;

//Declaração das variáveis utilizadas

char palavraOriginal[6];
int palavraCodificada[6];
float matrizC[3][3] = {{1,0,1},
					 {1,1,1},
					 {0,2,-1}};
							  
float matrizCriptografada[3][2], matrizM[3][2];

float identidade[3][3], inversa[3][3], m, p;
float pivot = 0;
float matrizDescriptografada[3][3];

const char alfabeto_maiusculo[] = "*ABCDEFGHIJKLMNOPQRSTUVWXYZ";


void descriptografar(){
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 3; k++){
				matrizDescriptografada[i][j] += inversa[i][k] * matrizCriptografada[k][j];
			}
		}
	}
	
	printf("Matriz Descriptografada: \n");
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 2; j++){
			printf("%.1f ", matrizDescriptografada[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	
	int codigoUnico;
	
	printf("Mensagem Original: ");
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			codigoUnico = matrizDescriptografada[j][i];
			printf("%c", alfabeto_maiusculo[codigoUnico]);
		}
	}
	
}

void calculaInversa(){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(i == j){
				identidade[i][j] = 1;
			}
			else{
				identidade[i][j] = 0;
			}
		}
	}
	
	printf("Matriz Identidade: \n");
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			printf("%.1f ", identidade[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	
	for(int j = 0; j < 3; j++){
		pivot = matrizC[j][j];
		p = pivot/pivot;
		
		for(int k = 0; k < 3; k++){
			matrizC[j][k] = matrizC[j][k]/pivot;
			identidade[j][k] = identidade[j][k]/pivot;
		}
		
		for(int i = 0; i < 3; i++){
			if(i != j){
				m = matrizC[i][j]/p;
				
				for(int k = 0; k < 3; k++){
					matrizC[i][k] = matrizC[i][k] - (m * matrizC[j][k]);
					identidade[i][k] = identidade[i][k] - (m * identidade[j][k]);
				}
			}
		}
	}
	
	//Atribuição da Inversa
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			inversa[i][j] = identidade[i][j];
		}
	}
	
	//Mostragem dos resultados
	
	printf("Matriz Inversa: \n");
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			printf("%.1f ", inversa[i][j]);
		}
		printf("\n");
	}
}

void capturaMensagemOriginal(){
	bool palavraCorreta;
	while(!palavraCorreta){
		printf("Escreva a mensagem para criptografar: ");
		scanf("%s", &palavraOriginal);
		palavraCorreta = true;
		
		//Tratamento de erros
		
		if(strlen(palavraOriginal) > 6 && strlen(palavraOriginal) <= 0){
			palavraCorreta = false;
		}
		
		for(int i = 0; i < 6; i++){
			if(isalpha(palavraOriginal[i]) == 0){
				palavraCorreta = false;
				break;
			}
		}
		
		system("cls");
	}
}

//Função que codifica a mensagem original de acordo com a tabela de conversão

void codificaMensagem(char palavra[]){
	
	for(int i = 0; i < 6; i++){
		palavra[i] = toupper(palavra[i]);
		int codigoCorresp = 1;
		int codigoAscii = (int) palavra[i];
		
		for(int j = 65; j <= 90; j++){
			if(codigoAscii == j){
				palavraCodificada[i] = codigoCorresp;
				break;
			}
			
			codigoCorresp++;
		}
	}
}

int main(){
	//Input da palavra a ser criptografada
	
	capturaMensagemOriginal();
	
	codificaMensagem(palavraOriginal);
	
	//Transformando a palavra codificada de vetor para matriz
	
	int cont = 0;
	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			matrizM[j][i] = palavraCodificada[cont];
			cont++;
		}
	}
	
	//Criptografia da Mensagem
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 3; k++){
				matrizCriptografada[i][j] += matrizC[i][k] * matrizM[k][j];
			}
		}
	}
	
	//Exibição dos resultados
	
	printf("Palavra Original: %s\n", &palavraOriginal);
	
	printf("\nMatriz M:\n");
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 2; j++){
			printf("%.1f ", matrizM[i][j]);
		}
		printf("\n");
	}
	
	printf("\nMatriz Criptografada:\n");
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 2; j++){
			printf("%.1f ", matrizCriptografada[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	
	//Módulo de Descriptografia
	
	calculaInversa();
	
	printf("\n");
	
	descriptografar();
}

//Nome: Beatriz Rodrigues Monteiro
//Matr�cula: 20100019
//Curso: Ci�ncia da computa��o

//Objetivo: Criar um algoritmo para controlar as vendas das passagens
//Nome do destino != 0; Quantidade de assentos >= 90 <= 200; Valor da passagem (se idade <=5, 50%);
//Reservas: confirmadas ou canceladas;

#include<stdio.h> //Inclus�o de biblioteca para entrada e sa�da de dados
#include<locale.h> //Inclus�o de biblioteca para incluir linguagem
#include<stdlib.h> //Inclus�o de biblioteca para limpar tela 
#include<string.h> //Inclus�o de biblioteca para manipula��o de string
#include<ctype.h> //Inclus�o de biblioteca para manipula��o de caracteres
#include<windows.h>  //Inclus�o de biblioteca para mudar a cor das letras


enum DOS_COLORS{ //Descri��o das cores
 BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
 LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
 LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE };

void textcolor(int iColor){ //Fun��o para cores
 HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
 CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
 BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
 bufferInfo.wAttributes &= 0x00F0;
 SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor); }

int main(void) { //In�cio do algoritmo: fun��o main
setlocale(LC_ALL, "Portuguese"); //Defini��o de portugu�s como linguagem 

    //Declara��o de vari�veis e o tipo
    char voltarMenu;
    char nomeDestino[60], nomePassageiro[60];
    char classificacao[20][10];
    float valorPassagem, valorTotal;
    int qtAssento, menuPrincipal, idadePassageiro, poltronaSelecionada, nReserva;
    int coluna = 0, linha = 0, contadorPoltrona = 0, reserva = 0, contadorConfirmado = 0, contadorDisponivel = 0, contadorReservado = 0;
    int poltrona[20][10], matrizReserva[20][10];
    
    printf("------------------------------------------\n");
    printf("  SEJA BEM-VINDO A SALUMAR LINHAS A�REAS\n");
   	printf("------------------------------------------\n\n\n");

	do{
		printf("INFORME O NOME DO DESTINO: ");
		fgets(nomeDestino, 60, stdin);
	 	fflush(stdin); //Limpar buffer
		nomeDestino[strlen(nomeDestino) - 1 ] = '\0'; //Evitar erro no momento que for imprimir o nome do destino
	        
		if(strlen(nomeDestino) < 2) 
		    printf("Nome inv�lido por ser muito curto.\n\n");
		} while(strlen(nomeDestino) < 2); //Condi��o de repeti��o para evitar entrada nula
		
	do{
		printf("INFORME O VALOR DA PASSAGEM PARA O DESTINO INDICADO: ");
		scanf("%f", &valorPassagem);
		fflush(stdin);
			
		if(valorPassagem <= 0)
			printf("Valor inv�lido, informe valor positivo.\n\n");
		} while(valorPassagem <= 0);
	
	do{
		printf("INFORME A QUANTIDADE DE ASSENTOS EXISTENTES PARA O AVI�O DESTE DESTINO: ");
   	    scanf("%d", &qtAssento);
    	fflush(stdin);
	        
		if(qtAssento > 200 || qtAssento < 90)
			printf("Valor inv�lido, por favor informar entre 90 e 200 assentos.\n\n");
		} while(qtAssento > 200 || qtAssento < 90);
			
		system("pause"); //Evitar mudan�as bruscas de tela
		system("cls");
    
    for(linha = 0; linha < 20; linha++){ //Contador para criar espa�o para at� 200 poltronas
			for(coluna = 0; coluna < 10; coluna++){
				contadorPoltrona++;
				poltrona[linha][coluna] = contadorPoltrona; //Associar poltrona com o contador
			}
	}
	
	for(linha = 0; linha < 20; linha++){ //Condi��o inicial, na qual todas poltronas est�o dispon�veis
		for(coluna = 0; coluna < 10; coluna++){		
			if(poltrona[linha][coluna] <= qtAssento){
				classificacao[linha][coluna] = 'D'; }
			
			if(poltrona[linha][coluna] <= qtAssento && classificacao[linha][coluna] == 'D'){ //Contador inicial de dispon�veis
				contadorDisponivel++; }	
		}
	}
		
	
    do{ //Repeti��o menu principal
		printf("------------------------------------------\n");
    	printf("           SALUMAR LINHAS A�REAS\n");
   		printf("------------------------------------------\n\n\n");	
   		printf("                   MENU\n\n\n");
   		printf("1- VERIFICAR OCUPA��O DO VOO\n");
   		printf("2- EFETUAR RESERVA\n");
   		printf("3- CONFIRMAR RESERVA\n");
   		printf("4- CANCELAR RESERVA\n");
   		printf("5- VERIFICAR STATUS DO VOO\n");
   		printf("6- SAIR\n\n");
   		printf("INFORME OP��O DESEJADA: ");
   		scanf("%d", &menuPrincipal);
   		fflush(stdin);
	
		switch(menuPrincipal){
			case 1:
				system("cls"); 		
				printf("------------------------------------------\n");
    			printf("           SALUMAR LINHAS A�REAS\n");
   				printf("------------------------------------------\n\n\n");
   				printf("            MAPA DE POLTRONAS\n\n\n");
   				
   				for(linha = 0; linha < 20; linha++){ //Condi��o para cria��o de mapa de poltronas
					for(coluna = 0; coluna < 10; coluna++)
						if(poltrona[linha][coluna] <= contadorPoltrona && (classificacao[linha][coluna] == 'D' || classificacao[linha][coluna] == 'R' || classificacao[linha][coluna] == 'C')){
							if(classificacao[linha][coluna] == 'D'){
								textcolor(GREEN);
                		    	printf("%c ", classificacao[linha][coluna]); 
								printf("%.3d   ", poltrona[linha][coluna]); }
                		    else if(classificacao[linha][coluna] == 'R'){
                		    	textcolor(LIGHT_RED);
                		    	printf("%c ", classificacao[linha][coluna]); 
								printf("%.3d   ", poltrona[linha][coluna]); }
                		    else if(classificacao[linha][coluna] == 'C'){
                		    	textcolor(LIGHT_BLUE);
                		    	printf("%c ", classificacao[linha][coluna]);
                  				printf("%.3d   ", poltrona[linha][coluna]); }
						}
					printf ("\n"); //N�O ESQUECER!
				} 
				textcolor(GREEN); //Escolha de cor
				printf("\n\nDispon�vel");
				textcolor(LIGHT_RED);
				printf("       Reservado");
				textcolor(LIGHT_BLUE);
				printf("       Confirmado\n");
				textcolor(LIGHT_GRAY);
				
				
				system("pause");
				system("cls");
				break;
		
			case 2:		
				system("cls"); 		
				printf("------------------------------------------\n");
    			printf("           SALUMAR LINHAS A�REAS\n");
   				printf("------------------------------------------\n\n\n");	

  				reserva++; //Contador do n�mero de reservas
   				
   				do{
					printf("INFORME NOME DO PASSAGEIRO: ");
					fgets(nomePassageiro, 60, stdin);
	 				fflush(stdin);
		    		nomePassageiro[strlen(nomePassageiro) - 1 ] = '\0';
				
					if(strlen(nomePassageiro) < 2) 
		    		printf("NOME INV�LIDO POR SER MUITO CURTO.\n\n");
				} while(strlen(nomePassageiro) < 2);
				
				do{
					printf("INFORME IDADE DO PASSAGEIRO: ");
					scanf("%d", &idadePassageiro);
					fflush(stdin);
					
					if(idadePassageiro < 1 || idadePassageiro > 110)
						printf("IDADE INV�LIDA PARA PASSAGEIRO.\n\n");
				} while(idadePassageiro < 1 || idadePassageiro > 110);				
						
       			do{
					printf("INFORME A POLTRONA DE SUA PREFER�NCIA: ");
					scanf("%d", &poltronaSelecionada);
					fflush(stdin);
       						
					if(poltronaSelecionada < 1 || poltronaSelecionada > qtAssento){
						printf("VALOR INV�LIDO PARA A POLTRONA SELECIONADA.\n\n"); }
               	} while(poltronaSelecionada < 1 || poltronaSelecionada > qtAssento);
				
				for(linha = 0; linha < 20; linha++) { //Mudan�a de status para reservado
       				for(coluna = 0; coluna < 10; coluna++){
            			if(poltrona[linha][coluna] == poltronaSelecionada){
                			classificacao[linha][coluna] = 'R';
                			matrizReserva[linha][coluna] = reserva; //Associar reserva ao assento
                			contadorReservado++;
                			contadorDisponivel--; } 
            		} 
           		}
					      
 				if (idadePassageiro <= 5){ //C�lculo do desconto
 					valorPassagem /= 2; }
 				
        		printf("\n\nO VALOR A SER PAGO � DE %.2f REAIS.\n", valorPassagem);
				printf("SUA RESERVA FOI EFETUADA COM SUCESSO E � A DE N�MERO %d.\n\n", reserva);
				
				if (idadePassageiro <= 5){ //Solu��o grotesca para voltar ao valor original
 					valorPassagem *= 2; }
				
				system("pause");
				system("cls");
				break;
				   		
			case 3:
				system("cls"); 		
				printf("------------------------------------------\n");
    			printf("           SALUMAR LINHAS A�REAS\n");
   				printf("------------------------------------------\n\n\n");	
   				
   				do{
   					printf("INFORME O N�MERO DA SUA RESERVA PARA EFETUAR A CONFIRMA��O: ");
   					scanf("%d", &nReserva);
   					fflush(stdin);
   					
   					if(nReserva > reserva || nReserva < 1)
   						printf("VALOR DE RESERVA INV�LIDO.\n\n");
   				} while(nReserva > reserva || nReserva < 1);
   				
   				for(linha = 0; linha < 20; linha++)
       				for(coluna = 0; coluna < 10; coluna++){
            			if(matrizReserva[linha][coluna] == nReserva && classificacao[linha][coluna] == 'R'){
                			classificacao[linha][coluna] = 'C';
                			contadorConfirmado++; //Contador para contagem de voos confirmados
                			contadorReservado--; //Contador para retirar os voos reservados
                			valorTotal += valorPassagem; //Contador para aumentar valor total
                		} 
            		}
            	
            	printf("\n\nSUA RESERVA FOI CONFIRMADA COM SUCESSO.\n\n");
            	system("pause");
				system("cls");
				break;   				
		
			case 4:
				system("cls"); 		
				printf("------------------------------------------\n");
    			printf("           SALUMAR LINHAS A�REAS\n");
   				printf("------------------------------------------\n\n\n");	
   				
   				do{
   					printf("INFORME O N�MERO DA SUA RESERVA PARA EFETUAR O CANCELAMENTO: ");
   					scanf("%d", &nReserva);
   					fflush(stdin);
   					
   					if(nReserva > reserva || nReserva < 1)
   						printf("VALOR DE RESERVA INV�LIDO.\n\n");
   				} while(nReserva > reserva || nReserva < 1);
   				
   				for(linha = 0; linha < 20; linha++)
       				for(coluna = 0; coluna < 10; coluna++){
            			if(matrizReserva[linha][coluna] == nReserva && classificacao[linha][coluna] == 'C'){
                			classificacao[linha][coluna] = 'D';
                			contadorConfirmado--;
                			contadorDisponivel++;
                			valorTotal -= valorPassagem; }
                		else if (matrizReserva[linha][coluna] == nReserva && classificacao[linha][coluna] == 'R'){
                			classificacao[linha][coluna] = 'D';
                			contadorReservado--;
                			contadorDisponivel++;
                			valorTotal -= valorPassagem; 
						}
            		}
            	
            	printf("\n\nSUA RESERVA FOI CANCELADA COM SUCESSO.\n\n");
            	system("pause");
				system("cls");
				break;  
		
			case 5:
				system("cls"); 		
				printf("------------------------------------------\n");
    			printf("           SALUMAR LINHAS A�REAS\n");
   				printf("------------------------------------------\n\n\n");	
   				printf("INFORMA��ES DO VOO\n\n\n");
   				
   				printf("DESTINO DO VOO: %s\n", nomeDestino);
   				printf("QUANTIDADE DE POLTRONAS DISPON�VEIS: %d\n", contadorDisponivel);
   				printf("QUANTIDADE DE POLTRONAS RESERVADAS: %d\n", contadorReservado);
   				printf("QUANTIDADE DE POLTRONAS CONFIRMADAS: %d\n", contadorConfirmado);
   				printf("QUANTIDADE TOTAL EM REAIS: %.2f\n", valorTotal);
   				system("pause");
				system("cls");
				break; 	
		
			case 6: 
				system("cls");
				printf("------------------------------------------\n");
    			printf("           SALUMAR LINHAS A�REAS\n");
   				printf("------------------------------------------\n\n\n");	
				printf("AGRADECEMOS SUA VISITA, BOM VOO E VOLTE SEMPRE.");
				fflush(stdin);
				exit(0); //Encerrar programa
				break;
				
			default: //Qualquer valor n�o esperado
				system("cls");
				printf("------------------------------------------\n");
    			printf("           SALUMAR LINHAS A�REAS\n");
   				printf("------------------------------------------\n\n\n");	
				
				do{		
					printf("DESEJA VOLTAR PARA O MENU? [S|N] ");
					scanf("%c", &voltarMenu);
					voltarMenu = toupper(voltarMenu); 
					fflush(stdin);
				
					if (voltarMenu == 'S'){
						system("cls");
						break; }
					else if(voltarMenu == 'N'){
						system("cls");
				
						printf("------------------------------------------\n");
    					printf("           SALUMAR LINHAS A�REAS\n");
   						printf("------------------------------------------\n\n\n");	
						printf("AGRADECEMOS SUA VISITA, BOM VOO E VOLTE SEMPRE.");
						break; }
					else {
						printf("Resposta inv�lida.\n\n\n"); }
				} while(voltarMenu != 'S' || voltarMenu != 'N');
		}
	} while(voltarMenu == 'S' || menuPrincipal > 0 && menuPrincipal < 7);


  return 0; //retorno da fun��o
}//final da fun��o

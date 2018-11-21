/*Anagrmas, por Juan Ureña.
El programa recibe un maximo de 100 palabras
nos muestra aquellas que son anagrama
y las letras en diferente orden*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum{
Maximo_caracter=102,
Inicio=0
};


/*Variables de control de los bucles*/
int x=Inicio;
int y=Inicio;

/*Numero de palabras de entrada*/
int Argumentos=Inicio;

/*Letras desordenadas y si tengo que mostrarlas*/
char *messy;
int show_differnets=Inicio;

/*Datos para liberar memoria y sacar resultados de la 
funcion are_anagrams*/
struct diferents_letters {
 int anagram;
 char *letters;
 char *word;
};

struct diferents_letters help_var;
/*Añadir caracteres que no esten en una palabra (two)
y si esten en otra (one)*/
char
add_character_different(char *word_one, char *word_two)
{
	int i=Inicio;
	int j=Inicio;

/*Comparo cada letra con todas las de las otras palabra*/	
	while (i<strlen(word_one)){
		while (j<strlen(word_two)){
			if (word_one[i]==word_two[j]){
				break;
			}else if(j==strlen(word_two)-1){
/*Llego al final, añado una letra que no contenia ante la palabra*/
				word_two[strlen(word_two)]=word_one[i];
			}
			j++;
		}
		j=Inicio;
		i++;
	}	
	free(word_one);
	return *word_two;
}

/*Nos de vuelve si son anagramas, las letras desordenadas
y la palabra auxiliar usada para tachar, para liberarla fuera*/
struct diferents_letters 
are_anagrams (char *word_one, char *word_two)
{
	struct diferents_letters result;
	char *aux_two; 
	aux_two=strdup(word_two);
	char *messy_letters = malloc(sizeof(word_one)+1);
	int anagrams=1;/*True*/
	int i=Inicio;
	int j=Inicio;
/*Comparo que no sean iguales*/
	int aux=strcmp(word_one, word_two);

	if (strlen(word_one)==strlen(word_two) && aux){
	
		while (i<strlen(word_one) && anagrams){	
		
			while (j<strlen(word_two)){
/*Comparo cada posicion con todas las de la otra palabra*/
				if (word_one[i]==aux_two[j]){
					anagrams=1;/*True*/
					aux_two[j]='-';		
					if (i !=j){
						messy_letters[strlen(messy_letters)]=word_one[i];
					}
					break;		
				}else{
					anagrams=0;/*False*/
/*Si alguna no esta, ya se que no son anagramas*/	
				}			
				j++;
			}
			i++;
			j=Inicio;
/*Siguiente letra de una palabra y vuelvo a comparar con 
todas las de la otra, por eso reinicio j*/
		}
	}else{
		anagrams=Inicio;
	}
	
/*Resultado*/
	result.anagram=anagrams;
	result.letters=messy_letters;
	result.word=aux_two;
	return result;       
}


int
main(int argc, char *argv[])
{
	Argumentos=argc;
	
	if (Argumentos<Maximo_caracter){
	
		for (x=1; x< Argumentos; x++){
/*Comparo cada palabra con todas las demas*/
			for (y=1; y< Argumentos; y++){
/*Compruebo no esten vacios*/
				if (strlen(argv[x]) && strlen(argv[y])){
					help_var=are_anagrams(argv[x], argv[y]);
					if (help_var.anagram){
/*Son anagramas, muestro las letras difernetes*/
						show_differnets=1;/*True*/
						printf("\n");
						printf("%s %s", argv[x], argv[y]);
						messy=strdup(help_var.letters);
/*Libero la memoria de Are_Anagrams*/
						free(help_var.letters);
						free(help_var.word);
/*Pongo a vacio el primer argumento*/
						argv[y][Inicio]='\0';
						break;
					}else{
					}
				}
			}	
/*Salgo del bucle, porque ahora ya solo deberia mostrar la palabra
con la que comparo, porque la original ya estaria escrita*/			
			for (y=1; y< Argumentos; y++){
				help_var=are_anagrams(argv[x], argv[y]);
				if (help_var.anagram){
					messy=strdup(help_var.letters);
/*Libero la memoria de Are_Anagrams*/
					free(help_var.letters);
					free(help_var.word);
					if (are_anagrams(argv[x], argv[y]).anagram){
						*messy=add_character_different(are_anagrams(argv[x], argv[y]).letters, messy);
						printf(" %s", argv[y]);
						argv[y][Inicio]='\0';
					}
				}
			}
/*Muestro la diferencias*/
			if (argv[x][Inicio]!='\0' && messy && show_differnets){
				printf(" %s%s%s", "[" , messy,"]");
				free(messy);
			}
			argv[x][Inicio]='\0';
			show_differnets=0;/*False*/
		}
	}
	printf("\n \n");
	exit(EXIT_SUCCESS);
}

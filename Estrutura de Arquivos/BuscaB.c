#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

long tam_bit(long n){
    return n*(sizeof(Endereco));
}

int main(int argc, char**argv){
    FILE *f;
	Endereco e;
	int c = 0;
	char* cepPesq = argv[1];
    long first = 0, last, mid;

	if(argc != 2){
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("cep_ordenado_novo.dat","r");

	fseek(f,0,SEEK_END);
	last = ftell(f)/sizeof(Endereco);

	while(first <= last){
		c++;
		mid = (first + last)/2;
		fseek(f,tam_bit(mid),SEEK_SET);
		fread(&e,sizeof(Endereco),1,f);

		if(strncmp(cepPesq,e.cep,8)==0){
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
        }else{
			if(strncmp(cepPesq,e.cep,8) > 0){
				first = mid + 1;
			}else{
				last = mid - 1;
			}	
		}
	}
	printf("Total Lido: %d\n", c);
	fclose(f);

	return 0;
}
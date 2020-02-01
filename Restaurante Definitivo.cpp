#include <iostream>
using namespace std;
struct produto {
    int codP;
    float valor;
    struct produto *proxP;
};
typedef struct produto *ptrP;
float total_dia = 0;
struct cliente {
    int codC;
    struct produto *prod;
    struct cliente *proxC;
};
typedef struct cliente *noPtr;
noPtr inicio = NULL;
bool listaVazia() {
    if (inicio) {
        return false;
    }else{
        return true;
    }
}
noPtr busca_cliente(int x) {
 noPtr aux;
 aux = inicio;
 while (aux != NULL){
    if (aux->codC == x){
    return aux;
    }else{
        aux = aux->proxC;
    }
 }
 return NULL;
}
void pedido() {
    int x;
    cout << "_______________________" << endl;
    cout << "Entre com o codigo do cliente: ";
    cin >> x;
 noPtr cli = busca_cliente(x);
 bool achou = false;
 do {
    if (cli) {
        achou = true;
        int cod_produto;
        float val_produto;
        cout << "Digite o codigo do pedido: ";
        cin >> cod_produto;
        cout << "Digite o valor do produto: ";
        cin >> val_produto;
        total_dia += val_produto;
        ptrP p = new produto;
        p->codP = cod_produto;
        p->valor = val_produto;
        p->proxP = cli->prod;
        cli->prod = p;
        cout << "_______________________" << endl;
    }else{
        achou = false;
        cout<<"Cliente n encontrado, digite dnv"<<endl;
        cin>>x;
        cli = busca_cliente(x);
   }
 }while(!achou);
}
void listarP() {
 int cod_cliente;
 cout << "_______________________" << endl;
 cout << "Entre com o codigo do cliente: ";
 cin >> cod_cliente;

 noPtr cli = busca_cliente(cod_cliente);
 bool achou = false;
 do{
    if(cli){
    achou = true;
    ptrP p = cli->prod;
        if(p!=NULL){
            cout << "Os produtos sao: " << endl;
            while (p != NULL){
                cout << p->codP << "->";
                p = p->proxP;
            }
            cout << "NULL" << endl;
        }else{
        cout << "Nao ha produtos !!" << endl;
        }
        cout << "_______________________" << endl;
    }else{
        achou = false;
        cout << "Cliente n encontrado, digite novamente: "<< endl;
        cin >> cod_cliente;
        cli = busca_cliente(cod_cliente);
    }
 }while(!achou);
}
void saida() {
  float totalC = 0;
  int cod_cliente;
  cout << "_______________________" << endl;
  cout << "Digite o codigo do cliente: ";
  cin >> cod_cliente;
  noPtr cli = busca_cliente(cod_cliente);
  noPtr ant = inicio;
  while(ant->proxC!=cli && ant->proxC!=NULL){
  	ant = ant->proxC;
  }
  bool achou = false;
    do {
       if(cli){
         achou = true;
         ptrP p = cli->prod;
         if(p!=NULL){
            while(p!=NULL){
            	totalC += p->valor;
                p = p->proxP;
            }
            if(cli==inicio){
            	noPtr temp = inicio;
                inicio = cli -> proxC;
                delete(temp);
			}else{
			    ant->proxC = cli->proxC;
			    delete(cli);
			}
           cout << "Total a pagar: " << totalC << endl;
           cout << "Cliente pagou e saiu" << endl;
          }else{
            cout << "O cliente nao consumiu nada !" << endl;
            if(cli==inicio){
            	noPtr temp = inicio;
            	inicio = cli -> proxC;
            	delete(temp);
            	cout << "Cliente saiu" << endl;
			}else{
				ant->proxC = cli->proxC;
				delete(cli);
				cout << "Cliente saiu" << endl;
			}
         }
         cout << "_______________________" << endl;
        }else{
            achou = false;
            cout << "Cliente nao encontrado, digite novamente: " << endl;
            cin >> cod_cliente;
            cli = busca_cliente(cod_cliente);
        }
    }while(!achou);
}
void chegada() {
    noPtr novo;
    int cod_cliente;
    novo = new cliente;
    cout << "_______________________" << endl;
    cout << "Digite o codigo do cliente: ";
    cin >> cod_cliente;
    novo->codC = cod_cliente;
    novo->proxC = inicio;
    inicio = novo;
    novo->prod = NULL;
    cout << "Cliente Adicionado" << endl;
    cout << "_______________________" << endl;
}
void listarC() {
    noPtr novo = inicio;
    if (!listaVazia()) {
    	cout << "_______________________" << endl;
        cout << "Os Clientes sao:" << endl;
        while (novo != NULL) {
            cout << novo->codC << "->";
            novo = novo->proxC;
        }
        cout << "NULL" << endl;
    }else{
        cout << "Nao ha clientes !!" << endl;
    }
    cout << "_______________________" << endl;
}
void valor_dia(){
	cout << "_______________________" << endl;
	cout << "Valor Total do dia: " << total_dia << endl;
	cout << "_______________________" << endl;
}
int menu() {
 int opcao;
    cout << "1: Chegada de um novo cliente - " << endl;
    cout << "2: Saida de um cliente - " << endl;
    cout << "3: Listar Clientes - " << endl;
    cout << "4: Consumo - " << endl;
    cout << "5: Listar Produtos Consumidos" << endl;
    cout << "6: Valor Acumulado do dia" << endl;
    cout << "0: Fechar Restaurante." << endl;
    cout << "Digite uma opcao (0-6): ";
    cin >> opcao;
return opcao;
}
int main() {
 int op;
    do {
        op = menu();
	    switch (op){
		    case 1: 
				chegada();
            	break;
            case 2:
 				saida();
 				break;
 			case 3:
 				listarC();
 				break;
 			case 4:
 				pedido();
 				break;
 			case 5:
 				listarP();
 				break;
 			case 6:
 				valor_dia();
 				break;
    	}
	}while(op!=0);
 return 0;
}

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct Participante{
    int id;
    string nome;
    int semestre;
    int ano;
    string curso;
    Participante* proximo;
}ALUNO;

struct Node {
    ALUNO aluno;
    Node *proximo;
};
struct Contribuicao{
    int idParticipante;
    int mes;
    int ano;
    float valor;
    Contribuicao* proxima;
};

struct Lista {
    Node *inicio;
    int tamanho;
    Contribuicao* inicioContribuicoes;
    int tamanhoContribuicoes;
};

void inicializarLista(Lista* );
void adicionarParticipante(Lista* );
void editarParticipante(Lista* , int );
void carregarParticipantes(Lista* );
void salvarParticipantes(Lista* );
void cadastrarContribuicao(Lista* );
void salvarContribuicoes(Lista* );
void sair(Lista* );


int main(){
Lista lista;
inicializarLista(&lista);

int escolha;
do
{
    cout << "Menu: \n";
    cout << "1. Adicionar participantes\n";
    cout << "2. Editar participantes\n";
    cout << "3. Carregar participantes de arquivo\n";
    cout << "4. Salvar participantes em arquivo\n";
    cout << "5. Cadastrar Contribuições\n";
    cout << "6. Salvar contribuições em arquivo\n";
    cout << "7. Salvar contribuições por curso\n";
    cout << "0. SAIR\n";
    cout << "Escolha uma opção: ";
    cin >> escolha;

    switch(escolha){
        case 1: {
            adicionarParticipante(&lista);
            break;
        }
        case 2: {
            int id;
            cout << "Digite o ID do participante a ser editado: ";
            cin >> id;
            editarParticipante(&lista, id);         
            break;
        }
        case 3: {
            carregarParticipantes(&lista);
            break;    
        }
        case 4: {
            
            salvarParticipantes(&lista);
            break;    
        }
        case 5: {
            
            cadastrarContribuicao(&lista);
            break;    
        }
        case 6: {
            
            salvarContribuicoes(&lista);
            break;    
        }
        /*case 7: {
            
            
            break;    
        }*/
        case 0:
            sair(&lista);
            break;
        
        default:
        cout << "Opção inválida. tente novamente." << endl;
        break;
    } 

} while (escolha != 0);
return 0;

}

void inicializarLista(Lista* lista){
    lista->inicio = NULL;
    lista->tamanho = 0;
    lista->inicioContribuicoes = NULL;
    lista->tamanhoContribuicoes = 0;
}

void adicionarParticipante(Lista* lista){
    ALUNO newParticipante;
    newParticipante.id = lista->tamanho + 1;
    
    cout << "Digite o nome do participante: ";
    cin >> newParticipante.nome;
    cout << "Digite o semestre de ingresso na Fatec Araras: ";
    cin >> newParticipante.semestre;
    cout << "Digite o ano de ingresso na Fatec Araras: ";
    cin >> newParticipante.ano;
    cout << "Digite o curso (DSM, SI ou GE): ";
    cin >> newParticipante.curso;
    
    Node* newNo = new Node;
    newNo->aluno = newParticipante;
    newNo->proximo = NULL;

    if(lista->inicio == NULL){
        lista->inicio = newNo;
    }else{
        Node* atual = lista->inicio;
        while(atual->proximo != NULL){
            atual = atual->proximo;
        }
        atual->proximo = newNo;
    }
    lista->tamanho++;
    cout << "Participante adicionado com sucesso!" << endl;

}

void editarParticipante(Lista* lista, int id){
    Node* atual = lista->inicio;
    while(atual != NULL){
        if(atual->aluno.id == id){
            cout << "Digite o nome do participante: ";
            cin >> atual->aluno.nome;
             cout << "Digite o semestre de ingresso na Fatec Araras: ";
            cin >> atual->aluno.semestre;
            cout << "Digite o ano de ingresso na Fatec Araras: ";
            cin >> atual->aluno.ano;
            cout << "Digite o curso (DSM, SI ou GE): ";
            cin >> atual->aluno.curso;
            cout << "Participante editado com sucesso!" << endl;
            return;
        }
        atual = atual->proximo;
    }
    cout <<" Participante com o ID " << id << " não encontrado. "<< endl;
}

void carregarParticipantes(Lista* lista){
    ifstream arquivo("participantes.txt");
    if(arquivo.is_open()){
        while(!arquivo.eof()){
            ALUNO newParticipante;
            if(arquivo >> newParticipante.id >> newParticipante.nome >> newParticipante.semestre >> newParticipante.ano >> newParticipante.curso){

                Node* newNo = new Node;
                newNo->aluno = newParticipante;
                newNo->proximo = NULL;

                if(lista->inicio == NULL){
                    lista->inicio = newNo;
                }else{
                    Node* atual = lista->inicio;
                    while(atual->proximo != NULL){
                        atual = atual->proximo;
                    }
                    atual->proximo = newNo;
                }
                lista->tamanho++;
            }
        }
        arquivo.close();
        cout<< "Participantes carregados com sucesso!" << endl;
    }else{
        cout<< "Erro ao abrir o arquivo participantes.txt" << endl;
    }
}

void salvarParticipantes(Lista* lista){
    ofstream arquivo("participantes.txt", ofstream::trunc);
    if(arquivo.is_open()){
        Node* atual = lista->inicio;
        while(atual != NULL){
            arquivo << atual->aluno.id << " " << atual->aluno.nome << " " << atual->aluno.semestre << " " << atual->aluno.ano << " " << atual->aluno.curso << endl;
            atual = atual->proximo;
        }
        arquivo.close();
        cout<< "Participantes salvos com sucesso!" << endl;
    }else{
        cout << "Erro ao abrir o arquivo participantes.txt" << endl;
    }
}

void cadastrarContribuicao(Lista* lista){
    int id;
    cout << "Digite o ID do participante para cadastrar a contribuição: ";
    cin >> id;

    Node* atual = lista->inicio;
    while(atual != NULL){
        if(atual->aluno.id == id){
            Contribuicao* novaContribuicao = new Contribuicao;
            novaContribuicao->idParticipante = id;
            cout << "Digite o mês da contribuição (1 a 12): ";
            cin >> novaContribuicao->mes;
            cout << "Digite o ano da contribuição: ";
            cin >> novaContribuicao->ano;
            cout << "Digite o valor da contribuição: ";
            cin >> novaContribuicao->valor;
            novaContribuicao->proxima = NULL;

            if(lista->inicioContribuicoes == NULL){
                lista->inicioContribuicoes = novaContribuicao;
            }else{
                Contribuicao* temp = lista->inicioContribuicoes;
                while(temp->proxima != NULL){
                    temp = temp->proxima;
                }
                temp->proxima = novaContribuicao;
            }
            lista->tamanhoContribuicoes++;
            cout << "Contribuiç~so cadastrada com sucesso!"<< endl;
            return;            
        }
        atual = atual->proximo;
    }
    cout << "Participante com o ID " << id << " não encontrado. Contribuição não cadastrada." << endl;
}

void salvarContribuicoes(Lista* lista){
    ofstream arquivo("contribuicoes.txt", ofstream::trunc);
    if(arquivo.is_open()){
        Contribuicao* atual = lista->inicioContribuicoes;
        while(atual != NULL){
            arquivo << atual->idParticipante << " " << atual->mes << " " << atual->ano << atual->valor << endl;
            atual = atual->proxima;
        }
        arquivo.close();
        cout << "Contribuições salvas com sucesso!" << endl;
    }else{
        cout << "Erro ao abrir o arquivo contribuições";
    }
}

void sair(Lista* lista){
    Node* atual = lista->inicio;
    while(atual != NULL){
        Node* temp = atual;
        atual = atual->proximo;
        delete temp;
    }

    Contribuicao* atualContribuicao = lista->inicioContribuicoes;
    while(atualContribuicao != NULL){
        Contribuicao* temp = atualContribuicao;
        atualContribuicao = atualContribuicao->proxima;
        delete temp;
    }
    cout << "Memória liberada e saindo do programa..."<<endl;
}


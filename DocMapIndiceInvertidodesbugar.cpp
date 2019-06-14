#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctype.h>
#include <map>
#include <string.h>
#include <string>
#include <set>
#include <list>
#include <fstream>



using namespace std;
string converter(string word);

class Doc {
private:
    string name_;
    map<string,double> palavras_;//map utilizado para saber se a palavra no campo STRING esta no documento e quantas vezes no campo DOUBLE

public:
    Doc (string n){//construtor da classe que coloca o nome do documento que o chamou.
    this->name_=n;
    }

    string filename(){//Retorna o nome do documento
    return this->name_;
    }

    void mapear (string word){//Insere no campo DOUBLE do map quantas vezes a palavra tem no documento.
    if (this->palavras_[word]==NULL){this->palavras_[word]=1;}//Se a palavra não existe ainda no map, a insere, colocando 1.
    else {this->palavras_[word]++;}//Caso a palavra ja esteja no Documento incrementa quantas vezes ela está la.
    }

    double find (string word){//Retorna quantas vezes uma palavra aparece no texto
    if (this->palavras_[word]==NULL){return 0;}//Retorna 0 vezes caso não tenha aquela palavra no map do documento.
    else {return this->palavras_[word];}//Retorna quantas vezes a palavra aparece no texto do documento.
    }

    int size(){
    return palavras_.size();
    }

    set<string> returnwords (){//Retorna um conjunto de string contendo as palavras no documento que a chamou.
    set<string> documentwords;
    map<string,double>::iterator it = this->palavras_.begin();
    while (it != this->palavras_.end()){
       cout<<it->first<<" ";
       documentwords.insert(it->first);
        it++;
    }
    cout<<endl<<endl;
    return documentwords;
    }

};


class Inv{
private:
    string name_;
    map<string,set<string> > inv_;// Map que guarda como CHAVE  a PALAVRA do vocabulario de todos os texto e o VALOR é um set de strings contendo o nome dos docs que tem essa palavra.
public:

    Inv (string n){// construtor da classe com nome.
    this->name_=n;
    }


    void mapear (string word, string nomedoc){//Insere no campo set<string> do map quais os documentos tem a palavra documento.
    inv_[word].insert(nomedoc);
    }


    set<string> busca(string word){//Busca se a palavra existe ou nao no indice invertido e retorna uma lista com os documentos com a palavra.

        set<string> docsnabusca;
        if(inv_[word].empty()){
                inv_.erase(word);
                return docsnabusca;
        }
        else{
            set<string>::iterator it = this->inv_[word].begin();
            while (it != inv_[word].end()){
                docsnabusca.insert(*it);
                it++;
            }
            return docsnabusca;
            }
    }


    int size(){//Retorna o tamanho de quantas palavras tem no vocabulario de todos os documentos
    return inv_.size();
    }



    void imprimeInv(){// Mostra todas as palavras do indice junto com os documentos que as contém.
    map<string,set<string> >::iterator it ;
    set<string>             ::iterator jt ;

    for (it = inv_.begin() ; it != inv_.end() ; it++){
        cout<<it->first<<endl;
        for (jt = it->second.begin() ; jt != it->second.end(); jt++){
            cout<< *jt <<endl;
        }
        cout<<endl<<endl;
    }

    }



    set<string> documentosdabusca(set<string> palavrasdabusca){//Função para retornar uma lista de documentos que contem todas as palavras da busca.

    set<string> docsallwords; // Conjunto de string resultante que contem a lista de documentos com todas as palavras da busca.
    set<string> ::iterator it = palavrasdabusca.begin();
    set<string> ::iterator jt ;

    while (it != palavrasdabusca.end()){//Laço while que pega palavra por paralavra e busca quais textos tem ou não tal palavra.
    if (docsallwords.empty()){
        docsallwords=busca(*it);
        if (docsallwords.empty()){
            return docsallwords;
        }
    }
    docsallwords=intersecao(docsallwords,busca(*it));
    it++;
    }
    return docsallwords;
    }//Fim função documentosdabusca.


    set<string> intersecao (set<string> a,set<string> b){// Função que faz a intersecao de dois conjuntos de string

    set<string> resultado;

    for (set<string>::iterator it = a.begin(); it != a.end() ;it++){
        for (set<string>::iterator jt = b.begin(); jt != b.end() ; jt++){
         if(*it==*jt)resultado.insert(*it);
    }
    }
         return resultado;
    }


};// Fim classe Índice Invertido Inv.





int main (){
Inv indiceinvertido("Indice invertido");
list<Doc> alldocs;
list<Doc>::iterator it = alldocs.begin();
int i=0;


while (i<3){
string nomearq,linha;

cout<<"Digite o nome do documento a ser inserido: ";
cin>>nomearq;
nomearq+=".txt";


vector<char>character;

ifstream documento;

documento.open(nomearq);


if (documento.is_open()){//Se o arquivo foi encontrado executar os comando do laço.
    alldocs.push_back(nomearq);
    it = alldocs.end();
    it--;
    while(getline(documento,linha)){//Laço para percorrer todo o conteudo do arquivo.

linha.resize(linha.size()+1);//Usado para o laço posterior saber quando há uma quebra de linha
linha.push_back('\n');//Usado para o laço posterior saber quando há uma quebra de linha

for (int i=0;i<linha.size();i++){//Laço para retirar palavra por palavra do documento.
    if (linha[i]=='.'||linha[i]==','||linha[i]==';'||linha[i]==':'||linha[i]=='!'||linha[i]=='?'){//laço para retirar caracteres de pontuação.
    }
    else if (linha[i]==' '){//laço para mandar para a função converter quando é identificado que a palavra acabou de ser retirada do texto completamente.

        string palavra( character.begin(), character.end() );
        palavra=converter(palavra);
        it->mapear(palavra);
        indiceinvertido.mapear(palavra,it->filename());
        palavra.clear();
        character.clear();

    }
    else if (linha[i]=='\n'){//laço para mandar para a função converter quando é identificado que a palavra acabou de ser retirada do texto completamente.

        string palavra( character.begin(), character.end() );
        palavra.pop_back();
        palavra=converter(palavra);
        it->mapear(palavra);
        indiceinvertido.mapear(palavra,it->filename());
        palavra.clear();
        character.clear();

    }
    else character.push_back(linha[i]);
}

    }



}

else{
cout<<"O arquivo nao pode ser encontrado, verifique se o arquivo esta dentro da pasta ou com o nome correto"<<endl;
}

documento.close();
i++;
}//fim while da inserção de documentos no programa



ofstream arquivobusca;//Inicio para produzir um documento com as palavras a serem procuradas
arquivobusca.open("busca.txt");
string busca;
cout<<endl<<"Digite sua busca : ";
fflush(stdin);
getline(cin,busca);
arquivobusca << busca;// Passagem do que foi digitado na string busca para um documento de texto com o nome busca.txt dentro do diretorio do programa.
arquivobusca.close();


Doc pesquisa("pesquisa");// Cria um documento da classe Doc para poder fazer operações.


ifstream abrebusca;
abrebusca.open("busca.txt");


if (abrebusca.is_open()){//Se o arquivo foi encontrado executar os comando do laço.
string linha;
vector<char>character;

    while(getline(abrebusca,linha)){//Laço para percorrer todo o conteudo do arquivo.

linha.resize(linha.size()+1);//Usado para o laço posterior saber quando há uma quebra de linha
linha.push_back('\n');//Usado para o laço posterior saber quando há uma quebra de linha

for (int i=0;i<linha.size();i++){//Laço para retirar palavra por palavra do documento.
    if (linha[i]=='.'||linha[i]==','||linha[i]==';'||linha[i]==':'||linha[i]=='!'||linha[i]=='?'){//laço para retirar caracteres de pontuação.
    }
    else if (linha[i]==' '){//laço para mandar para a função converter quando é identificado que a palavra acabou de ser retirada do texto completamente.

        string palavra( character.begin(), character.end() );
        pesquisa.mapear(converter(palavra));
        palavra.clear();
        character.clear();

    }
    else if (linha[i]=='\n'){//laço para mandar para a função converter quando é identificado que a palavra acabou de ser retirada do texto completamente.

        string palavra( character.begin(), character.end() );
        palavra.pop_back();
        pesquisa.mapear(converter(palavra));
        palavra.clear();
        character.clear();

    }
    else character.push_back(linha[i]);
}

    }

}

else{
cout<<"O arquivo nao pode ser encontrado, verifique se o arquivo esta dentro da pasta ou com o nome correto"<<endl;
}

abrebusca.close();//Fecha o arquivo que produz um documento para busca.


/*pesquisa.returnwords();*/

/*indiceinvertido.imprimeInv();*/


set<string> docsbusca;
docsbusca=indiceinvertido.documentosdabusca(pesquisa.returnwords());

if (docsbusca.empty()){
    cout<<"Nao ha documentos com essa busca =( "<<endl;
}
else{
set<string>::iterator db = docsbusca.begin();
cout<<"Os documentos que contem a busca sao =) : "<<endl<<endl;
while(db != docsbusca.end()){
    cout<<*db<<endl;
    db++;
}
}









/*
cout<<"O numero de palavras do vocabulario do documento de busca e : "<<pesquisa.size()<<endl;
cout<<"Existe a palavra no doc de pesquisa 1 sim 0 nao : "<<pesquisa.find("casa")<<endl;
cout<<"Existe a palavra no doc de pesquisa 1 sim 0 nao : "<<pesquisa.find("guardaroupa")<<endl;
cout<<"Existe a palavra no doc de pesquisa 1 sim 0 nao : "<<pesquisa.find("apartamento")<<endl;

*/



/*
it = alldocs.begin(); //inicio para testar se tem a palavra em um certo documento no Set<Doc> alldocs;
while (it != alldocs.end()){

cout<<it->find("eu")<<endl;
cout<<it->find("nos")<<endl;
cout<<it->find("campeao")<<endl;
cout<<it->find("casa")<<endl;
cout<<it->find("existe")<<endl;
cout<<it->find("entretanto")<<endl;
cout<<it->find("guardaroupa")<<endl;
cout<<it->find("coracao")<<endl;

cout<<it->filename()<<endl<<endl;
    it++;
}

cout<<"Quantos docs existem para busca :";
cout<<alldocs.size()<<endl;

indiceinvertido.busca("casa");

cout<<endl<<"Quantidade de palavras do vocabulario : "<<indiceinvertido.size();*/

return 0;
}/************************************************************************** FIM INT MAIN *****************************************************************************/




string converter(string word){//função para colocar a palavra em minúsculo e retirar hiféns.

int hifen=1;
while (hifen){
        hifen=0;

for (int i=0;i < word.size();i++){
    word[i]=tolower(word[i]);
    if (word[i]=='-'){
            hifen=1;
        for(int j=i;j<word.size();j++){
          word[j]=word[j+1];
        }
    word.pop_back();
    }
}
}
return word;
}




/*class Alldocs{
private:
    string nome_;
    list<Doc> alldocs_;
    list<Doc>::iterator it_;

public:
    Alldocs(string c){//construtor somente nome
    this->nome_ = c;
    }

    Alldocs(string c,list<Doc> d){// Construtor nome + lista
    this->nome_ = c;
    this->alldocs_ = d;
    }

    void inserir(list<Doc> d){// Coloca uma lista de documentos no objeto da classe
    this->alldocs_ = d;
    }

    bool find(string word){// Procurar o ducomento pelo nome.
    it_ = alldocs_.begin();

    while(it_ != alldocs_.end()){
        if (it_->filename()==word) {return true;}
        it_++;
    }
    return false;
    }

    int size(){//Retorna tamanho da lista de documentos
    return alldocs_.size();
    }


};*/






















/*
Alldocs todos("Lista De Todos Os Documentos");
list<Doc> alldocs;

int i=0;

while (i<3){
string nomearq;
cin>>nomearq;
alldocs.push_back(nomearq);
i++;
}

    todos.inserir(alldocs);

    list<Doc>::iterator it = alldocs.begin();

    while(it != alldocs.end()){
    cout<<it->namefile()<<endl;
    it++;
    }

    cout<<todos.find("doc1");
    cout<<todos.size();
*/







/*
Doc doc1("doc1.txt");
Doc doc2("doc2.txt");

doc1.mapear("azul");
doc1.mapear("branco");
doc1.mapear("vermelho");
doc1.mapear("casa");

doc2.mapear("casa");
doc2.mapear("apartamento");
doc2.mapear("lote");

set<string> conjuntodocs;

string word;
cout<<"Digite a palavra que deseja buscar : ";
cin>>word;

if (doc1.find(word)==true){conjuntodocs.insert(doc1.namefile());}
if (doc2.find(word)==true){conjuntodocs.insert(doc2.namefile());}
set<string>::iterator it = conjuntodocs.begin();

if (conjuntodocs.empty()){cout<<"Nao ha documentos que contem essa palavra :";}
else{
     cout<<"Os documentos que contem a palavra sao : ";
while(it != conjuntodocs.end()){
     cout<<*it<<"  "<<endl;
     it++;
}
}

*/












/*
Doc doc1("doc1.txt");
Doc doc2("doc2.txt");

doc1.mapear("azul");
doc1.mapear("branco");
doc1.mapear("vermelho");

doc2.mapear("casa");
doc2.mapear("apartamento");
doc2.mapear("lote");


set<string> alldocs;
alldocs.insert(doc1.namefile());
alldocs.insert(doc2.namefile());
set<string>::iterator it = alldocs.begin();

while (it != alldocs.end()){
    cout<<*it<<endl;
    it++;
}
*/












/*
set<int> i;
i.insert(40);
i.insert(10);
i.insert(70);
i.insert(20);
i.insert(30);
i.insert(70);
i.insert(30);

set<int>::iterator it = i.begin();

while(it != i.end()){
    cout<<*it<<endl;
    it++;
}

*/


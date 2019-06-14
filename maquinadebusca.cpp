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
#include <dirent.h>
#include <cmath>


using namespace std;
string converter(string word);

class Doc {
private:
    string name_;
    map<string,double> palavras_;//map utilizado para saber se a palavra no campo STRING esta no documento e quantas vezes no campo DOUBLE
    map<string,double> coordenadaW_;//A importancia de cada palavra dentro do documento.
    map<string,double> idf_;// Indice idf de cada palavra do documento
    double cosseno_=0;

public:

    Doc (string n){//construtor da classe que coloca o nome do documento que o chamou.
    this->name_=n;
    }//Fim do construtor da classe

    string filename(){//Retorna o nome do documento
    return this->name_;
    }//fim da função filename

    void mapear (string word){//Insere no campo DOUBLE do map quantas vezes a palavra tem no documento.
    if (this->palavras_[word]==NULL){this->palavras_[word]=1;}//Se a palavra não existe ainda no map, a insere, colocando 1.
    else {this->palavras_[word]++;}//Caso a palavra ja esteja no Documento incrementa quantas vezes ela está la.
    }//Fim da função mapear

    double find (string word){//Retorna quantas vezes uma palavra aparece no texto
    if (this->palavras_[word]==NULL){return 0;}//Retorna 0 vezes caso não tenha aquela palavra no map do documento.
    else {return this->palavras_[word];}//Retorna quantas vezes a palavra aparece no texto do documento.
    }//Fim da função find

    int size(){
    return palavras_.size();
    }//Fim da função size.

    set<string> returnwords (){//Retorna um conjunto de string contendo as palavras no documento que a chamou.
    set<string> documentwords;
    map<string,double>::iterator it = this->palavras_.begin();
    while (it != this->palavras_.end()){
       documentwords.insert(it->first);
        it++;
    }
    return documentwords;
    }//Fim da função return words

   void importidf(map<string,double> idf){
   this->idf_=idf;
   }
    map<string,double> returnidf (){//Retorna o idf das palavras do documento que o chamou.
    map<string,double>::iterator it = idf_.begin();

    while (it != idf_.end()){
    it++;
    }
    return idf_;
    }//Fim da função importaridf


    void coordenadaW(){
    map<string,double>::iterator it = palavras_.begin();
    while(it != palavras_.end()){
        coordenadaW_[it->first]=find(it->first)*idf_[it->first] ;
        it++;
    }
    }//Fim da função coordenadaW


    double returnW(string p){// Retorna a coordenadaW W(dj.pi) de uma palavra.
    return coordenadaW_[p];
    }//Fim da função returnW



    void cosseno(string p,double Wqpi){// Função ja automatizada que calcula (WdxP1 * WdxP2 * WdxPN .... )
    cosseno_= cosseno_ + (returnW(p)*Wqpi);
    }//Fim da função cosseno.

    double returncosseno(){
    return cosseno_;
    }//Fim da função returncosseno.


};//Fim classe Doc.


class Inv{
private:
    string name_;
    map<string,set<string> > inv_;// Map que guarda como CHAVE  a PALAVRA do vocabulario de todos os texto e o VALOR é um set de strings contendo o nome dos docs que tem essa palavra.
    map<string,double>       idf_;//Indice idf de cada palavra do vocabulario.
public:

    Inv (string n){// construtor da classe com nome.
    this->name_=n;
    }//Fim função contrutor Inv

    void mapear (string word, string nomedoc){//Insere no campo set<string> do map quais os documentos tem a palavra documento.
    inv_[word].insert(nomedoc);
    idf_[word]=NULL;
    }//Fim função mapear

    int size(){//Retorna o tamanho de quantas palavras tem no vocabulario de todos os documentos
    return inv_.size();
    }//Fim função size.

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
    }//Fim função busca

    set<string> documentosdabusca(set<string> palavrasdabusca){//Função para retornar uma lista de documentos que contem todas as palavras da busca.

    set<string> docsallwords;// Conjunto de string resultante que contem a lista de documentos com todas as palavras da busca.
    set<string> espelho;
    set<string> ::iterator it = palavrasdabusca.begin();
    while (it != palavrasdabusca.end()){//Laço while que pega palavra por paralavra e busca quais textos tem ou não tal palavra.
    espelho=busca(*it);
    set<string> ::iterator jt = espelho.begin();
    while (jt != espelho.end()){
        docsallwords.insert(*jt);
        jt++;
    }
    it++;
    }
    return docsallwords;
    }//Fim função documentosdabusca.


    void calcularidf (int n){// Calcula idf N é o numero de documentos totais.
    map<string,set<string> >::iterator it ;

    for (it = inv_.begin() ; it != inv_.end() ; it++){
        idf_[it->first]=log (n*1.000000/it->second.size()*1.000000);
    }
    }//Fim função calcularidf


    double returnidf (string word){//Retorna o idf da palavra desejada.
    return idf_[word];
    }//fim função returnidf


    map<string,double> exportidf (set<string> word){
    map<string,double> idf;
    set<string>::iterator it = word.begin();

    while (it != word.end()){
    idf[*it]=idf_[*it];
    it++;
    }
    return idf;
    }//Fim função exportaridf

};// Fim classe Índice Invertido Inv.

                                            /***********************************************************************************/
/********************************************************************* INÍCIO INT MAIN ********************************************************************************/
                                           /***********************************************************************************/

int main (){
list<string> nomearquivos;

 DIR *dir;// Aqui começa a buscar todos os arquivos .txt do diretorio onde esta o arquivo.
    struct dirent *lsdir;

    dir = opendir("c:\\Users\\victor lambertucci\\Desktop\\TP PRONTO");


    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        string nome( lsdir->d_name );

        if (nome[(nome.size()-4)]=='.'&&nome[(nome.size()-3)]=='t'&&nome[(nome.size()-2)]=='x'&&nome[(nome.size()-1)]=='t'){//Lista somente arquivos com final .txt
            if (nome=="busca.txt"){}
            else {
                nomearquivos.push_back(nome);
            }
        }


    }

    closedir(dir);// Aqui finaliza a busca dos arquivos do diretorio.

    list<string>::iterator na = nomearquivos.begin();


Inv indiceinvertido("Indice invertido");
list<Doc> alldocs;
list<Doc>::iterator it = alldocs.begin();
int contador=0;


while (contador<nomearquivos.size()){//Laço while que começa a mapear cada arquivo como 1 DOC na lista de documentos alldocs.
string nomearq,linha;

nomearq = *na;

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
na++;
contador++;
}//fim while da inserção de documentos no programa


ofstream arquivobusca;//Inicio para produzir um documento de busca com as palavras a serem procuradas
arquivobusca.open("busca.txt");
string busca;
cout<<endl<<"Digite sua busca : ";
fflush(stdin);
getline(cin,busca);
arquivobusca << busca;// Passagem do que foi digitado na string busca para um documento de texto com o nome busca.txt dentro do diretorio do programa.
arquivobusca.close();// Fecha a inicialização do documento de busca.

Doc pesquisa("pesquisa");// Cria um documento da classe Doc para poder fazer operações.

ifstream abrebusca;//Inicia a intrudução do documento de busca a um objeto da classe Doc
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


set<string> docsbusca;//Nome com os Documentos onde contem pelo menos uma palavra da busca
docsbusca=indiceinvertido.documentosdabusca(pesquisa.returnwords());

if (docsbusca.empty()){
    cout<<"Nao ha documentos relacionados com essa busca =( "<<endl;
}
else{
set<string>::iterator db = docsbusca.begin();
cout<<"O(s) documento(s) que contem alguma palavra busca e(sao) =) : "<<endl<<endl;
while(db != docsbusca.end()){
    cout<<*db<<endl;
    db++;
}
}

indiceinvertido.calcularidf(alldocs.size());


it = alldocs.begin();// exportar para cada doc o respectivo idf do conjunto de palavras dentro de todos os docs.
while (it != alldocs.end()){
    it->importidf(indiceinvertido.exportidf(it->returnwords()));
    it++;
}

pesquisa.importidf(indiceinvertido.exportidf(pesquisa.returnwords()));
pesquisa.coordenadaW();


it = alldocs.begin();
while (it != alldocs.end()){
   it->coordenadaW();
    it++;
}

set<string> searchdocs = pesquisa.returnwords();

for (it = alldocs.begin(); it != alldocs.end() ;it++){// Laço for para rankear a busca com os documentos a partir do cosseno.
    for (set<string>::iterator db = docsbusca.begin(); db != docsbusca.end() ;db++){

        if (it->filename()==*db){
        for(set<string>::iterator vx = searchdocs.begin(); vx != searchdocs.end() ; vx++){
        it->cosseno(*vx,pesquisa.returnW(*vx));
        }
        }
    }
}// Fim laço for que rankeia pelo cosseno.


map<double,set<string> >  ranking;//Mapear os documentos pelo ranking e retornar os docs da busca.
it = alldocs.begin();
int contacos=0;// Variavel para contar quantas vezes há cosseno 0 no conjunto de documentos.
while (it != alldocs.end()){
    if (it->returncosseno()!= 0){
    ranking[(1/(it->returncosseno()))].insert(it->filename());//Inverte o cossento para poder ser representado no map, de forma onde o mais significativo é o que tem maior cosseno.
    }
    else {contacos++;}
    it++;
}

if(contacos==alldocs.size()){}
else {
    map<double,set<string> >::iterator rk ;
    set<string>             ::iterator jt ;
    int countrank = 0;
cout <<"**************DOCUMENTOS POR ORDEM DE IMPORTANCIA**************"<<endl;
    for (rk = ranking.begin() ; rk != ranking.end() ; rk++){
            countrank++;
           cout<<"|"<< countrank <<"o  ---> ";
        for (jt = rk->second.begin() ; jt != rk->second.end(); jt++){
            cout<< *jt <<"   ";
        }
        cout<<endl<<endl;
    }
}

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


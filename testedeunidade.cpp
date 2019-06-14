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
#include <set>
#include <list>


using namespace std;

class test{

public:
    static map.palavras_(const Doc& c) {
    return  c.palavras_;
    }
     static string name_(const Doc& c) {
    return   c.name_;
     }
TEST_SUIT("Doc"){
TEST_CASE ( "Doc(string)");
Doc d;
d.Doc("doc1");
check(teste:: name(d)=="doc1")
}
TEST_CASE("filename()"){
Doc d;
d.filename() = doc1
check(teste:: name(d)= "doc1");

}
TEST_CASE ("mapear(string)"){
Doc d;
d.insert ("a");
d.insert ("a");
check(teste:: d.mapear("a") == 2);
}

TEST_CASE ("find(string)"){
Doc d;
d.insert ("a");
d.insert ("a");
d.insert ("b");
check(teste:: d.find("a") == 2);
}

TEST_CASE ("size()"){
Doc d;
d.insert ("a");
d.insert ("a");
d.insert ("b");
check(teste::d.size() = 3);
}

TEST_CASE ("returnwords()"){
Doc d;
d.insert ("a");
d.insert ("a");
d.insert ("b");
check(teste::d.returnwords() == "a" "b");
}
};

TEST_SUIT("inv"){
TEST_CASE("mapear(string)"){
inv d;
d["a"].insert("doc1");
d["a"].insert("doc2");
check(teste::d.mapear()== "doc1, doc2");
}
TEST_CASE("size()"){
inv d;
d["a"].insert("doc1");
d["b"].insert("doc2");
check(teste::d.size() == 2;

}
TEST_CASE("busca(string)"){
inv d;
d["a"].insert("doc1");
d["b"].insert("doc2");
check(teste::d.busca("a") = "doc1";
check(teste::d.busca("b") = "doc2";
}

TEST_SUIT("alldocs"){
TEST_CASE("inserir(list<string>)"){
Alldocs d;
d.inserir("doc1");
d.inserir("doc2");
check(teste::d.find("doc1") );
check(teste::d.find("doc2") );
}
TEST_CASE("inserir(list<string>)"){
Alldocs d;
d.inserir("doc1");
d.inserir("doc2");
check(teste::d.find("doc1") );
check(teste::d.find("doc2") );
}


};


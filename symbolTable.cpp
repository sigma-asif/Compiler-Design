#include <bits/stdc++.h>
using namespace std;
struct token{
    string t;
    string l;
};
/*vector<token>tokens = {
        {"kw","float"},{"id","n1"},{"op","="},{"num","3.125"},{"sep",";"}
};*/
vector<token> tokens = {
        {"kw", "float"}, {"id", "x1"}, {"op", "="}, {"num", "3.125"}, {"sep", ";"},
        {"kw", "double"}, {"id", "f1"}, {"par", "("}, {"kw", "int"}, {"id", "x"}, {"par", ")"}, {"brc", "{"},
        {"kw", "double"}, {"id", "z"}, {"sep", ";"}, {"id", "z"}, {"op", "="}, {"num", "0.01"}, {"sep", ";"},
        {"kw", "return"}, {"id", "z"}, {"sep", ";"}, {"brc", "}"},
        {"kw", "int"}, {"id", "main"}, {"par", "("}, {"kw", "void"}, {"par", ")"}, {"brc", "{"},
        {"kw", "int"}, {"id", "n1"}, {"sep", ";"}, {"kw", "double"}, {"id", "z"}, {"sep", ";"},
        {"id", "n1"}, {"op", "="}, {"num", "25"}, {"sep", ";"}, {"id", "z"}, {"op", "="}, {"id", "f1"}, {"par", "("}, {"id", "n1"}, {"par", ")"}, {"sep", ";"}, {"brc", "}"}
};

struct entity{
    string n, id, dt, sc, val;
    entity(string n1, string id1, string dt1, string sc1, string val1){
        n = n1;
        id = id1;
        dt = dt1;
        sc = sc1;
        val = val1;
    }

};
vector<entity>table;

void insert(string n1,string id1, string dt1, string sc1, string val1){
    table.push_back(entity(n1,id1,dt1,sc1,val1));
    cout<<"inserted:"<<n1<<endl;
}

void update(string n1,string sc1,string val1){
    for(auto &i: table){
        if(i.n == n1 && i.sc == sc1){
            i.val = val1;
        }
    }
}
void display(){
    cout<<setw(15)<<"Name"<<setw(15)<<"Identifier"<<setw(15)<<"DataType"<< setw(15)<<"Scope"<<setw(15)<<"Value"<<endl;
   for(auto i:table){
       cout<<setw(15)<<i.n<<setw(15)<<i.id<<setw(15)<<i.dt<< setw(15)<<i.sc<<setw(15)<<i.val<<endl;
   }
}
void parse_token(){
    string n1,id1,dt1,sc1= "global",val1;
    stack<string >s;
    for(int i = 0; i<tokens.size(); i++){
        if(tokens[i].t == "kw"){
            dt1 = tokens[i].l;
        }
        else if(i<tokens.size()-2 && tokens[i].t == "id" && tokens[i+1].l =="="){
            n1 = tokens[i].l;
            val1 = tokens[i+2].l;
            id1 = "var";


            bool exists = false;

            for(const auto i: table){
                if(i.n == n1 && i.sc == sc1){
                    exists = true;
                    break;
                }
            }
            if(exists){
                update(n1,sc1,val1);
                val1.clear();
            }
            else{
                insert(n1,id1,dt1,sc1,val1);
                val1.clear();
            }
        }
        else if(tokens[i].t == "id"){ // fun or key
            if(i<tokens.size()-1 && tokens[i+1].l == "("){
                n1 = tokens[i].l;
                id1 = "func";
                insert(n1,id1,dt1,sc1,"");
                sc1 = n1;
                val1.clear();

            }
            //assigned var declara
            else if(i<tokens.size()-2 && tokens[i+1].l == "="){

                    n1 = tokens[i].l;
                    id1 = "var";
                    val1 = tokens[i+2].l;
                    insert(n1,id1,dt1,sc1,val1);
                    val1.clear();


            }
            else if(i<tokens.size()-1 && tokens[i+1].l == ";"){ //unassigned var declarion
                n1 = tokens[i].l;
                id1 = "var";
                insert(n1,id1,dt1,sc1," ");
                val1.clear();
            }
        }
        //z = fun/25 id op id/num assigned

        else if(i<tokens.size() && tokens[i].t == "brc" && tokens[i].l == "{"){
            s.push(sc1);
        }
        else if(i<tokens.size() && tokens[i].t == "brc" && tokens[i].l == "}"){
            s.pop();
            if(s.empty()){
                sc1 = "global";
            }
            else{
                sc1 = s.top();
            }
        }
    }
}
int main() {
     //display();
     parse_token();
     display();
    return 0;
}


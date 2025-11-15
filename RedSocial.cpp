#include "RedSocial.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

RedSocial::RedSocial(){
    this->_usuarios;
    this->_conocidos;
    this->_conocidos_usuarios_mas_popular;
    this->_usuario_a_id;
    this->_id_a_usuario;
    this->_cantidad_de_amigos=0;
    this->_amigos;
}

const set<int> & RedSocial::usuarios() const{
    // borrar todo esto y escribir algo correcto
    // este set "static" debe desaparecer y tiene que devolverse
    // algo de la estructura de representación de la clase
    return this->_usuarios;
}

string RedSocial::obtener_alias(int id) const{
    // borrar todo esto y escribir algo correcto
    return this->_id_a_usuario.at(id);
    
}
const set<string> & RedSocial::obtener_amigos(int id) const{
    // borrar todo esto y escribir algo correcto
    // este set "static" debe desaparecer y tiene que devolverse
    // algo de la estructura de representación de la clase
    return this->_amigos.at(id);
    
}

const set<string> & RedSocial::obtener_conocidos(int id) const{
    // borrar todo esto y escribir algo correcto
    // este set "static" debe desaparecer y tiene que devolverse
    // algo de la estructura de representación de la clase
    return this->_conocidos.at(id);
}
int RedSocial::cantidad_amistades() const{
    // Borrar esto y escribir algo correcto
    return this->_cantidad_de_amigos;
}

void RedSocial::registrar_usuario(string alias, int id){
    this->_usuarios.insert(id);
    this->_id_a_usuario[id] = alias;
    this->_usuario_a_id[alias] = id;
    this->_amigos[id] = set<string>();  // Inicializar con set vacío
    this->_conocidos[id] = set<string>(); // Inicializar con set vacío
    
    if(this->_usuarios.size() == 1){
        this->_conocidos_usuarios_mas_popular = this->_conocidos[id];
    }
    else{
        //ver si cambia el usuario con mas conocidos
        auto ittt= this->_conocidos.begin(); //primer elemento del set de amigos del que voy a eliminar
        int id_mas_grande= ittt->first;//el id del primero
        for(ittt; ittt!=this->_conocidos.end(); ittt++){
            if(ittt->second.size() > this->_conocidos.at(id_mas_grande).size()){
                id_mas_grande= ittt->first;
            }
        }

        //actualizo usuario ams conocido
        this->_conocidos_usuarios_mas_popular= this->_conocidos.at(id_mas_grande);
    }

}

void RedSocial::eliminar_usuario(int id){
    /*
    tengo que:
    -check=>sacarlo del set de usuarios

    -check=>eliminarlo de ambos set de nombre de usuarios

    -check=>eliminarlo del map de amigos

    -check=>y del de conocidos

    - check=>y tengo que eliminarlo de todos los sets del resto de los usuarios

    -check=>antes de eliminarlo de amigos veo el taman~0 de su set y se lo resto a cantidad de amistades 
    
    -check=> antes de eliminarlo de amistades, recorro el set con iterador(total no importa el orden) y voy
    eliminando en cada set de cada amigo su amistad
    */
    if(this->_usuarios.size()==1){
        this->_usuarios.erase(--this->_usuarios.end());
        this->_conocidos.clear();
        this->_conocidos_usuarios_mas_popular.clear();//va a estar vacio
        this->_usuario_a_id.clear();
        this->_id_a_usuario.clear();
        this->_cantidad_de_amigos=0;
        this->_amigos.clear();
        return;
    }
    
    int cant_amigos= this->_amigos[id].size();
    this->_cantidad_de_amigos= this->_cantidad_de_amigos-cant_amigos; //le resto las amistades

    string a_eliminar= this->_id_a_usuario[id];
    //recorro el mapa de amigos, eliminando si esta en cada set el id este
    auto it= this->_amigos[id].begin(); //primer elemento del set de amigos del que voy a eliminar

    while(it != this->_amigos[id].end()){//hasta que recorra todo el set de sus amigos

        int idd= this->_usuario_a_id[*it];//pasamos a id el string del set de _amigos del que vamos a eliminar
        this->_amigos.at(idd).erase(a_eliminar);//eliminamos de cada set de amigos al que vamos a eliminar
        it++;
    }
    this->_amigos.erase(id); //lo borramos de la lista de amigos 

    //recorro todo el map de conocidos, y me borro si encuentra

    auto itt= this->_conocidos.begin(); //primer elemento del set de amigos del que voy a eliminar

    for(itt; itt!= this->_conocidos.end(); itt++){
        
        if(this->_conocidos[itt->first].find(a_eliminar) != this->_conocidos[itt->first].end()){//si lo encuentra en el set
            this->_conocidos[itt->first].erase(a_eliminar);// lo elimina
        }
    }
    this->_conocidos.erase(id); //lo borramos de todo el mapa
    
    this->_usuarios.erase(id); //borro del set de usuarios

    //ver si cambia el usuario con mas conocidos
    auto ittt= this->_conocidos.begin(); //primer elemento del set de amigos del que voy a eliminar
    int id_mas_grande= ittt->first;//el id del primero
    for(ittt; ittt!=this->_conocidos.end(); ittt++){
        if(ittt->second.size() > this->_conocidos.at(id_mas_grande).size()){
            id_mas_grande= ittt->first;
        }
    }

    //actualizo usuario ams conocido
    this->_conocidos_usuarios_mas_popular= this->_conocidos.at(id_mas_grande);

    string alias= this->_id_a_usuario[id];

    //lo borro de estos mapas
    this->_usuario_a_id.erase(alias);
    this->_id_a_usuario.erase(id);

    
}
void RedSocial::amigar_usuarios(int id_A, int id_B){
    /*
    tengo que:
    -check=> actualizar cantidad de amigos
    -check=> sumarle al set de amigos de cada id
    -check=>sumarle a cada set de conocidos, los amigos del otro que no son amigos
    -revisar quien es el mas conocido
    -////// HACER////// SI SON CONOCIDOS, SACAR DE CONOCIDOS
    */
   //sumo cantidad de amigos
    this->_cantidad_de_amigos++;

    //paso de id a alias
    string aliasA= this->_id_a_usuario[id_A];
    string aliasB= this->_id_a_usuario[id_B];
    

    //an~ado a los amigos al diccionario amigos
    this->_amigos[id_A].insert(aliasB);
    this->_amigos[id_B].insert(aliasA);
    
    
    //creo punteros
    auto it_amigos_A= this->_amigos[id_A].begin();
    auto it_amigos_B= this->_amigos[id_B].begin();
    

    
    //ciclo para an~adir conocidos a B
    for(it_amigos_A; it_amigos_A != this->_amigos[id_A].end(); it_amigos_A++){
            if(*it_amigos_A != aliasB && this->_amigos[id_B].find(*it_amigos_A) == this->_amigos[id_B].end()){//si un amigo de a no esta en la lista de amigos de b...
                this->_conocidos[id_B].insert(*it_amigos_A);//lo inserta en la lista de conocidos de a
            }
    }

    //ciclo para an~adir conocidos a A
    for(it_amigos_B; it_amigos_B != this->_amigos[id_B].end(); it_amigos_B++){
            if(*it_amigos_B != aliasA && this->_amigos[id_A].find(*it_amigos_B) == this->_amigos[id_A].end()){//si un amigo de b no esta en la lista de amigos de a...
                this->_conocidos[id_A].insert(*it_amigos_B);//lo inserta en la lista de conocidos de b
            }
    }
    
    it_amigos_A= this->_amigos[id_A].begin();
    it_amigos_B= this->_amigos[id_B].begin();
    //tengo que actualizar la lista de conocidos de cada amigo de a
    for(it_amigos_A; it_amigos_A != this->_amigos[id_A].end(); it_amigos_A++){
        //si el amigo i de a, no tiene de amigo a b, se lo suma a la lista del amigo i de a, a conocidos
        int amigo_actual= this->_usuario_a_id[*it_amigos_A];
        if(this->_amigos[amigo_actual].find(aliasB) == this->_amigos[amigo_actual].end() ){
            this->_conocidos[amigo_actual].insert(aliasB);
        }
    }

    //actualizar la lista de conocidos de cada amigo de b
    for(it_amigos_B; it_amigos_B != this->_amigos[id_B].end(); it_amigos_B++){
        //si el amigo i de a, no tiene de amigo a b, se lo suma a la lista del amigo i de a, a conocidos
        int amigo_actual= this->_usuario_a_id[*it_amigos_B];
        if(this->_amigos[amigo_actual].find(aliasA) == this->_amigos[amigo_actual].end() ){
            this->_conocidos[amigo_actual].insert(aliasA);
        }
    }

     //elimino a mano a si mismo de cada id

    this->_conocidos[id_A].erase(aliasA);
    this->_conocidos[id_B].erase(aliasB);

    it_amigos_A= this->_amigos[id_A].begin();
    it_amigos_B= this->_amigos[id_B].begin();

    auto it_conocidos_A= this->_conocidos[id_A].begin();
    auto it_conocidos_B= this->_conocidos[id_B].begin();

    //chequeo que por cada amigo de a, no este en su lista de conocidos
    //por cada conocido que tiene, se fija si esta en la lista de amigos de el mismo,
    //si esta, lo saca
    for(it_conocidos_A; it_conocidos_A != this->_conocidos[id_A].end(); it_conocidos_A++){
        this->_amigos[id_A].begin();
        for(it_amigos_A; it_amigos_A != this->_amigos[id_A].end(); it_amigos_A++){
            if(*it_conocidos_A == *it_amigos_A){
                this->_conocidos[id_A].erase(*it_conocidos_A);
            }
        }
    }

    //chequeo que por cada amigo de b, no este en su lista de conocidos
    for(it_conocidos_B; it_conocidos_B != this->_conocidos[id_B].end(); it_conocidos_B++){
        this->_amigos[id_B].begin();
        for(it_amigos_B; it_amigos_B != this->_amigos[id_B].end(); it_amigos_B++){
            if(*it_conocidos_B == *it_amigos_B){
                this->_conocidos[id_B].erase(*it_conocidos_B);
            }
        }
    }

    //actualizo la lista de mas concocido
    auto ittt= this->_conocidos.begin(); //primer elemento del set de amigos del que voy a eliminar
    int id_mas_grande= ittt->first;//el id del primero
    for(ittt; ittt!=this->_conocidos.end(); ittt++){
            if(ittt->second.size() > this->_conocidos.at(id_mas_grande).size()){
               id_mas_grande= ittt->first;
            }
        }



   
}

void RedSocial::desamigar_usuarios(int id_A, int id_B){
    /*
    tengo que:
    -check=> restarle a uno la cant de amigos
    -check=>sacarlo de la lista de amigos de cada uno
    -check=>checkear que la lista de conocidos este bien...
    -check=>volver a hacer el chequeo del set de mas conocidos
    */
    this->_cantidad_de_amigos--;

    string aliasA= this->_id_a_usuario[id_A];
    string aliasB= this->_id_a_usuario[id_B];

    //saco de ambas listas de amigos
    this->_amigos[id_A].erase(aliasB);
    this->_amigos[id_B].erase(aliasA);

    
    //saco de las listas de conocidos
    //puntero a conocidos de a
    auto conocidos_a= this->_conocidos[id_A].begin();

    vector<string> conocidos_a_borrar_A;

    //ciclo por cada conocido de a
    for(conocidos_a; conocidos_a != this->_conocidos[id_A].end(); conocidos_a++){
        //ciclo que revise por cada amigo de a
        auto amigos_a= this->_amigos[id_A].begin();
        int cont=0;
        for(amigos_a; amigos_a != this->_amigos[id_A].end(); amigos_a++){
            if(this->_amigos[id_A].find(*conocidos_a) != this->_amigos[id_A].end()){//si lo encuentra al menos una vez...
                cont++;//suma 1
                break;//hace break del ciclo interno
            }
        }
        if(cont == 0){//si no encontro a ninguno, lo tenemos que borrar de la lista de conocidos
            conocidos_a_borrar_A.push_back(*conocidos_a);
        }
    }    

    //ahora borramos a todos del vector conocidos a borrar

    for(int i=0; i<conocidos_a_borrar_A.size(); i++){
        this->_conocidos[id_A].erase(conocidos_a_borrar_A[i]);//borra cada uno de esos conocidos(erase del set de strings)
    }

    //ahora lo mismo con b
    auto conocidos_b= this->_conocidos[id_B].begin();

    vector<string> conocidos_a_borrar_B;

    //ciclo por cada conocido de a
    for(conocidos_b; conocidos_b != this->_conocidos[id_B].end(); conocidos_b++){
        //ciclo que revise por cada amigo de a
        auto amigos_b= this->_amigos[id_B].begin();
        int cont=0;
        for(amigos_b; amigos_b != this->_amigos[id_B].end(); amigos_b++){
            if(this->_amigos[id_B].find(*conocidos_b) != this->_amigos[id_B].end()){//si lo encuentra al menos una vez...
                cont++;//suma 1
                break;//hace break del ciclo interno
            }
        }
        if(cont == 0){//si no encontro a ninguno, lo tenemos que borrar de la lista de conocidos
            conocidos_a_borrar_B.push_back(*conocidos_b);
        }
    }    

    //ahora borramos a todos del vector conocidos a borrar

    for(int i=0; i<conocidos_a_borrar_B.size(); i++){
        this->_conocidos[id_B].erase(conocidos_a_borrar_B[i]);//borra cada uno de esos conocidos(erase del set de strings)
    }


    //ver si cambia el usuario con mas conocidos
    auto ittt= this->_conocidos.begin(); //primer elemento del set de amigos del que voy a eliminar
    int id_mas_grande= ittt->first;//el id del primero
    for(ittt; ittt!=this->_conocidos.end(); ittt++){
        if(ittt->second.size() > this->_conocidos.at(id_mas_grande).size()){
            id_mas_grande= ittt->first;
        }
    }

    //actualizo usuario ams conocido
    this->_conocidos_usuarios_mas_popular= this->_conocidos.at(id_mas_grande);
}

int RedSocial::obtener_id(string alias) const{
    return this->_usuario_a_id.at(alias);
}
const set<string> & RedSocial::conocidos_del_usuario_mas_popular() const{
    return this->_conocidos_usuarios_mas_popular;
}

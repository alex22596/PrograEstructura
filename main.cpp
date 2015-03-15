#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

struct Sector{
//Lista de los sectores

    string tipoSector;
    float porcentaje;

    struct Sector *sig;//Lista simple

    Sector(string t,float p){
        tipoSector = t;
        porcentaje = p;
        sig = NULL;
    }
}*primeroS;

struct Localidad{
//Lista de las ubicaciones

    string nombre;
    string clasificacion;
    int consumoTotal;

    struct Localidad *sig;//Lista Circular
    struct subLocalidadSector *enlaceSubLS;//Enlace a la sublista localidad-sector
    struct subLocalidadVivienda *enlaceSubLV;//Enlace a la sublista localidad-vivenda

    Localidad(string n,string c, int co){
        nombre = n;
        clasificacion = c;
        consumoTotal = co;
        sig = NULL;
        enlaceSubLS = NULL;
        enlaceSubLV = NULL;
    }

}*primeroU;

struct tipoEnergia{
//Lista de tipos de energia
    string tipo;
    float porcentaje;

    struct tipoEnergia *sig;//Lista Simple

    tipoEnergia(string t,float p){
        tipo = t;
        porcentaje = p;
        sig = NULL;

    }
}*primeroE;

struct aparatosElectricos{
//Lista de aparatos electricos

    string nombre;
    int ID;
    int consumoTotal;

    struct aparatosElectricos *sig;//Lista circular

    aparatosElectricos(string n, int c, int id){
        nombre = n;
        consumoTotal = c;
        ID = id;
        sig = NULL;
    }
}*primeroEL;

struct personas{
//Lista de las personas

    string nombre;
    string apellido;
    string clasificacion;
    int consumoMax;
    int ID;

    struct personas *sig,*ant;//Lista doble
    struct subPersonaConsumo *enlaceSubPC;//Enlace sublista persona-consumo

    personas(string n,string a,string c,int co,int id){
        nombre = n;
        apellido = a;
        clasificacion = c;
        consumoMax = co;
        ID = id;
        sig = NULL;
        ant = NULL;
        enlaceSubPC = NULL;
    }
}*primeroP;

struct vivienda{
//Lista de las viviendas

    int ID;
    int consumoMax;

    struct vivienda *sig;//Lista simple
    struct subViviendaPersonas *enlaceSubVP;//Enlace a la sub lista vivienda-personas
    struct subViviendaConsumo *enlaceSubVC;//Enlace a la sub lista vivienda-consumo

    vivienda(int id,int c){
        ID = id;
        consumoMax = c;
        sig = NULL;
        enlaceSubVP = NULL;
        enlaceSubVC = NULL;
    }

}*primeroV;

struct consumo{
//Lista de los consumos

    int cantidad;

    struct consumo *sig;//Lista Simple

    consumo(int c){
        cantidad = c;
        sig = NULL;
    }

}*primeroC;

struct subLocalidadSector{
//Sub lista de localidades y sectores

    struct subLocalidadSector *sig;//Lista simple
    struct Sector *enlaceSector;//Enlace a la lista sector

};

struct subLocalidadVivienda{
//Sub lista de localidad y viviendas

    struct subLocalidadVivienda *sig;//Lista simple
    struct vivienda *enlaceVivienda;//Enlace a la lista vivienda

};

struct subViviendaPersonas{
//Sub lista de vivienda y persona

    struct subViviendaPersonas *sig;//Lista simple
    struct personas *enlacePersona;//Enlace a la lista persona

};

struct subViviendaConsumo{
//Sub lista de vivienda y consumo

    struct subViviendaConsumo *sig;//Lista simple
    struct consumo *enlaceConsumo;

};

struct subPersonaConsumo{
//Sub lista de persona y consumo

    struct subPersonaConsumo *sig;//Lista simple
    struct consumo *enlacePConsumo;//Enlace de persona-consumo

};

//*********************BUSCAR********************

struct Localidad * buscarLocalidad(string n){
    if(primeroU == NULL)
        return NULL;
    else{
        struct Localidad * temp = primeroU;
        do{
            if(temp->nombre == n){
                return temp;
            }
            temp = temp -> sig;
        }while(temp -> sig != primeroU);
        return NULL;
    }
}

struct Sector * buscarSector(string t){
    if(primeroS == NULL){
        return NULL;
    }
    else{
        struct Sector * temp = primeroS;
        while(temp != NULL){
            if(temp->tipoSector == t){
                return temp;
            }
            temp = temp->sig;
        }
        return NULL;
    }
}

struct personas * buscarPersona(int id){
    if(primeroP == NULL){
        return NULL;
    }
    else{
        struct personas * temp = primeroP;
        while(temp != NULL){
            if(temp->ID == id){
                return temp;
            }
            else{
                temp = temp->sig;
            }
        }
        return NULL;
    }
}

struct aparatosElectricos *  buscarAparatoElectrico(int id){
    if(primeroEL == NULL){
        return NULL;
    }
    else{
        struct aparatosElectricos * temp = primeroEL;
        do{
            if(temp->ID == id){
                return temp;
            }
            temp = temp -> sig;
        }while(temp->sig != primeroEL);
        return NULL;
    }
}

struct tipoEnergia * buscarTipoEnergia(string t){
    if(primeroE == NULL){
        return NULL;
    }
    else{
        struct tipoEnergia * temp = primeroE;
        while(temp!= NULL){
            if(temp->tipo == t){
                return temp;
            }
            temp = temp -> sig;
        }
        return NULL;
    }
}

struct vivienda * buscarVivienda(int id){
    if(primeroV == NULL){
        return NULL;
    }
    else{
        struct vivienda * temp = primeroV;
        while(temp!= NULL){
            if(temp->ID == id){
                return temp;
            }
            temp = temp ->sig;
        }
        return NULL;
    }
}

//*******************INSERTAR **********************

void insertarLocalidad(string n){
//Metodo donde se inserta las localidades, resibe el nombre

    struct Localidad *existe = buscarLocalidad(n);

    if(existe == NULL){
        struct Localidad *nuevaLocalidad = new Localidad(n,"",0);

        if(primeroU == NULL){
            primeroU = nuevaLocalidad;
            nuevaLocalidad->sig = primeroU;
        }
        else if(n<primeroU->nombre){
            struct Localidad *temp = primeroU;
            do{
                temp = temp->sig;
            }while(temp->sig!=primeroU);
            nuevaLocalidad->sig = primeroU;
            temp->sig = nuevaLocalidad;
            primeroU = nuevaLocalidad;
        }
        else{
            struct Localidad *actual = primeroU;
            struct Localidad *anterior = NULL;//este va a ir detras del actual
            do{
                anterior = actual;
                actual = actual->sig;
            }while((actual != primeroU)&&(n>actual->nombre));

            if(actual == primeroU){//Se inserta al final de la lista
                if(n<actual->nombre){
                    nuevaLocalidad->sig = primeroU;
                    primeroU->sig = nuevaLocalidad;
                    primeroU =nuevaLocalidad;
                }
                else{
                    anterior->sig = nuevaLocalidad;
                    nuevaLocalidad->sig = actual;
                }
            }
            else if(anterior == NULL){//al inicio
                nuevaLocalidad->sig = primeroU;
                primeroU = nuevaLocalidad;
            }
            else{
                anterior->sig = nuevaLocalidad;
                nuevaLocalidad->sig = actual;
            }
        }
    }
}

void insertarSector(string t,string n){
    if(primeroU == NULL){
        cout <<endl<<"No existe ninguna localidad.";
        return;
    }
    struct Localidad * existe = buscarLocalidad(n);
    if(existe == NULL){
        cout <<endl<< "No se encontro la localidad.";
    }
    else {
        struct Sector * existeS = buscarSector(t);
        if(existeS == NULL) {
            struct Sector *nodoSector = new Sector(t, 0);
            if (primeroS == NULL) {
                nodoSector->sig = primeroS;
                primeroS = nodoSector;
            }
            else {
                struct Sector *temp = primeroS;
                while (temp->sig != NULL) {
                    temp = temp->sig;
                }
                temp->sig = nodoSector;
            }
            struct subLocalidadSector *nodoSubSector = new subLocalidadSector();
            if (existe->enlaceSubLS == NULL) {
                existe->enlaceSubLS = nodoSubSector;
            }
            else {
                nodoSubSector->sig = existe->enlaceSubLS;
                existe->enlaceSubLS = nodoSubSector;
            }
            nodoSubSector->enlaceSector = nodoSector;
        }
        else{
            cout <<"EL SECTOR " << t << " YA EXISTE EN ESTA LOCALIDAD" << endl;
        }

    }
}

void insertarVivienda(int id,string n){
    if(primeroU == NULL){
        cout <<"NO EXISTE NINGUNA LOCALIDAD" << endl;
        return;
    }
    struct Localidad * existeL = buscarLocalidad(n);
    if(existeL == NULL){
        cout << "LA LOCALIDAD " << n << "NO EXISTE" << endl;
        return;
    }
    struct vivienda * existeV = buscarVivienda(id);
    if(existeV == NULL){
        struct vivienda * nodoVivienda = new vivienda(id,0);
        nodoVivienda->sig  = primeroV;
        primeroV = nodoVivienda;

        struct subLocalidadVivienda * nodoSubLV = new subLocalidadVivienda();
        if(existeL->enlaceSubLV == NULL){
            existeL->enlaceSubLV = nodoSubLV;
        }
        else{
            nodoSubLV->sig = existeL->enlaceSubLV;
            existeL->enlaceSubLV = nodoSubLV;
        }
        nodoSubLV->enlaceVivienda = nodoVivienda;
    }
    else{
        cout <<"ESTA VIVIENDA YA EXISTE" << endl;
    }
}

void insertarConsumo(int c,int id){
    if(primeroV == NULL){
        cout <<"NO EXISTE NINGUNA VIVIENDA" << endl;
        return;
    }
    struct vivienda * existe =  buscarVivienda(id);
    if(existe == NULL){
        cout <<"LA VIVIENDA NO EXISTE" << endl;
        return;
    }



}

//*************************************IMPRIMIR**********************************

void imprimirLocalidad(){
    if(primeroU == NULL){
        cout << "NO EXISTE NINGUNA LOCALIDAD" << endl;
        return;
    }
    struct Localidad  * temp = primeroU;
    do{
        cout <<"Nombre: "<< temp->nombre << endl;
        temp = temp->sig;
    }while(temp != primeroU);
}

void imprimirSector(string n){
    if(primeroU == NULL){
        cout <<"NO EXISTE NINGUNA LOCALIDAD" << endl;
        return;
    }
    struct Localidad * existe = buscarLocalidad(n);
    if(existe == NULL){
        cout << "ESTA LOCALIDAD NO EXISTE" << endl;
    }
    else{
        cout << "Nombre de la localidad: " << existe->nombre << endl;
        if(existe->enlaceSubLS == NULL){
            cout << "NO TIENE NINGUN SECTOR" << endl;
            return;
        }
        struct subLocalidadSector * temp = existe->enlaceSubLS;
        while(temp!= NULL){
            cout << "SECTOR: " << temp->enlaceSector->tipoSector << endl;
            temp = temp ->sig;
        }
    }
}

void imprimirVivienda(string n){
    if(primeroU == NULL){
        cout <<"NO EXISTE NINGUNA LOCALIDAD" << endl;
    }
    else{
        struct Localidad * existeL = buscarLocalidad(n);
        if(existeL == NULL){
            cout <<"ESTA LOCALIDAD NO EXISTE" << endl;
        }
        else{
            cout <<"NOMBRE DE LA LOCALIDAD: " << existeL->nombre << endl;
            if(existeL->enlaceSubLV == NULL){
                cout <<"ESTA LOCALIDAD NO TIENE VIVIENDAS" << endl;
            }
            else{
                struct subLocalidadVivienda * temp = existeL->enlaceSubLV;
                while(temp!=NULL){
                    cout << "VIVIENDA: " << temp->enlaceVivienda->ID << endl;
                    temp = temp->sig;
                }
            }
        }
    }
}


void cargarDatos(){
    insertarLocalidad("Florencia");
    insertarLocalidad("Santa Clara");
    insertarLocalidad("La Vega");
    insertarLocalidad("Cuestillas");
    imprimirLocalidad();
    insertarSector("Comercio","Florencia");
    insertarSector("Industria","Florencia");
    insertarSector("Transporte","Florencia");
    imprimirSector("Florencia");
    insertarVivienda(01,"Florencia");
    insertarVivienda(02, "Florencia");
    imprimirVivienda("Florencia");
}


int main(){
//Fecha de inicio: 10/03/2015
//Ultima modificacion: 14/03/2015
    cargarDatos();
    return 0;
}

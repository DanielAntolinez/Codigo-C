#include <iostream>
#include <limits.h>
using namespace std;

int const n=4;
int const m=5;
void LimpiezaMatrices(bool disponibilidad[n][m],int peso[n][m],int precios[n][m]);
void ImprimirDisponibilidad(bool disponibilidad[n][m]);
void cantidadContenedores(bool disponibilidad[n][m]);
void contenedoresporPuerto(string nombresPuertos[],int contenedoresPuerto[],int numeroPuertos);
void listaZonaEconomica(int precios[n][m],string marca[n][m]);
void listaZonaPremium(int precios[n][m], string marca[n][m]);
int nombreEmpresa(string marca[n][m],int precios[n][m]);
float promedioPeso(bool disponibilidad[n][m],int peso[n][m]);
int filaMayorCarga(int peso[n][m]);
int cantidadArticulo(string tipoArticulo[n][m]);
float promedioPesoPuerto(int peso[n][m],string puertoCarga[n][m]);
int MarcaMayorPeso(int peso[n][m],string marca[n][m]);
int MarcaMenorPeso(int peso[n][m],string marca[n][m]);

int main(){
    //variables
    int porcentaje=0;
    
    //numero de puertos
    int numeroPuertos=0;
    cout<<"Ingrese la cantidad de puertos a arribar "<<endl;
    cin>>numeroPuertos;
    string nombresPuertos[numeroPuertos];
    for(int i=0;i<numeroPuertos;i++){
        cout<<"Ingrese el nombre del puerto numero "<<i+1<<endl;
        cin>>nombresPuertos[i];
    }
    cout<<"Los puertos son los siguientes "<<endl;
    for(int i=0;i<numeroPuertos;i++){
        cout<<nombresPuertos[i]<<endl;
    }

    //matrices y vectores
    bool disponibilidad[n][m];
    string marca[n][m];
    string puertoCarga[n][m];
    int peso[n][m];
    string tipoArticulo[n][m];
    int precios[n][m];
    int recaudoPuerto[numeroPuertos];
    int contenedoresPuerto[numeroPuertos];

    LimpiezaMatrices(disponibilidad,peso,precios);

    //llenado de matrices y operaciones
    for (int x=0;x<numeroPuertos;x++){
        int numeroContenedores=0;
        cout<<"Ingrese el numero de contenedores para el puerto "<<nombresPuertos[x]<<endl;
        cin>>numeroContenedores;
        contenedoresPuerto[x]=numeroContenedores;
        for(int i=0;i<numeroContenedores;i++){
            bool bandera=0;
            while(bandera==0){
                int fila=0;
                int columna=0;
                cout<<"La disponibilidad es la siguiente "<<endl;
                ImprimirDisponibilidad(disponibilidad);
                cout<<"Ingrese la coordenada de la fila "<<endl;
                cin>>fila;
                cout<<"Ingrese la coordenada de la columna "<<endl;
                cin>>columna;
                if(disponibilidad[fila][columna]==1 && fila<4 && fila>=0 && columna<5 && columna>=0){
                    cout<<"Ingrese la marca del contenedor "<<endl;
                    cin>>marca[fila][columna];
                    cout<<"Ingrese el peso del contenedor "<<endl;
                    cin>>peso[fila][columna];
                    puertoCarga[fila][columna]=nombresPuertos[x];
                    cout<<"Ingrese el tipo de articulo donde (A) se refiere a alimentos, (B) se refiere a dispositivos electronicos y (C) se refiere a ropa y demas textiles "<<endl;
                    cin>>tipoArticulo[fila][columna];
                    disponibilidad[fila][columna]=0;
                    bandera=1;
                }else{
                    cout<<"La coordenada ingresada no existe o esta ocupada, intentelo nuevamente"<<endl;
                }
            }
        }
        int contador=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(disponibilidad[i][j]==0){
                    contador=contador+1;
                }
            }
        }
        porcentaje=(contador*100)/20;
        cout<<"EL porcentaje de ocupación actual del barco es del "<<porcentaje<<"%"<<endl;

        int acumulador=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(puertoCarga[i][j]==nombresPuertos[x]){
                    acumulador=acumulador+precios[i][j];
                }
            }
        }
        recaudoPuerto[x]=acumulador;
        cout<<"El valor del recaudo del puerto actual es "<<recaudoPuerto[x]<<"USD"<<endl;
    }
    cantidadContenedores(disponibilidad);
    contenedoresporPuerto(nombresPuertos,contenedoresPuerto,numeroPuertos);
    listaZonaEconomica(precios,marca);
    listaZonaPremium(precios,marca);
    nombreEmpresa(marca,precios);
    promedioPeso(disponibilidad,peso);
    filaMayorCarga(peso);
    cantidadArticulo(tipoArticulo);
    promedioPesoPuerto(peso,puertoCarga);
    MarcaMayorPeso(peso,marca);
    MarcaMenorPeso(peso,marca);
    return 0;
}
void LimpiezaMatrices(bool disponibilidad[n][m],int peso[n][m],int precios[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            disponibilidad[i][j]=1;
            peso[i][j]=0;
            if(i==0 && j<5 || i==3 && j<5 || j==0 && i<4 || j==4 && i<4){
                precios[i][j]=100;
            }else{
                precios[i][j]=300;
            }
        }
    }
}
void ImprimirDisponibilidad(bool disponibilidad[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<disponibilidad[i][j]<<" ";
        }
        cout<<endl;
    }
}
void cantidadContenedores(bool disponibilidad[n][m]){
    int contador=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(disponibilidad[i][j]==0){
                contador=contador+1;
            }
        }
    }
    cout<<"El numero de contenedores recogidos en total de todos los puertos es "<<contador<<endl;
}
void contenedoresporPuerto(string nombresPuertos[],int contenedoresPuerto[],int numeroPuertos){
    for(int i=0;i<numeroPuertos;i++){
        for(int j=0;j<numeroPuertos;j++){
            if(contenedoresPuerto[j]<contenedoresPuerto[i]){
                int aux=contenedoresPuerto[i];
                contenedoresPuerto[i]=contenedoresPuerto[j];
                contenedoresPuerto[j]=aux;
                string auxnom=nombresPuertos[i];
                nombresPuertos[i]=nombresPuertos[j];
                nombresPuertos[j]=auxnom;
            }
        }
    }
    for(int i=0;i<numeroPuertos;i++){
        cout<<nombresPuertos[i]<<"-->"<<contenedoresPuerto[i]<<endl;
    }
}
void listaZonaEconomica(int precios[n][m],string marca[n][m]){
    int contador=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(precios[i][j]==100 && marca[i][j]!=""){
                contador=contador+1;
            }
        }
    }
    string zonaEconomica[contador];
    for(int x=0;x<contador;x++){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(precios[i][j]==100 && marca[i][j]!=""){
                zonaEconomica[x]=marca[i][j];
                }
            }
        }
    }
    cout<<"La lista de marcas en las celdas economicas es "<<endl;
    for(int i=0;i<contador;i++){
        cout<<zonaEconomica[i]<<endl;
    }
}
void listaZonaPremium(int precios[n][m], string marca[n][m]){
    int contador=0;
        for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(precios[i][j]==300 && marca[i][j]!=""){
                contador=contador+1;
            }
        }
    }
    string zonaPremium[contador];
    for(int x=0;x<contador;x++){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(precios[i][j]==300 && marca[i][j]!=""){
                zonaPremium[x]=marca[i][j];
                }
            }
        }
    }
    cout<<"La lista de marcas en las celdas premium es "<<endl;
    for(int i=0;i<contador;i++){
        cout<<zonaPremium[i]<<endl;
    }
}
int nombreEmpresa(string marca[n][m],int precios[n][m]){
    int acumulador=0;
    int contadorEconomica=0;
    int contadorPremium=0;
    string marcaEmpresa="";
    cout<<"Ingrese el nombre de la empresa "<<endl;
    cin>>marcaEmpresa;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(marcaEmpresa==marca[i][j]){
                if(precios[i][j]==100){
                    acumulador=acumulador+precios[i][j];
                    contadorEconomica=contadorEconomica+1;
                }else if(precios[i][j]==300){
                    acumulador=acumulador+precios[i][j];
                    contadorPremium=contadorPremium+1;
                }
            }
        }
    }
    cout<<"La empresa "<<marcaEmpresa<<" tiene "<<contadorEconomica<<" contenedor(es) en la zona economica y "<<contadorPremium<<" contenedor(es) en la zona premium"<<endl;
    return acumulador,contadorPremium,contadorEconomica;
}
float promedioPeso(bool disponibilidad[n][m],int peso[n][m]){
    float promedio=0;
    int acumulador=0;
    int contador=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(disponibilidad[i][j]==0){
                contador=contador+1;
                acumulador=acumulador+peso[i][j];
            }
        }
    }
    promedio=acumulador/contador;
    cout<<"El promedio del peso de los contenedores es "<<promedio<<endl;
    return promedio;
}
int filaMayorCarga(int peso[n][m]){
    int mayor=0;
    int fila=0;
    int acumulador1=0;
    int acumulador2=0;
    int acumulador3=0;
    int acumulador4=0;
    for(int i=0;i<n;i++){
        int acumulador=0;
        for(int j=0;j<m;j++){
            if(i==0){
                acumulador1=acumulador1+peso[i][j];
            }else if(i==1){
                acumulador2=acumulador2+peso[i][j];
            }else if(i==2){
                acumulador3=acumulador3+peso[i][j];
            }else if(i==3){
                acumulador4=acumulador4+peso[i][j];
            }
        }
    }
    int pesoFila[4];
    for(int i=0;i<4;i++){
        if(i==0){
            pesoFila[i]=acumulador1;
        }else if(i==1){
            pesoFila[i]=acumulador2;
        }else if(i==2){
            pesoFila[i]=acumulador3;
        }else if(i==3){
            pesoFila[i]=acumulador4;
        }
    }
    for(int i=0;i<4;i++){
        if(pesoFila[i]>mayor){
            mayor=pesoFila[i];
            fila=i;
        }
    }
    cout<<"La fila numero "<<fila<<" tiene el mayor peso con "<<mayor<<" toneladas"<<endl;
    return mayor,fila;
}
int columnaMenorCarga(int peso[n][m]){
    int menor=0;
    int columna=0;
    int acumulador1=0;
    int acumulador2=0;
    int acumulador3=0;
    int acumulador4=0;
    int acumulador5=0;
    for(int i=0;i<n;i++){
        int acumulador=0;
        for(int j=0;j<m;j++){
            if(j==0){
                acumulador1=acumulador1+peso[i][j];
            }else if(j==1){
                acumulador2=acumulador2+peso[i][j];
            }else if(j==2){
                acumulador3=acumulador3+peso[i][j];
            }else if(j==3){
                acumulador4=acumulador4+peso[i][j];
            }else if(j==4){
                acumulador5=acumulador5+peso[i][j];
            }
        }
    }
    int pesoColumna[5];
    for(int i=0;i<5;i++){
        if(i==0){
            pesoColumna[i]=acumulador1;
        }else if(i==1){
            pesoColumna[i]=acumulador2;
        }else if(i==2){
            pesoColumna[i]=acumulador3;
        }else if(i==3){
            pesoColumna[i]=acumulador4;
        }else if(i==4){
            pesoColumna[i]=acumulador5;
        }
    }
    for(int i=0;i<5;i++){
        if(pesoColumna[i]<menor){
            menor=pesoColumna[i];
            columna=i;
        }
    }
    cout<<"La columna numero "<<columna<<" tiene el menor peso con "<<menor<<" toneladas"<<endl;
    return menor,columna;
}
int cantidadArticulo(string tipoArticulo[n][m]){
    int contador=0;
    string articulo="";
    cout<<"Ingrese el tipo de articulo dado que (A) son alimentos, (B) son dispositivos electronicos y (C) son ropa y demas textiles"<<endl;
    cin>>articulo;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(articulo==tipoArticulo[i][j]){
                contador=contador+1;
            }
        }
    }
    cout<<"Se encontraron "<<contador<<" contenedores del articulo "<<articulo<<endl;
    return contador;
}
float promedioPesoPuerto(int peso[n][m],string puertoCarga[n][m]){
    float promedio=0;
    int contador=0;
    int acumulador=0;
    string nombrePuerto="";
    cout<<"Ingrese el nombre del puerto a buscar "<<endl;
    cin>>nombrePuerto;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(nombrePuerto==puertoCarga[i][j]){
                contador=contador+1;
                acumulador=acumulador+peso[i][j];
            }
        }
    }
    promedio=acumulador/contador;
    cout<<"El promedio de peso generado en el puerto "<<nombrePuerto<<" es "<<promedio<<" toneladas"<<endl;
    return promedio;
}
int MarcaMayorPeso(int peso[n][m],string marca[n][m]){
    int mayor=0;
    string Empresa="";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(peso[i][j]>mayor){
                mayor=peso[i][j];
                Empresa=marca[i][j];
            }
        }
    }
    cout<<"La empresa "<<Empresa<<" registra el contenedor de mayor peso con "<<mayor<<" toneladas"<<endl;
    return mayor;
}
int MarcaMenorPeso(int peso[n][m],string marca[n][m]){
    int menor=0;
    string Empresa="";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(peso[i][j]<menor){
                menor=peso[i][j];
                Empresa=marca[i][j];
            }
        }
    }
    cout<<"La empresa "<<Empresa<<" registra el contenedor de menor peso con "<<menor<<" toneladas"<<endl;
    return menor;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define TAM 256000

typedef struct {
	int vector[TAM];
	int ultimo;
} monticulo;

void hundir(monticulo *m, int i){
	int HijoIzq, HijoDer, aux, j;
		
	do{
		HijoIzq = 2*i+1;
		HijoDer = 2*i+2;
		j = i;
		
		if(HijoDer <= m->ultimo && m->vector[HijoDer] < m->vector[i]){
			i = HijoDer;
		}
		
		if(HijoIzq <= m->ultimo && m->vector[HijoIzq] < m->vector[i]){
			i = HijoIzq;
		}
		
		aux = m->vector[j];
		m->vector[j] = m->vector[i];
		m->vector[i] = aux;
		
	}while(j!=i);
}

void crearMonticulo(int v[], int n, monticulo *m){
	int i;
	
	for (i=0;i<n;i++){
		m->vector[i] = v[i];
	}
	
	m->ultimo = n-1;
	
	for (i=(n-1)/2;i>=0;i--){
		hundir(m, i);
	}
}

int consultarMenor(monticulo *m){
	return m->vector[0];
}

int esMonticuloVacio(monticulo *m){
	return m->ultimo==(-1);
}

void quitarMenor(monticulo *m){	
	if(esMonticuloVacio(m)){
		printf("Montículo vacío");
	}else {
		m->vector[0] = m->vector[m->ultimo];
		m->ultimo--;
		if(m->ultimo >= 0){
				hundir(m, 0);
		}
	}
}

void ordMonticulo(int v[], int n){
	monticulo m;
	int i;
	
	crearMonticulo(v, n, &m);
	for(i=0;i<n;i++){
		v[i] = consultarMenor(&m);
		quitarMenor(&m);
	}
}


void inicializar_semilla() {
	srand(time(NULL));
}

/* se generan números pseudoaleatorio entre -n y +n */
void aleatorio(int v [], int n) {
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
}

void ascendente(int v[], int n) {
	int i;
	for(i=0; i < n; i++)
		v[i] = i;
}

void descendente(int v[], int n) {
	int i;
	for(i=n; i > 0 ; i--)
		v[n-i] = i-1;
}

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void listar_vector(int v[], int n) {
	int a;
	for(a = 0; a < n; a++) printf("%d ", v[a]);
		printf("\n");
}

void mostrar_monticulo(monticulo m){
	printf("--Vector del montículo: "), listar_vector(m.vector, m.ultimo+1);
	printf("--Última posición: %d\n", m.ultimo);
}


void test1(){
	int v[10];
	monticulo m;
	printf("\nInicializando vector...\n"), aleatorio(v, 10);
	printf("\nVector: "), listar_vector(v, 10);
	printf("\nCreando montículo...\n"),	crearMonticulo(v, 10, &m);
	printf("\nMontículo:\n"), mostrar_monticulo(m);
	printf("\nMenor elemento: %d\n", consultarMenor(&m));
	printf("\nEliminando el menor elemento...\n"), quitarMenor(&m);
	printf("\nMontículo tras la eliminación:\n"), mostrar_monticulo(m);
	printf("\n");
}

void test2(void orden()){
	int v[10];

	printf("Vector original: ");
	orden(v, 10);
	listar_vector(v, 10);
	
	printf("Vector ordenado: ");
	ordMonticulo(v, 10);
	listar_vector(v, 10);
}

//Cotas de crearMonticulo de/as/al su/es/so
double cota_calsu(int n) {return pow(n, 0.912);}
double cota_cales(int n) {return pow(n, 1.012);}
double cota_calso(int n) {return pow(n, 1.112);}

//Cotas de ordMonticulo de/as/al su/es/so5
double cota_odesu(int n) {return pow(n, 1.05);}
double cota_odees(int n) {return pow(n, 1.085);}
double cota_odeso(int n) {return pow(n, 1.15);}

double cota_oassu(int n) {return pow(n, 1.065);}
double cota_oases(int n) {return pow(n, 1.095);}
double cota_oasso(int n) {return pow(n, 1.125);}

double cota_oalsu(int n) {return pow(n, 1.06);}
double cota_oales(int n) {return pow(n, 1.11);}
double cota_oalso(int n) {return pow(n, 1.16);}

void mostrar_tabla_crearMonticulo() {
	double t1, t2, tiempo; //Variables de tiempo
	monticulo m;
	int vector[TAM];
	int capacidad;
	int k;

	printf("   (n)\t\tt(n)\t t(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n");
	for (capacidad = 2000; capacidad <= TAM; capacidad*=2) {
		aleatorio(vector, capacidad);	
		t1 = microsegundos();
		crearMonticulo(vector, capacidad, &m);
		t2 = microsegundos();
		tiempo = t2 - t1;
		if (tiempo < 500) {
			printf("*");						
			t1 = microsegundos();
			for (k = 0; k < 1000; k++) {
				crearMonticulo(vector, capacidad, &m);
			}
			t2 = microsegundos();
			tiempo= (t2-t1)/1000;
		}else printf(" ");
	 	printf("%7d    ",capacidad);
	 	printf("%12.3f   ",tiempo);
	 	printf("%.10f   ",tiempo/cota_calsu(capacidad));
	 	printf("%.10f   ",tiempo/cota_cales(capacidad));
	 	printf("%.10f\n",tiempo/cota_calso(capacidad));
	}
	printf("\t\t\t Subestimada\tAjustada\tSobreestimada\n\n");
}

void mostrar_tabla (void algoritmo(),void orden(),
					double cota1(),double cota2(),double cota3()) {
	double t1, t2, taux1, taux2, tiempo; //Variables de tiempo
	int vector[TAM];
	int capacidad;
	int k;

	printf("   (n)\t\tt(n)\t t(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n");
	for (capacidad = 2000; capacidad <= TAM; capacidad*=2) {
		orden(vector, capacidad);	
		t1 = microsegundos();
		algoritmo(vector, capacidad);
		t2 = microsegundos();
		tiempo = t2 - t1;
		if (tiempo < 500) {
			printf("*");
			
			taux1 = microsegundos();
			for (k = 0; k < 1000; k++) {
				orden(vector, capacidad);
			}
			taux2 = microsegundos();
						
			t1 = microsegundos();
			for (k = 0; k < 1000; k++) {
				orden(vector, capacidad);
				algoritmo(vector, capacidad);
			}
			t2 = microsegundos();
			tiempo= (t2-t1-(taux2-taux1))/1000;
		}else printf(" ");
	 	printf("%7d    ",capacidad);
	 	printf("%12.3f   ",tiempo);
	 	printf("%.10f   ",tiempo/cota1(capacidad));
	 	printf("%.10f   ",tiempo/cota2(capacidad));
	 	printf("%.10f\n",tiempo/cota3(capacidad));
	}
}

int main(){
	inicializar_semilla();	
	
	//Tests
	printf("Test de funcionamiento:\n"),test1();
	printf("Test de ordenación(vector ascendente):\n"),test2(ascendente);
	printf("Test de ordenación(vector aleatorio):\n"),test2(aleatorio);
	printf("Test de ordenación(vector descendente):\n"),test2(descendente);
	
	//Tabla de crearMonticulo
	printf("\nCrear montículo\n\n");
	printf("Cota Subestimada:  f(n)=n^0.912\n");
	printf("Cota Ajustada:     g(n)=n^1.012\n");
	printf("Cota Sobrestimada: h(n)=n^1.112\n\n");
	mostrar_tabla_crearMonticulo();
	
	//Tablas de ordMonticulo
	printf("\nOrdenacion por Montículos con inicializacion descendente\n\n");
	printf("Cota Subestimada:  f(n)=n^1.05\n");
	printf("Cota Ajustada:     g(n)=n^1.085\n");
	printf("Cota Sobrestimada: h(n)=n^1.15\n\n");
	mostrar_tabla(ordMonticulo,descendente,cota_odesu,cota_odees,cota_odeso);
	
	printf("\nOrdenacion por Montículos con inicializacion ascendente\n\n");
	printf("Cota Subestimada:  f(n)=n^1.065\n");
	printf("Cota Ajustada:     g(n)=n^1.095\n");
	printf("Cota Sobrestimada: h(n)=n^1.125\n\n");
	mostrar_tabla(ordMonticulo,ascendente,cota_oassu,cota_oases,cota_oasso);
	
	printf("\nOrdenacion por Montículos con inicializacion aleatoria\n\n");
	printf("Cota Subestimada:  f(n)=n^1.06\n");
	printf("Cota Ajustada:     g(n)=n^1.11\n");
	printf("Cota Sobrestimada: h(n)=n^1.16\n\n");
	mostrar_tabla(ordMonticulo,aleatorio,cota_oalsu,cota_oales,cota_oalso);
}

#ifndef ARCH_EST_EMP_H_INCLUDED
#define ARCH_EST_EMP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{

 long int dni;
 char apellido[50];
 char nombre[50];
 double sueldo;

}tEmpleado;

typedef struct{

 long int dni;
 char apellido[50];
 char nombre[50];
 float promedio;

}tEstudiante;

int abrir_archivo(FILE** pf,const char *path,const char*modo , int mostrarError);

/**ordenados alf apellido nombre dni */
/** actualizar sueldo un %7,28 si promedio > 7 */
void crearLotePruebaEmpleados();
void crearLotePruebaEstudiantes();

void mostrarRegistroEmp(const tEmpleado *emp);
void mostrarRegistroEst(const tEstudiante *est);

void mostrarArchivoEmpleados(FILE *pem);
void mostrarArchivoEstudiantes(FILE *pes);

void actualizarSueldo(FILE *pem, FILE *pes);
int comparar(const tEmpleado *emp, const tEstudiante *clave);

#endif // ARCH_EST_EMP_H_INCLUDED

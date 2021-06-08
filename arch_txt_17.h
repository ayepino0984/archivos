#ifndef ARCH_TXT_17_H_INCLUDED
#define ARCH_TXT_17_H_INCLUDED

#include <string.h>
#include "arch_est_emp.h"

void trozarCamposLongFijaEst( tEstudiante *alu, char *cad);
void trozarCamposLongFijaEmp( tEmpleado *emp, char *cad);

void trozarCamposLongVarEmp(tEmpleado *emp, char *cadEmp);
void trozarCamposLongVarEst(tEstudiante *est, char *cadEst);

void actualizarSueldoEnTxt(FILE *pes, FILE *pem, FILE *pemN);
void actualizarSueldoEnTxtVar(FILE *pes,FILE * pem, FILE *pemN);

void mostrarEmpleado( const tEmpleado *empl);
void mostrarArchivoTxt(FILE *p);

int crearArchEstTxtLV(char *nombreArchOrigen, char*nombreArchDest);
int crearArchEmpTxtLV(char *nombreArchOrigen, char*nombreArchDest);
int crearArchEstTxtLF(char *nombArchOrig, char* nombArchDest);
int crearArchEmpTxtLF(char *nombArchOrig, char* nombArchDest);

#endif // ARCH_TXT_17_H_INCLUDED

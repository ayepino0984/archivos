#include "main.h"

#define ARG_NOM_ARCH_BIN_EST    1
#define ARG_NOM_ARCH_BIN_EMP    2
#define ARG_NOM_ARCH_TXTF_EST   3
#define ARG_NOM_ARCH_TXTF_EMP   4
#define ARG_NOM_ARCH_TXTV_EST   5
#define ARG_NOM_ARCH_TXTV_EMP   6
#define ARG_NOM_ARCH_TXT_NEMP   7
#define ARG_NOM_ARCH_TXTV_NEMP   8

int main( int argc, char* argv[])
{
    if(argc != 9)
    {
        printf("Error invocando argumentos main\n");
        return ERR_INV_ARG;
    }
/**----------- EJERCICIO 13--------------**/
/*
    crearLotePruebaEmpleados();
    crearLotePruebaEstudiantes();

  FILE *pem,*pes;

    if( !abrir_archivo(&pem,"empleados.dat","rb"))
    {
        fclose(pem);
        return -1;
    }
    mostrarArchivoEmpleados(pem);
    fclose(pem);

    if(!abrir_archivo(&pes,"estudiantes.dat","rb"))
    {
        return -1;
        fclose(pes);
    }
    mostrarArchivoEstudiantes(pes);
    fclose(pes);


    if(!abrir_archivo(&pes,"estudiantes.dat","rb")) //LEE SU PROMEDIO
    { return 1; }
    if(!abrir_archivo(&pem,"empleados.dat","r+b")) //LEE y modifica si su prom > 7
    {return 1;    }

    actualizarSueldo(pem,pes);
    printf("\n\n");
    mostrarArchivoEmpleados(pem);

    fclose(pem);
    fclose(pes);
*/
/***------------ FIN EJERCICIO 13---------- ***/
/***-------------EJERCICIO 17 txt ---------****/

    FILE *pes, *pem, *pemN;
    tEstudiante alu;
    tEmpleado empl;
    char cad[TAM_LINEA],cad1[TAM_LINEA];

    if(!abrir_archivo(&pem,argv[ARG_NOM_ARCH_TXTV_EMP],"rt",1))
        exit(1);
    if(!abrir_archivo(&pes,argv[ARG_NOM_ARCH_TXTV_EST],"rt",1))
    {
        exit(1);
        fclose(pem);
    }
    if(!abrir_archivo(&pemN,argv[ARG_NOM_ARCH_TXTV_NEMP],"wt",1))
    {
        exit(1);
        fclose(pes);
        fclose(pem);
    }
         /*
          while(fgets(cad, sizeof(cad),pes))
         {
             trozarCamposLongFijaEst(&alu,cad);
             mostrarRegistroEst(&alu);
         }
            printf("\n");
          while(fgets(cad1, sizeof(cad1),pem))
         {
             trozarCamposLongFijaEmp(&empl,cad1);
             mostrarEmpleado(&empl);
         }
            */
        actualizarSueldoEnTxtVar(pes,pem,pemN);

        fclose(pem);
        fclose(pes);
        fclose(pemN);

    //remove(argv[ARG_NOM_ARCH_TXTV_EMP]);
    //rename(argv[ARG_NOM_ARCH_TXTV_NEMP],"empleados.txt");

/***------------ FIN EJERCICIO 17---------- ***/
    return 0;
}

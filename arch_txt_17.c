#include "arch_txt_17.h"
#include "main.h"

#define TAM_DNI 8
#define TAM_APE 49
#define TAM_NOM 49
#define TAM_SUELDO 8
#define TAM_PROM 9
#define TAM_LEST 115
#define TAM_LEMP 114

void mostrarArchivoTxt(FILE *p)
{
    char cad[1000];
    while(fgets(cad,sizeof(cad),p))
    {
        printf("%s\n",cad);
    }
}

void mostrarEmpleado( const tEmpleado *empl)
{
    printf( "%ld %-s %-s %.2f\n",
            empl->dni,
            empl->apellido,
            empl->nombre,
            empl->sueldo);
}

void trozarCamposLongFijaEst(tEstudiante *alu, char *cad)
{
    char* aux = cad + TAM_LEST; //

    *aux = '\0'; //APUNTA AL FINAL COLOCO FIN DE CADENA

    aux-= TAM_PROM;
    sscanf(aux,"%f",&alu->promedio);
    *aux='\0';

    aux-= TAM_NOM;
    strcpy(alu->nombre,aux);
    *aux='\0';

    aux-= TAM_APE;
    strcpy(alu->apellido,aux);
    *aux='\0';

    aux-= TAM_DNI;
    sscanf(cad,"%ld",&alu->dni);
    *aux='\0';
}

void trozarCamposLongFijaEmp( tEmpleado *emp, char *cad)
{
    char *aux = cad + TAM_LEMP;
    *aux ='\0';

    aux -= TAM_SUELDO;
    sscanf(aux,"%lf", &emp->sueldo);
    *aux='\0';

    aux -= TAM_NOM;
    strcpy(emp->nombre,aux);
    *aux='\0';

    aux -= TAM_APE;
    strcpy(emp->apellido,aux);
    *aux='\0';

    aux -= TAM_DNI;
    sscanf(aux, "%ld",&emp->dni);
    *aux='\0';
}
void actualizarSueldoEnTxt(FILE *pes,FILE * pem, FILE *pemN)
{
    char cadEst[500];
    char cadEmp[500];
    int rdo; //
    tEmpleado emp;
    tEstudiante est;
    rewind(pem);
    rewind(pemN);

    fgets(cadEst,sizeof(cadEst),pes);

    fgets(cadEmp,sizeof(cadEmp),pem);

    while(!feof(pem) && !feof(pes))
    {
        trozarCamposLongFijaEmp(&emp,cadEmp);
        trozarCamposLongFijaEst(&est,cadEst);

        rdo = comparar(&emp,&est);

            if(rdo == 0)
            {
                if(est.promedio > 7)
                {
                    emp.sueldo += ((emp.sueldo*7.28)/100);
                }
            }

        ///Escribo el nuevo archivo de empleados
        fprintf(pemN,
                "%08ld%-*s%-*s%f\n",
                emp.dni,
                (int)sizeof(emp.apellido)-1,
                emp.apellido,
                (int)sizeof(emp.nombre)-1,
                emp.nombre,
                emp.sueldo);

        fgets(cadEmp,sizeof(cadEmp),pem);

        fgets(cadEst,sizeof(cadEst),pes);
    }
}

void actualizarSueldoEnTxtVar(FILE *pes,FILE * pem, FILE *pemN)
{
    char cadEst[500];
    char cadEmp[500];
    int rdo; //
    tEmpleado emp;
    tEstudiante est;
    rewind(pem);
    rewind(pemN);

    fgets(cadEst,sizeof(cadEst),pes);

    fgets(cadEmp,sizeof(cadEmp),pem);

    while(!feof(pem) && !feof(pes))
    {
        trozarCamposLongVarEmp(&emp,cadEmp);
        trozarCamposLongVarEst(&est,cadEst);

        rdo = comparar(&emp,&est);

            if(rdo == 0)
            {
                if(est.promedio > 7)
                {
                    emp.sueldo += ((emp.sueldo*7.28)/100);
                }
            }

        ///Escribo el nuevo archivo de empleados
        fprintf(pemN,
                "%ld|%s|%s|%.2f\n",
                emp.dni,
                emp.apellido,
                emp.nombre,
                emp.sueldo);

        fgets(cadEmp,sizeof(cadEmp),pem);

        fgets(cadEst,sizeof(cadEst),pes);
    }
}

void trozarCamposLongVarEmp(tEmpleado *emp, char *cadEmp)
{
    char *aux = strchr(cadEmp,'\n');

    *aux = '\0';

    aux = strrchr(cadEmp,'|');
    sscanf(aux + 1, "%lf", &emp->sueldo);
    *aux = '\0';

    aux= strrchr(cadEmp,'|');
    strcpy(emp->nombre, aux + 1);
    *aux = '\0';

    aux= strrchr(cadEmp,'|');
    strcpy(emp->apellido, aux + 1);
    *aux = '\0';

    sscanf(cadEmp,"%ld",&emp->dni);
}
void trozarCamposLongVarEst(tEstudiante *est, char *cadEst)
{
    char *aux = strchr(cadEst,'\n');

    *aux = '\0';

    aux = strrchr(cadEst,'|');
    sscanf(aux + 1, "%f", &est->promedio);
    *aux = '\0';

    aux= strrchr(cadEst,'|');
    strcpy(est->nombre, aux + 1);
    *aux = '\0';

    aux= strrchr(cadEst,'|');
    strcpy(est->apellido, aux + 1);
    *aux = '\0';

    sscanf(cadEst,"%ld",&est->dni);
}

int crearArchEmpTxtLV(char *nombreArchOrigen, char*nombreArchDest)
{
    tEmpleado emp;
    FILE *fpBin,
         *fpTxtLV;

    fpBin= fopen(nombreArchOrigen,"rb");
    if(!fpBin)
        return ERR_ARCH;

    fpTxtLV= fopen(nombreArchDest,"wt");
    if(!fpTxtLV)
        {   fclose(fpBin);
            return ERR_ARCH;
        }

    fread(&emp,sizeof(tEmpleado),1,fpBin);
    while(!feof(fpBin))
    {
        fprintf(fpTxtLV,
                "%ld|%s|%s|%.2f\n",
                emp.dni,
                emp.apellido,
                emp.nombre,
                emp.sueldo);
        fread(&emp,sizeof(tEmpleado),1,fpBin);
    }

    fclose(fpBin);
    fclose(fpTxtLV);
    return TODO_OK;
}

int crearArchEstTxtLV(char *nombreArchOrigen, char*nombreArchDest)
{
    tEstudiante est;
    FILE *fpBin,
         *fpTxtLV;

    fpBin= fopen(nombreArchOrigen,"rb");
    if(!fpBin)
        return ERR_ARCH;

    fpTxtLV= fopen(nombreArchDest,"wt");
    if(!fpTxtLV)
        {   fclose(fpBin);
            return ERR_ARCH;
        }

    fread(&est,sizeof(tEstudiante),1,fpBin);
    while(!feof(fpBin))
    {
        fprintf(fpTxtLV,
                "%ld|%s|%s|%.2f\n",
                est.dni,
                est.apellido,
                est.nombre,
                est.promedio);
        fread(&est,sizeof(tEstudiante),1,fpBin);
    }

    fclose(fpBin);
    fclose(fpTxtLV);
    return TODO_OK;
}

int crearArchEstTxtLF(char *nombArchOrig, char* nombArchDest)
{
    tEstudiante alu;
    FILE *fpBin,
         *fpTxtLF;

    fpBin = fopen(nombArchOrig,"rb");
    if(!fpBin)
        return ERR_ARCH;
    fpTxtLF = fopen(nombArchDest,"wt");
    if(!fpTxtLF)
    {
        fclose(fpBin);
        return ERR_ARCH;
    }

    fread(&alu,sizeof(tEstudiante),1,fpBin);
    while(!feof(fpBin))
    {
        fprintf(fpTxtLF,
                "%08ld%-*s%-*s%.2f\n",
                alu.dni,
                (int)sizeof(alu.apellido)-1,
                alu.apellido,
                (int)sizeof(alu.nombre)-1,
                alu.nombre,
                alu.promedio);

        fread(&alu,sizeof(tEstudiante),1,fpBin);
    }

    fclose(fpBin);
    fclose(fpTxtLF);
    return TODO_OK;
}


int crearArchEmpTxtLF(char *nombArchOrig, char* nombArchDest)
{
    tEmpleado empl;
    FILE *fpBin,
         *fpTxtLF;

    fpBin = fopen(nombArchOrig,"rb");
    if(!fpBin)
        return ERR_ARCH;
    fpTxtLF = fopen(nombArchDest,"wt");
    if(!fpTxtLF)
    {
        fclose(fpBin);
        return ERR_ARCH;
    }

    fread(&empl,sizeof(tEmpleado),1,fpBin);
    while(!feof(fpBin))
    {
        fprintf(fpTxtLF,
                "%08ld%-*s%-*s%.2f\n",
                empl.dni,
                (int)sizeof(empl.apellido)-1,
                empl.apellido,
                (int)sizeof(empl.nombre)-1,
                empl.nombre,
                empl.sueldo);

        fread(&empl,sizeof(tEmpleado),1,fpBin);
    }

    fclose(fpBin);
    fclose(fpTxtLF);
    return TODO_OK;
}


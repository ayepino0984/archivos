#include "arch_est_emp.h"

int abrir_archivo(FILE** pf,const char *path,const char*modo, int mostrarError)
{
   *pf= fopen(path,modo);
    if(*pf == NULL)
    {
        if(mostrarError == 1)
        {
            fprintf(stderr,
                    "Error abriendo\"%s\"en modo\"%s\".",
                    path,
                    modo);
        }
        return 0;
    }
    return 1;
}

void mostrarRegistroEmp(const tEmpleado *emp)
{
    if(!emp)
    {
        printf(" DNI        APELLIDO        NOMBRE      SUELDO    \n");
        printf(" -------    -----------     ---------   --------  \n");
    }

    printf("%08ld %-*s %-*s %.2f\n",
           emp->dni,
           (int)sizeof(emp->apellido)-1,
           emp->apellido,
           (int)sizeof(emp->nombre)-1,
           emp->nombre,
           emp->sueldo);
}
void mostrarRegistroEst(const tEstudiante *est)
{
    if(!est)
    {
        printf(" DNI        APELLIDO        NOMBRE      PROMEDIO   \n");
        printf(" -------    -----------     ---------   --------  \n");
    }

    printf("%08ld %-*s %-*s %.2f\n",
           est->dni,
           (int)sizeof(est->apellido)-1,
           est->apellido,
           (int)sizeof(est->nombre)-1,
           est->nombre,
           est->promedio);
}

void mostrarArchivoEmpleados(FILE *pem)
{
    tEmpleado empleado;

    fseek(pem,0L,SEEK_SET);
    fread(&empleado,sizeof(tEmpleado),1,pem);
    while(!feof(pem))
    {
        mostrarRegistroEmp(&empleado);
        fread(&empleado,sizeof(tEmpleado),1,pem);
    }
}

void mostrarArchivoEstudiantes(FILE *pes)
{
    tEstudiante est;

    fseek(pes,0L,SEEK_SET);
    fread(&est,sizeof(tEstudiante),1,pes);
    while(!feof(pes))
    {
        mostrarRegistroEst(&est);
        fread(&est,sizeof(tEstudiante),1,pes);
    }
}

void actualizarSueldo(FILE *pem, FILE *pes)
{
    int rdo; /** COMPARA si emp>alu rdo>0,
    sino (OSEA emp<alu) rdo<0  o son ==*/
    tEmpleado emp;
    tEstudiante alu;
    rewind(pem);
    rewind(pes); ///vuelve al inicio los punteros a los archivos

    fread(&emp,sizeof(tEmpleado),1,pem); /**LEE los archivos en paralelo*/
    fread(&alu,sizeof(tEstudiante),1,pes);
    while(!feof(pes) && !feof(pem))
    {
        if((rdo=comparar(&emp,&alu))>=0)
        {
            if(rdo==0)
            {
                if(alu.promedio > 7)
                {
                    emp.sueldo+= ((emp.sueldo*7.28)/100);
                    fseek(pem,(long int)-sizeof(tEmpleado),SEEK_CUR);
                    fwrite(&emp,sizeof(tEmpleado),1,pem);
                    fseek(pem,0L,SEEK_CUR);
                }
                fread(&emp,sizeof(tEmpleado),1,pem);
                fread(&alu,sizeof(tEstudiante),1,pes);
            }else
            fread(&alu,sizeof(tEstudiante),1,pes);
        }else
        fread(&emp,sizeof(tEmpleado),1,pem);
    }
}
/** Compara si son la misma persona */
int comparar(const tEmpleado *emp, const tEstudiante *clave)
{
    int rdo;
    rdo= strcmpi(emp->apellido,clave->apellido);
    if(rdo == 0)
    {   rdo=strcmpi(emp->nombre,clave->nombre);
        if(rdo == 0)
            return emp->dni - clave->dni;
    }
    return rdo;
}

/**LOTE DE PRUEBA se crean e invocan una sola vez**/
void crearLotePruebaEmpleados()
{
    tEmpleado vecEmpl[]=
    {
        {11111111, "Abigail","Amata", 11111.11},
        {22222222, "Bastian","Barredo",22222.22},
        {33333333, "Ciraudo","Camila",33333.33},
        {44444444, "Daiana","Damico",44444.444},
        {55555555, "Espinosa","Ayelen",55555.5},
        {66666666, "Fiore","Felipa",6000.0},
        {88888887, "Hugh","Horacio",77777.7},
        {88888888, "Hugh","Horacio",8000.8},
        {99999999, "Irala","Ismael",9900.9},
        {10000000, "Jonas","Javier",10500.0},
    };
    FILE *pem;
    if(!abrir_archivo(&pem,"empleados.dat","wb",1))
        exit(1);
    fwrite(vecEmpl,sizeof(vecEmpl),1,pem);
    fclose(pem);
}
void crearLotePruebaEstudiantes()
{
    tEstudiante vecEst[]=
    {
        {11111111, "Abigail","Amata", 6.5},
        {22223332, "Bernardo","Bardo",5.6},
        {33333333, "Ciraudo","Camila",8.5},
        {44444444, "Daiana","Diaz",6.0},
        {55555566, "Espinosa","Ayelen",5.9},
        {66666666, "Fiore","Felipa",5.8},
        {77777776, "Gil","Gisela",6.7},
        {88888888, "Hugh","Horacio",6.8},
        {99999999, "Irala","Ismael",9.9},
        {10000000, "Jonas","Javier",8.0},
    };
    FILE *pes;
    if(!abrir_archivo(&pes,"estudiantes.dat","wb",1))
        exit(1);
    fwrite(vecEst,sizeof(vecEst),1,pes);
    fclose(pes);
}

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct trans
{
    int len;
    char datos[2000];
};

void proceso (char *aci, struct trans *tx_in, struct trans *tx_out,
struct trans *tx_sa)
{
    char nombre[21];
    char genero[21];
    char pais[21];
    char anio[5];
    char stock[21];
    char precio[6];

    memset(nombre, 0 , sizeof nombre);
    memset(genero, 0 , sizeof genero);
    memset(pais, 0, sizeof pais);
    memset(anio, 0 , sizeof anio);
    memset(stock, 0, sizeof stock);
    memset(precio, 0, sizeof precio);

    sscanf(tx_in->datos,"%20c%20c%20c%4c%20c%5c", nombre, genero, 
    pais, anio, stock, precio);

    printf( "Llego desde el formulario: %s\n", tx_in->datos);

printf("Nombre:  %s\n", nombre);
printf("Genero:  %s\n", genero);
printf("Pais:  %s\n", pais);
printf("Anio:  %s\n", anio);
printf("Stock:  %s\n", stock); //ACAAAAA!!!! 


//    tx_out->len = sprintf(tx_out->datos,"%s%s%s%s%s%s", nombre, genero,
  //  pais, anio, stock, precio);


// Comunicacion con el Demonio 

    int qid,pid;

        struct msgbuf {
                long mtype;
                struct {
                        int pid;
                        char dat[2000];
                } texto;
        } mensaje, respuesta;

        qid = msgget(666666, 0666);
        pid = getpid();

   // Limpiamos la estructura del mensaje
        memset(&mensaje, 0, sizeof mensaje);

  // guardamos en la estructura mensaje lo que se quiere enviar 
        //al demonio
        sprintf(mensaje.texto.dat, "%6s%s%s%s%s%s%s", "ingpel" , 
nombre,
        genero, pais, anio, stock, precio);

        mensaje.mtype = 1;
        mensaje.texto.pid = pid;
        msgsnd(qid, &mensaje, strlen(mensaje.texto.dat)+4,0);

        // Limpiamos la estructura de respuesta
        memset(&respuesta, 0, sizeof respuesta);

        msgrcv(qid, &respuesta, 2000, pid, 0);

        printf("\n\n -------- RESPUESTA --------\n\n");

        printf("respuesta demonio: %s\n\n", respuesta.texto.dat);


// en tx out se debe dejar la tx de salida
tx_out->len=sprintf(tx_out->datos,"%s", respuesta.texto.dat);

printf("El mensaje que sale del formulario es: %s\n", tx_out->datos);
}

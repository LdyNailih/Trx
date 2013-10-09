#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct trans
{
int len;
char datos[2000];
};

void proceso (char *aci , struct trans *tx_in, struct trans *tx_out, struct trans *tx_sa)
{
	char rut[9];
	char nombre[21];
	char apellido[21];
	char mail[51];
	char clave[21];

	memset(rut, 0 , sizeof rut);
	memset(nombre, 0 , sizeof nombre);
	memset(apellido, 0, sizeof apellido);
	memset(mail, 0 , sizeof mail);
	memset(clave, 0, sizeof clave);

	sscanf(tx_in->datos,"%8c%20c%20c%50c%20c", rut, nombre, apellido, mail, clave);
	tx_out->len = sprintf(tx_out->datos,"%s%s%s%s%s",rut,nombre, apellido, mail , clave );


// Comunicacion con el demonio


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

        // guardamos en la estructura mensaje lo que se quiere enviar al demonio
        sprintf(mensaje.texto.dat, "%6s%s", "modusu", rut,nombre, apellido, mail , clave );

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

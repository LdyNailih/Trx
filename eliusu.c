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

void proceso (char *aci, struct trans *tx_in, struct trans *tx_out, struct trans *tx_sa)
{
	char rut[8];
	memset(rut, 0 , sizeof rut);
	
	sscanf(tx_in->datos,"%8c", rut);
	tx_out->len = sprintf(tx_out->datos,"%s",rut);

	
	// Comunicacion con el demonio


int qid,pid;

	struct msgbuf {
		long mtype;
		struct {
			int pid;
			char dat[2000];
		} texto;
	} mensaje, respuesta;

	qid = msgget(5942016, 0666);
	pid = getpid();

	// Limpiamos la estructura del mensaje
	memset(&mensaje, 0, sizeof mensaje);

	// guardamos en la estructura mensaje lo que se quiere enviar al demonio
	sprintf(mensaje.texto.dat, "%s", "eliusu", rut);

	mensaje.mtype = 1;
	mensaje.texto.pid = pid;
	msgsnd(qid, &mensaje, strlen(mensaje.texto.dat)+4,0);

	// Limpiamos la estructura de respuesta
	memset(&respuesta, 0, sizeof respuesta);

	msgrcv(qid, &respuesta, 2000, pid, 0);
	
	printf("\n\n -------- RESPUESTA --------\n\n");

	printf("respuesta demonio: %s\n\n", respuesta.texto.dat);

	// en tx out se debe dejar la tx se salida
	tx_out->len= sprintf (tx_out->datos,"%s", respuesta.texto.dat);


}




	

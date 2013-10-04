#include <stdio.h>
#include <string.h>

struct trans
{
	int len;
	char datos[2000];
};

void proceso (char *aci, struct trans *tx_in, struct trans *tx_out, struct trans *tx_sa)
{
	char rut[8];
	char nombre[20];
	char apellido[20];
	char mail[50];
	char clave[20];

	memset(rut, 0 , sizeof rut);
	memset(nombre, 0 , sizeof nombre);
	memset(apellido, 0, sizeof apellido);
	memset(mail, 0 , sizeof mail);
	memset(clave, 0, sizeof clave);

	sscanf(tx_in->datos,"%8c%20c%20c%50c%20c", rut, nombre, apellido, mail, clave);
	tx_out->len = sprintf(tx_out->datos,"%s%s%s%s%s",rut,nombre, apellido, mail , clave );
}

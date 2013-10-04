#include <stdio.h>
#include <string.h>

struct trans
{
	int len;
	char datos[2000];
};

void proceso (char *aci, struct trans *tx_in, struct trans *tx_out, struct trans *tx_sa)
{
	char nombre[20];
	char genero[20];
	char pais[20];
	char anio[4];
	char stock[20];
	char precio[5];

	memset(nombre, 0 , sizeof nombre);
	memset(genero, 0 , sizeof genero);
	memset(pais, 0, sizeof pais);
	memset(anio, 0 , sizeof anio);
	memset(stock, 0, sizeof stock);
	memset(precio, 0, sizeof precio);

	sscanf(tx_in->datos,"%20c%20c%20c%4c%20c%5c", nombre, genero, pais, anio, stock, precio);
	tx_out->len = sprintf(tx_out->datos,"%s%s%s%s%s%s", nombre, genero, pais, anio, stock, precio);
}

export LD_LIBRARY_PATH=/usr/pgsql-9.0/lib
ecpg demonio.pgc
gcc -I /usr/include/postgresql demonio.c -o demonio -L /usr/include/postgresql/libpq -lecpg


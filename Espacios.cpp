#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include "TG.h"

bool Inicio (Usuario &Pro) {
	
	FILE *Arch;
	Usuario Buscar, Dato;
	bool Sesion = false;
	
	Arch = fopen("Profesionales.dat", "r+b");
	
	printf("Ingrese los Datos Requeridos");
	printf("\n=============================");
	printf("\n\n [Usuario] = ");
	_flushall();
	gets(Buscar.Usuario);
	printf("\n [Contraseña] = ");
	gets(Buscar.Clave);
	
	fread(&Dato, sizeof(Usuario), 1, Arch);
	
	while (!feof(Arch)) {
		
		if (strcmp(Buscar.Usuario, Dato.Usuario) == 0 and strcmp(Buscar.Clave, Dato.Clave) == 0) {
		
			Sesion = true;
			break;
		
		}
		
		fread(&Dato, sizeof(Dato), 1, Arch);
		
	}
	
	if (!Sesion) {
		
		system("CLS");
		
		printf("Usuario o Contraseña Incorrectos...");
		
	} else {
		
		system("CLS");
		
		printf("Bienvenido [%s]", Dato.ApeNom);
		
	}
	
	Pro = Dato;
	
	fclose(Arch);
	
	return Sesion;
	
}

void ListaTurnos (Usuario Pro) {
	
	FILE *Arch, *Aux;
	Turnos Dato;
	Fecha Actual;
	Cliente DatoCli;
	bool Existe = false;
	
	Arch = fopen("Turnos.dat", "r+b");
	Aux = fopen("Clientes.dat", "r+b");
	
	if (!Arch) {
			
		printf("No hay Registros Disponibles Aun...");
		
		return;
			
	}
	
	printf("Ingrese los Datos Requeridos");
	printf("\n==============================");
	printf("\n\n[Fecha Actual]");
	printf("\n\n\t[Dia - DD] = ");
	scanf("%d", &Actual.DD);
	printf("\n\t[Mes - MM] = ");
	scanf("%d", &Actual.MM);
	printf("\n\t[Año - AAAA] = ");
	scanf("%d", &Actual.AAAA);
	
	fread(&Dato, sizeof(Turnos), 1, Arch);
	
	system("CLS");
	
	printf("Lista de Turnos");
	printf("\n=================\n\n");
	
	while (!feof(Arch)) {
		
		if (Pro.ID == Dato.ID and Actual.DD == Dato.FechaTurno.DD and Actual.MM == Dato.FechaTurno.MM and Actual.AAAA == Dato.FechaTurno.AAAA) {
			
			Existe = true;
			
			rewind(Aux);
			
			fread(&DatoCli, sizeof(Cliente), 1, Aux);
			
			while (!feof(Aux)) {
				
				if (Dato.DNI == DatoCli.DNI) {
					
					printf("[Apellido y Nombre] => %s    ---    [DNI] => %d\n\n", DatoCli.ApeNom, DatoCli.DNI);
					
				}
				
				fread(&DatoCli, sizeof(Cliente), 1, Aux);
				
			}
			
		}
		
		fread(&Dato, sizeof(Turnos), 1, Arch);
		
	}
	
	fclose(Aux);
	fclose (Arch);
	
	if (!Existe) {
		
		system("CLS");
		
		printf("Actualmente no hay Turnos para Atender con esos Datos...");
		return;
		
	}
	
}

void Atencion (Usuario Pro) {
	
	FILE *Arch, *Aux, *Atencion, *New;
	Turnos Dato;
	Fecha Actual;
	Cliente DatoCli;
	int i = 0, Estado, DNI;
	char Nom[60];
	bool Existe = false;
	
	Arch = fopen("Turnos.dat", "r+b");
	Aux = fopen("Clientes.dat", "r+b");
	Atencion = fopen("Atencion.dat", "r+b");
	New = fopen("New.dat", "w+b");
	
	if (!Arch) {
			
		printf("No hay Registros Disponibles Aun...");
		
		return;
			
	}
	
	printf("Ingrese los Dato Requeridos para Comenzar la Atencion");
	printf("\n========================================================");
	printf("\n\n[Apellido y Nombre del Cliente] = ");
	_flushall();
	gets(Nom);
	printf("\n\n[DNI del Cliente] = ");
	scanf("%d", &DNI);
	printf("\n\n[Fecha Actual]");
	printf("\n\n\t[Dia - DD] = ");
	scanf("%d", &Actual.DD);
	printf("\n\t[Mes - MM] = ");
	scanf("%d", &Actual.MM);
	printf("\n\t[Año - AAAA] = ");
	scanf("%d", &Actual.AAAA);
	_flushall();
	
	fread(&Dato, sizeof(Turnos), 1, Arch);
	
	while (!feof(Arch)) {
		
		if (Pro.ID == Dato.ID and Actual.DD == Dato.FechaTurno.DD and Actual.MM == Dato.FechaTurno.MM and Actual.AAAA == Dato.FechaTurno.AAAA and Dato.DNI == DNI) {
			
			rewind(Aux);
			
			fread(&DatoCli, sizeof(Cliente), 1, Aux);
			
			while (!feof(Aux)) {
				
				if (strcmp(strlwr(Nom), strlwr(DatoCli.ApeNom)) == 0 and DatoCli.DNI == DNI and Dato.DNI == DNI) {
						
					system("CLS");
			
					printf("Datos del Cliente");
					printf("\n=================");
					printf("\n\n[Apellido y Nombre] => %s", DatoCli.ApeNom);
					printf("\n[DNI] => %d", DatoCli.DNI);
					printf("\n[Domicilio] => %s", DatoCli.Domicilio);
					printf("\n[Edad] => %d", DatoCli.Edad);
					printf("\n[Peso] => %.2f kg\n\n\n", DatoCli.Peso);
					
					system("PAUSE");
					
					system("CLS");

					printf("Ingrese la Evolucion del Tratamiento (380 o menos caracteres)");
					printf("\n\n==> ");
					gets(Dato.DetalleAtencion);
					strcpy(Dato.ApeNom, Pro.ApeNom);
					
					fwrite(&Dato, sizeof(Turnos), 1, Atencion);
					
					i = 1;
					
					Existe = true;
					
				}
				
				fread(&DatoCli, sizeof(Cliente), 1, Aux);
				
			}
			
		}
		
		if (i != 1) {
			
			fwrite(&Dato, sizeof(Turnos), 1, New);
			
		} else {
			
			i = 0;
			
		}
		
		fread(&Dato, sizeof(Turnos), 1, Arch);
		
	}
	
	fclose(New);
	fclose(Atencion);
	fclose(Aux);
	fclose(Arch);
	
	if (!Existe) {
		
		system("CLS");
		
		printf("Datos Incorrectos o No hay Clientes por Atender...");
		
		remove("New.dat");
		
		return;
		
	}
	
	Estado = remove("Turnos.dat");
	rename("New.dat", "Turnos.dat");
	
	if (!Estado) {
		
		system("CLS");
		
		printf("Se Quito de la Lista el Cliente Atendido");
		
	}
	
}

main () {
	
	setlocale(LC_ALL, "");
	
	int Opcion = 0, Ingreso = 1;
	bool Sesion = false;
	Usuario Pro;

	do {
		
		system("CLS");
		
		printf("Modulo Espacios");
		printf("\n==========================");
		printf("\n\n 1.- Iniciar Sesion");
		printf("\n 2.- Visualizar Lista de Espera de Turnos (informes)");
		printf("\n 3.- Registrar Evolucion del tratamiento\n");
		printf("\n 4.- Cerrar la aplicacion\n");
		printf("\nIngrese una Opcion: ");
		scanf("%d", &Opcion);
		
		if (!Sesion and Opcion != 1 and Opcion != 4) {
			
			system("CLS");
				
			printf("Primero Inicie Sesion...");
			
		} else {
			
			Ingreso = 1;
	
		    switch (Opcion) {
			
				case 1:
					
					system("CLS");
					
					Sesion = Inicio(Pro);
					
				break;
				
				case 2:
					
					system("CLS");
					
					ListaTurnos(Pro);
					
				break;
				
				case 3:
					
					system("CLS");
					
					Atencion(Pro);
					
				break;
		
			}
		
		}
		
		printf("\n\n\n");
		
		system("PAUSE");
	
	} while (Opcion != 4);
	
}

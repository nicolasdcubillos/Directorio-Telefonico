#include <iostream>
#include <string.h>
#include <windows.h>

/*
			   NICOLÁS DAVID CUBILLOS
			PROGRAMACIÓN DE COMPUTADORES
		    	NOVIEMBRE 5 DE 2020
*/

using namespace std;

struct Directorio{
	char nombre[30];
	char apellido[30];
	char direccion[30];
};

template <typename T>
struct Nodo
{
    Nodo<T> * SigNombre;
    Nodo<T> * SigApellido;
    Nodo<T> * SigDireccion;
    T info;
};

template <typename T>
struct Lista
{
    Nodo<T> * PrimNombre;
    Nodo<T> * PrimApellido;
    Nodo<T> * PrimDireccion;
    int tam;
};

template <typename T>
Lista<T> * crearDirectorio()
{
    Lista <T> *directorio;

    directorio = new Lista<T>;
    directorio->tam = 0;
    directorio->PrimNombre = NULL;
    directorio->PrimApellido = NULL;
    directorio->PrimDireccion = NULL;

    return directorio;
}

void _top()
{
	system("cls");
	cout << "\n\t\t\tElaborado por Nicolas David Cubillos" << endl;
}

template <typename T>
bool vacio (Lista <T> * directorio)
{
    if (directorio->tam == 0) return true;
    else return false;
}

template <typename T>
void _verDirectorio(Lista <T> * directorio, char opt)
{
	int p = 1;

   	cout << "\t\t- Directorio:" << endl;
    Nodo <T> * aux;

	switch (opt)
	{
		case 'A':
			{
				aux = directorio->PrimNombre;
				break;
			}
		case 'B':
			{
				aux = directorio->PrimApellido;
				break;
			}
		case 'C':
			{
				aux = directorio->PrimDireccion;
				break;
			}
	}
    cout << "\t\t#\t\tNombre\t\tApellido\t\tDireccion" << endl;
    while(aux != NULL)
    {

        cout << "\t\t" << p << "\t\t" << (aux->info)->nombre << "\t\t" << (aux->info)->apellido << "\t\t" << (aux->info)->direccion << endl;
		switch (opt)
		{
			case 'A':
				{
					aux = aux->SigNombre;
					break;
				}
			case 'B':
				{
					aux = aux->SigApellido;
					break;
				}
			case 'C':
				{
					aux = aux->SigDireccion;
					break;
				}
		}
        p++;
    }
    system("Pause");
}

template <typename T>
void _nuevaPersona(Lista<T> * directorio, T PersonaNueva)
{
	int cont = 0;
    Nodo<T> * nuevo = new Nodo<T>();

    nuevo->info = PersonaNueva;
    nuevo->SigNombre = NULL;
    nuevo->SigApellido = NULL;
    nuevo->SigDireccion = NULL;

    if (directorio->tam == 0)
    {
        directorio->PrimNombre = nuevo;
        directorio->PrimApellido = nuevo;
        directorio->PrimDireccion = nuevo;
        directorio->tam++;
    }

    else
    {
    	Nodo<T> *aux;
    	aux = directorio->PrimNombre;

        while (aux->SigNombre != NULL)
        {
        	if (strcmp((nuevo->info)->nombre, ((aux->SigNombre)->info)->nombre) < 0)
        	{
				{
					nuevo->SigNombre = aux->SigNombre;
	        		aux->SigNombre = nuevo;
				}
	        	break;
			}
        	aux = aux->SigNombre;
		}

		aux->SigNombre = nuevo;
		aux = directorio->PrimApellido;

		while (aux->SigApellido != NULL)
        {
        	if (strcmp((nuevo->info)->apellido, ((aux->SigApellido)->info)->apellido) < 0)
        	{
				nuevo->SigApellido = aux->SigApellido;
	        	aux->SigApellido = nuevo;
	        	break;
			}
        	aux = aux->SigApellido;
		}

        aux->SigApellido = nuevo;
        aux = directorio->PrimDireccion;

        while (aux->SigDireccion != NULL)
        {
        	if (strcmp((nuevo->info)->direccion, ((aux->SigNombre)->info)->direccion) < 0)
        	{
				nuevo->SigDireccion = aux->SigDireccion;
	        	aux->SigDireccion = nuevo;
	        	break;
			}
        	aux = aux->SigDireccion;
		}

		cont++;
        aux->SigDireccion = nuevo;
        directorio->tam++;
    }
}

template <typename T>
void _buscar(char* dir, Lista<T> * directorio)
{
	Nodo<T> * aux;
    aux = directorio->PrimDireccion;
    int e = 0;
    while (aux != NULL)
    {
    	if (strcmp(dir, ((aux)->info)->direccion) == 0)
    	{
			if (e==0)
    			cout << "\t\t- Personas encontradas en la direccion '" << dir << "':" << endl;
    		cout << "\t\t" << (aux->info)->nombre << " " << (aux->info)->apellido << endl;
    		e++;
		}
		aux = aux->SigDireccion;
	}
	if (e==0)
		cout << "\t\t[!] No se encontraron personas en la direccion '" << dir << "':" << "\n\t\t";
	system("Pause");
}

template <typename T>
void _delete(char* dname, char* dapel, Lista<T> * directorio)
{
	bool encontrado = 0;
	int cont = 1;

	Nodo<T> * aux;
	aux = directorio->PrimNombre;

	while (aux != NULL)
	{
		if ((strcmp(dname, (aux->info)->nombre) == 0) && (strcmp(dapel, (aux->info)->apellido) == 0))
		{
			encontrado = 1;
			break;
		}
		aux = aux->SigNombre;
		cont++;
	}

	if (encontrado)
	{
        if (cont!=0)
        {
			aux = directorio->PrimNombre;

            for (int i=1; i<cont-1; i++)
                aux = aux->SigNombre;

            Nodo<T> * temp;

            temp = aux->SigNombre;
			aux->SigNombre = temp->SigNombre;
            temp->SigNombre = NULL;

    	}

    	cont = 1;
    	aux = directorio->PrimApellido;

		while (aux != NULL)
		{
			if ((strcmp(dname, (aux->info)->nombre) == 0) && (strcmp(dapel, (aux->info)->apellido) == 0))
			{
				encontrado = 1;
				break;
			}
			aux = aux->SigApellido;
			cont++;
		}

        if (cont != 0)
        {
        	aux = directorio->PrimApellido;

        	for (int i=1; i<cont-1; i++)
                aux = aux->SigApellido;

            Nodo<T> * temp;

        	temp = aux->SigApellido;
			aux->SigApellido = temp->SigApellido;
            temp->SigApellido = NULL;
		}

        cont = 1;
    	aux = directorio->PrimDireccion;

		while (aux != NULL)
		{
			if ((strcmp(dname, (aux->info)->nombre) == 0) && (strcmp(dapel, (aux->info)->apellido) == 0))
			{
				encontrado = 1;
				break;
			}
			aux = aux->SigDireccion;
			cont++;
		}

        if (cont != 0)
        {
        	aux = directorio->PrimDireccion;

        	for (int i=1; i<cont-1; i++)
                aux = aux->SigDireccion;

            Nodo<T> * temp;

        	temp = aux->SigDireccion;
			aux->SigDireccion = temp->SigDireccion;
            temp->SigDireccion = NULL;
		}
            directorio->tam--;
            encontrado = 1;
            cout << "\t\t" << dname << " " << dapel << " eliminado correctamente del directorio." << endl;
        }

	else
		cout << "\t\t[!] No existe una persona en el directorio con ese nombre." << endl;
	system("Pause");
}


int main()
{
	Lista <Directorio*> *directorio = crearDirectorio <Directorio*>();
	char op;
	char op2[1];
	char dir_busqueda[30];
	char dname[30];
	char dapel[30];
	bool salida = 0;

	while(1)
	{
		_top();
		cout << "\t\t[1] Imprimir el directorio telefonico." << endl;
		cout << "\t\t[2] Insertar una persona al directorio." << endl;
		cout << "\t\t[3] Consultar el numero de personas en una direccion." << endl;
		cout << "\t\t[4] Eliminar una persona del directorio." << endl;
		cout << "\t\t[0] Salir.\n\t\t";
		cin >> op;

		switch (op)
		{
			case 'm':
				{
					_verDirectorio(directorio, 'a');
					system("pause");
					break;
				}
			case '1':
				{
					_top();
					if (vacio(directorio))
					{
						cout << "\t\t[!] El directorio esta vacio.\n\t\t";
						system("pause");
						break;
					}
					salida = 0;
					while (!salida)
					{
						cout << "\t\tIngrese el criterio por el cual desea imprimir el directorio telefonico." << endl;
						cout << "\t\t[A] Nombre" << endl;
						cout << "\t\t[B] Apellido" << endl;
						cout << "\t\t[C] Direccion" << endl;
						cout << "\t\t[Z] Salir\n\t\t";
						cin >> op2;
						strupr(op2);
						if (*op2 == 'A' || *op2 == 'B' || *op2 == 'C')
						{
							_verDirectorio(directorio, *op2);
							salida = 1;
						}
						else if (*op2 == 'Z') salida = 1;
					}
					break;
				}
			case '2':
				{
					Directorio* nuevo = new Directorio [1];
					_top();
					cout << "\t\t[-] Nueva persona en el directorio.\n";
					cin.ignore();
					while (1)
					{
						cout << "\t\tIngrese el nombre: ";
						cin.getline(nuevo->nombre, 30);
						if (strlen(nuevo->nombre) > 0)
							break;
					}
					while (1)
					{
						cout << "\t\tIngrese el apellido: ";
						cin.getline(nuevo->apellido, 30);
						if (strlen(nuevo->apellido) > 0)
							break;
					}
					while (1)
					{
						cout << "\t\tIngrese la direccion: ";
						cin.getline(nuevo->direccion, 30);
						if (strlen(nuevo->direccion) > 0)
							break;
					}
					system("cls");
					cout << "\n\t\t- Datos de la nueva persona:" << endl;
					cout << "\t\tNombre: " << nuevo->nombre << "\n\t\tApellido: " << nuevo->apellido << "\n\t\tDireccion: " << nuevo->direccion << "\n\t\t";
					_nuevaPersona(directorio, nuevo);
					system("pause");
					break;
				}
			case '3':
				{
					_top();
					cout << "\t\t[-] Consultar personas por direccion." << endl;
					cin.ignore();
					while (1)
					{
						cout << "\t\tIngrese la direccion: ";
						cin.getline(dir_busqueda, 30);
						if (strlen(dir_busqueda) > 0)
							break;
					}

					_buscar(dir_busqueda, directorio);
					break;
				}
			case '4':
				{
					_top();
					cout << "\t\t[-] Eliminar una persona del directorio." << endl;
					cin.ignore();
					while (1)
					{
						cout << "\t\tIngrese el nombre: ";
						cin.getline(dname, 30);
						if (strlen(dname) > 1)
							break;
					}
					while (1)
					{
						cout << "\t\tIngrese el apellido: ";
						cin.getline(dapel, 30);
						if (strlen(dapel) > 1)
							break;
					}
					_delete(dname, dapel, directorio);
					break;
				}
			case '0':
					exit(1);
		}
	}
}

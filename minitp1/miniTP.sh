#!/bin/bash

function error_empty(){
	echo "Error: debe ejecutar con un parámetro al menos."
}

function error_params(){
	echo "Error: debe ejecutar con un solo parámetro."
}

function error_dir(){
	echo "Error: ya existe directorio."
}

function files_home(){
	find /home -type f -exec ls -l {} \; 2>/dev/null 
}

if [ $# -eq 1 ]
then
	parametro=$1
	cd $HOME
	if [ -d "$parametro" ]
	then
		error_dir
	else
		mkdir "$parametro"
		echo "Directorio $parametro creado."
		echo "buscando archivos /home ..."
		echo ""
		cd "$parametro" || exit
		files=$(files_home)

		echo "Listado de archivos con permisos de HOME incluyendo archivos ocultos." > contenido_home.txt
		echo "------------------------------------------" >> contenido_home.txt
        files_home >> contenido_home.txt

		cat contenido_home.txt
	fi
else
	if [ $# -eq 0 ]
	then
		error_empty
	else
		error_params
	fi
fi

read -p "PRESIONAR ENTER PARA SALIR"

exit
// Fill out your copyright notice in the Description page of Project Settings.

#include <Python.h>
#include <windows.h>
#include <string>
#include <iostream>
#include "MainMenuUserWIdget.h"

void UMainMenuUserWIdget::StartPythonServer() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = string( buffer ).find_last_of( "\\/" );
    std::string path = string( buffer ).substr( 0, pos);

	char filename[] = path;
	FILE* fp;

	Py_Initialize();

	fp = _Py_fopen(filename, "r");
	PyRun_SimpleFile(fp, filename);

	Py_Finalize();
}
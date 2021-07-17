#include "pch.h"
#include "concommand.h"
#include <iostream>

typedef void(*ConCommandConstructorType)(ConCommand* newCommand, const char* name, void(*callback)(const CCommand&), const char* helpString, int flags, void* parent);
ConCommandConstructorType conCommandConstructor;

void RegisterConCommand(const char* name, void(*callback)(const CCommand&), const char* helpString, int flags)
{
	std::cout << "Registering ConCommand " << name << std::endl;

	// no need to free this ever really, it should exist as long as game does
	ConCommand* newCommand = new ConCommand;
	conCommandConstructor(newCommand, name, callback, helpString, flags, nullptr);
}

void InitialiseConCommands(HMODULE baseAddress)
{
	conCommandConstructor = (ConCommandConstructorType)((char*)baseAddress + 0x415F60);
}
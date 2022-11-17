#include "WeaponModule.h"

#include "WeaponStyle.h"
#include "WeaponCommand.h"

#define LOCTEXT_NAMESPACE "FWeaponModule"

void FWeaponModule::StartupModule()
{
	FWeaponStyle::Get();

	Command = MakeShareable(new FWeaponCommand());
	Command->Startup();
}

void FWeaponModule::ShutdownModule()
{
	if(Command.IsValid())
		Command.Reset();
	
	FWeaponStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWeaponModule, Weapon)
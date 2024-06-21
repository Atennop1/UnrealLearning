#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSavingTestModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

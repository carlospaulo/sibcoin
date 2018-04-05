#include "callbackdbforgui.h"

CallBackDbForGui *CallBackDbForGui::pSingleton = nullptr;
int CallBackDbForGui::nCounter = 0;

CallBackDbForGui::CallBackDbForGui()
{
    qRegisterMetaType<TypeTable>("TypeTable");
    qRegisterMetaType<TypeTableOperation>("TypeTableOperation");
    qRegisterMetaType<StatusTableOperation>("StatusTableOperation");
}

CallBackDbForGui *CallBackDbForGui::instance()
{
    if (pSingleton == nullptr) {
        pSingleton = new CallBackDbForGui();
    }

    nCounter++;

    return pSingleton;
}

void CallBackDbForGui::freeInstance()
{
    if (nCounter > 0) {
        nCounter--;

        if (nCounter == 0) {
            delete pSingleton;
            pSingleton = nullptr;
        }
    }
}

void CallBackDbForGui::finishTableOperation(const TypeTable &table, const TypeTableOperation &operation, const StatusTableOperation &status)
{
    Q_EMIT tableOperationFinished(table, operation, status);
}

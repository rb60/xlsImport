#ifndef XLSIMPORT_H
#define XLSIMPORT_H
#include<qglobal.h>
#include "importTypes.h"
#include <QList>

#ifdef Q_OS_WIN
#define МУ_EXPORT __declspec(dllexport)
#else
    #define МУ_EXPORT
#endif


class XlsImport : public ImportData
{
private:
    QList<char*> chars;
public:
    char *getName() override;
    int getParametrsCount() override;
    char *getParametrName(int index) override;
    int getParametrType(int index) override;
    TransferData *getData(char **parametrs) override;
    void destroy() override;

};



extern "C" МУ_EXPORT
{
    ImportData* getInstance();
}

#endif // XLSIMPORT_H

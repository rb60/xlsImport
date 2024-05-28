#include "xlsimport.h"
#include "simpletransferdata.h"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"


ImportData *getInstance()
{
    return new XlsImport;
}

char *XlsImport::getName()
{
    char* result = "Excel";
    chars.append(result);
    return result;
}

int XlsImport::getParametrsCount()
{
    return 1;
}

char *XlsImport::getParametrName(int index)
{
    char* result;
    if(index == 0)
    {
        result = "Path";
    }
    else
    {
        result = "";
    }
    chars.append(result);
    return result;
}

int XlsImport::getParametrType(int index)
{
    return ParametrType::OPEN_FILE_PATH;
}

TransferData *XlsImport::getData(char **parametrs)
{
    QString filePath(parametrs[0]);
    SimpleTransferData* result = new SimpleTransferData;

    QXlsx::Document doc(filePath);
    if(doc.load())
    {
        QXlsx::Cell* cell;

        for(int i = 2;; i++)
        {
            cell = doc.cellAt(1,i);
            if(cell != nullptr)
            {
                result->columns.append(cell->value().toString());
            }
            else
            {
                break;
            }
        }

        for(int i = 2;; i++)
        {
            cell = doc.cellAt(i,1);
            if(cell != nullptr)
            {
                result->rows.append(cell->value().toString());
            }
            else
            {
                break;
            }
        }

        result->values.resize(result->rows.size());
        result->valueExist.resize(result->rows.size());
        for(int i = 2; i < result->rows.size() + 2; i++)
        {
            result->values[i - 2].resize(result->columns.size());
            result->valueExist[i - 2].resize(result->columns.size());
            for (int j = 2; j < result->columns.size() + 2; j++)
            {
                cell = doc.cellAt(i, j);
                if(cell != nullptr)
                {
                    QVariant var = cell->readValue();
                    bool OK;
                    float floatResult = var.toFloat(&OK);
                    if(OK)
                    {
                        result->values[i - 2][j - 2] = floatResult;
                        result->valueExist[i - 2][j - 2] = true;
                    }
                    else
                    {
                        result->values[i - 2][j - 2] = 0;
                        result->valueExist[i - 2][j - 2] = false;
                    }
                }
                else
                {
                    result->values[i - 2][j - 2] = 0;
                    result->valueExist[i - 2][j - 2] = false;
                }
            }
        }
    }

    return result;
}

void XlsImport::destroy()
{
    for(int i = 0; i < chars.size(); i++)
    {
        delete[] chars[i];
    }
    delete this;
}

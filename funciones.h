
#define maxData 100

struct Info{ //Estructura para la informacion correspondiente
    float co2;
    float so2;
    float no2;
    float pm25;
    float temp;
    float wind;
    float hum;
    char date[10];
};

struct readData{ //Estructura para almacenar los datos leidos
    float co2Data[maxData];
    float so2Data[maxData];
    float no2Data[maxData];
    float pm25Data[maxData];
    float tempData[maxData];
    float windData[maxData];
    float humData[maxData];
};


//Prototipado de funciones que se utilizan en main
void getDiaActual(struct Info info, const char *filename);
void monitorActual(struct Info *info);
void predictionAlerts();
void predictTomorrow();
void historicalAvrgBySearch();
void writeReport(bool f1, bool f2, bool f3, bool f4, struct Info *info);
int mainValid(bool f1);
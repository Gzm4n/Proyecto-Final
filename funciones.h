
#define maxData 100

struct Info{
    float co2;
    float so2;
    float no2;
    float pm25;
    float temp;
    float wind;
    float hum;
    char date[10];
};

struct readData{
    float co2Data[maxData];
    float so2Data[maxData];
    float no2Data[maxData];
    float pm25Data[maxData];
    float tempData[maxData];
    float windData[maxData];
    float humData[maxData];
};

void getDiaActual(struct Info *info, const char *filename);
void monitorActual(struct Info *info);
void predictionAlerts();
void predictTomorrow();
void historicalAverage();
void writeReport();
int mainValid(bool f1);
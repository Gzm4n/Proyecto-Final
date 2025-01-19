
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

struct nonDated{
    float co2;
    float so2;
    float no2;
    float pm25;
    float temp;
    float wind;
    float hum;
};

void getDiaActual(struct Info *info, const char *filename);
void monitorActual(struct Info *info);
void predictionAlerts();
void predictTomorrow();
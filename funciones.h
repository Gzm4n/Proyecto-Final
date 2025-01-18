
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

void getDiaActual(struct Info *info, const char *filename);
void monitorActual(struct Info *info);

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

const char zonas[5][15] = {"Calderon", "Cumbaya", "Pifo", "Tababela", "Tumbaco"};

const float co2Breakpoints[6][4] = {
    {0.0, 350.0, 0, 50},
    {351.0, 450.0, 51, 100},
    {451.0, 700.0, 101, 150},
    {701.0, 1000.0, 151, 200},
    {1001.0, 1500.0, 201, 300},
    {1501.0, 2000.0, 301, 500}
};

const float so2Breakpoints[6][4] = {
    {0.0, 20.0, 0, 50},
    {20.1, 80.0, 51, 100},
    {80.1, 365.0, 101, 150},
    {365.1, 800.0, 151, 200},
    {800.1, 1600.0, 201, 300},
    {1600.1, 2100.0, 301, 500}
};

const float no2Breakpoints[6][4] = {
    {0.0, 40.0, 0, 50},
    {40.1, 80.0, 51, 100},
    {80.1, 180.0, 101, 150},
    {180.1, 280.0, 151, 200},
    {280.1, 400.0, 201, 300},
    {400.1, 500.0, 301, 500}
};

const float pm25Breakpoints[6][4] = {
    {0.0, 12.0, 0, 50},
    {12.1, 35.4, 51, 100},
    {35.5, 55.4, 101, 150},
    {55.5, 150.4, 151, 200},
    {150.5, 250.4, 201, 300},
    {250.5, 500.4, 301, 500}
};

void getDiaActual(struct Info *info, const char *filename);
void monitorActual(struct Info *info);
import random
import csv
from datetime import datetime, timedelta

zones = ["Tumbaco", "Jipijapa", "Cumbaya", "Chillogallo", "Sangolqui"]
start_date = datetime(2024, 12, 21)
num_days = 30

def random_float(min_val, max_val, decimals=1):
    return round(random.uniform(min_val, max_val), decimals)

data = []
for day in range(num_days):
    date = (start_date + timedelta(days=day)).strftime("%Y-%m-%d")
    for zone in zones:
        co2 = random_float(350, 450)
        so2 = random_float(0, 20)
        no2 = random_float(5, 60)
        pm25 = random_float(5, 100)
        temperature = random_float(-10, 45)
        wind_speed = random_float(0, 50)
        humidity = random_float(20, 90)
        data.append([zone, co2, so2, no2, pm25, temperature, wind_speed, humidity, date])

with open("data_historica.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(["Zona", "CO2(ppm)", "SO2(ppb)", "NO2(ppb)", "PM2.5(ug/m^3)", "Temperatura(Celsius)", "VelocidadViento(km/h)", "Humedad(%)", "Fecha(YYYY-MM-DD)"])
    writer.writerows(data)

print("Historical data generated and saved to 'historical_data.csv'.")
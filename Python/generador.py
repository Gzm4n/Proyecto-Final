import random
import csv
from datetime import datetime, timedelta

# Define zones and date range
zones = ["Tumbaco", "La Carolina", "Cumbaya", "San Rafael", "San Isidro"]
start_date = datetime(2024, 12, 18)
num_days = 30

# Random value generator within a range
def random_float(min_val, max_val, decimals=1):
    return round(random.uniform(min_val, max_val), decimals)

# Generate 30 days of data
data = []
for day in range(num_days):
    date = (start_date + timedelta(days=day)).strftime("%Y-%m-%d")
    for zone in zones:
        co2 = random_float(100, 300)
        so2 = random_float(10, 50)
        no2 = random_float(20, 70)
        pm25 = random_float(10, 60)
        temperature = random_float(15, 35)
        wind_speed = random_float(5, 15)
        humidity = random_float(40, 80)
        data.append([zone, co2, so2, no2, pm25, temperature, wind_speed, humidity, date])

# Write data to CSV file
with open("historical_data.csv", "w", newline="") as file:
    writer = csv.writer(file)
    writer.writerow(["Zona", "CO2", "SO2", "NO2", "PM2.5", "Temperatura", "VelocidadViento", "Humedad", "Fecha"])
    writer.writerows(data)

print("Historical data generated and saved to 'historical_data.csv'.")
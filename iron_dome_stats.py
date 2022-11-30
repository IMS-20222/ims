import os
import subprocess
import time

def get_stats():
    runs_dict = {
        "100": [],
        "200": [],
        "300": [],
        "500": [],
        "750": [],
        "1000": [],
        "1500": [],
        "2000": [],
        "2500": [],
        "3000": [],
        "4000": [],
        "5000": [],
        "7500": [],
        "10000": [],
        "12500": [],
        "15000": [],
        "17500": [],
        "20000": [],
        "25000": [],
        "30000": [],
    }
    for key, value in runs_dict.items():
        for i in range(10):
            output = os.popen(f"./main -Z 1440 -R {key}").readlines()
            time.sleep(1);
            percentage = str(output[23]).split("%")[0].split("m")[-1].strip()
            value.append(float(percentage))
        avg = sum(value) / 10
        print(f"{key}: ".ljust(10), "{:.3f}".format(avg).rjust(10))

if __name__ == "__main__":
    get_stats()

import requests

url = "http://localhost:8080"

response = requests.get(url)

if response.status_code == 200:
    print(response.text)
else:
    print("HTTP request failed")

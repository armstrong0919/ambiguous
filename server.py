from http.server import BaseHTTPRequestHandler, HTTPServer
import time
import logging
import json
hostName = "0.0.0.0" #0.0.0.0 #localhost #127.0.0.1
serverPort = 8080

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("Not Connect", "utf-8"))
        #self.wfile.write(bytes("<html><head><title>https://pythonbasics.org</title></head>", "utf-8"))
        #self.wfile.write(bytes("<p>Request: %s</p>" % self.path, "utf-8"))
        #self.wfile.write(bytes("<body>", "utf-8"))
        #self.wfile.write(bytes("<p>This is an example web server.</p>", "utf-8"))
        #self.wfile.write(bytes("</body></html>", "utf-8"))

    def do_POST(self):
        print(self.headers) # which device connect to this server 
        print(self.command) # api from ESP32 ,GET/POST...etc
        req_datas = self.rfile.read(int(self.headers['content-length']))
        print(req_datas) #data from ESP32
        data = {
            'result_code': '1',
            'result_desc': 'Success'
        }
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()
        self.wfile.write(json.dumps(data).encode('utf-8'))

if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")

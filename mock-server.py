import os
import asyncio
import datetime
import random
import functools
import websockets
import np
from http import HTTPStatus

MIME_TYPES = {
    "html": "text/html",
    "js": "text/javascript",
    "css": "text/css"
}

sampling_rate = 1000
freq = 5
samples = 1000
x = np.arange(samples)
y = 100*np.sin(2*np.pi * freq * x / sampling_rate)

# print(y)

async def process_request(path, request_headers):
    """Serves a file when doing a GET request with a valid path."""

    if "Upgrade" in request_headers:
        return  # Probably a WebSocket connection

    if path == '/':
        path = '/index.html'

    response_headers = [
        ('Server', 'asyncio websocket server'),
        ('Connection', 'close'),
    ]

    # Derive full system path
    full_path = os.path.realpath(path[1:])

    # Validate the path
    if not os.path.exists(full_path) or not os.path.isfile(full_path):
        print("HTTP GET {} 404 NOT FOUND".format(path))
        return HTTPStatus.NOT_FOUND, [], b'404 NOT FOUND'

    # Guess file content type
    extension = full_path.split(".")[-1]
    mime_type = MIME_TYPES.get(extension, "application/octet-stream")
    response_headers.append(('Content-Type', mime_type))

    # Read the whole file into memory and send it out
    body = open(full_path, 'rb').read()
    response_headers.append(('Content-Length', str(len(body))))
    print("HTTP GET {} 200 OK".format(path))
    return HTTPStatus.OK, response_headers, body


async def time(websocket, path):
    index = 0
    while True:
        if index == len(y) - 1:
            index = 0
        now = datetime.datetime.utcnow().isoformat() + "Z"
        await websocket.send(str(y[index]))
        await asyncio.sleep(1/25)
        index = index + 1
        if index % 17 == 0:
            await asyncio.sleep(2)

start_server = websockets.serve(time, "127.0.0.1", 5678, process_request=process_request)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
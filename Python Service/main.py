from homeassistant_api import Client
import paho.mqtt.client as mqtt
import json

broker_address = "eu1.cloud.thethings.network"
broker_port = 1883
username = "paketbox-iot@ttn"
passkey = "NNSXS.VBOIQGBJTR2OQYPPH2PZP2WIOQWY532HTYXS2EY.BIUKFEZFWS2L56VCH4JBWJQBLMWUH3OJPCSLWKPFJJBHUTRHYAIQ"
topic = "v3/paketbox-iot@ttn/devices/eui-70b3d57ed0064c21/up"


URL = 'http://192.168.0.164:8123/api'
TOKEN = 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9' \
        '.eyJpc3MiOiIzMjFiMDk2YWMzYmE0OWQ2OTkxODA2ZTFmYmQ2NTQzNyIsImlhdCI6MTcwNzEzODI1NiwiZXhwIjoyMDIyNDk4MjU2fQ' \
        '.piCuYWiscPjG88Fj3AQrX3suJqP-o4oKEQcQpxeSl_E'


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker")
        client.subscribe(topic)
    else:
        print(f"Connection failed with code {rc}")


def on_message(client, userdata, msg):
    print(f"{msg.payload.decode()}")
    payload = msg.payload.decode('utf-8')  # Decode payload bytes to string
    try:
        data = json.loads(payload)

        uplink_message = data["uplink_message"]
        print(json.dumps(uplink_message, indent=4))
    except json.JSONDecodeError as e:
        print("Error decoding JSON:", e)

    print(uplink_message)

    home_assistant_client = Client(URL, TOKEN)
    home_assistant_client.trigger_service('notify', 'notify', message='Es ist ein Paket in der Paketbox angekommen!', title='Alarm')


mqtt = mqtt.Client()

mqtt.on_connect = on_connect
mqtt.on_message = on_message

mqtt.username_pw_set(username=username, password=passkey)

mqtt.connect(broker_address, broker_port, keepalive=60)

mqtt.loop_forever()

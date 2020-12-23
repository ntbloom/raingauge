# Schema v1 worksheet

A work in progress to get all of the MQTT topics sorted out. For now this is only the topics that need to be addressed on the client side.

---

# add rain event

Sent whenever a rain event occurs. Message timestamp will be recorded by the broker.

topic: "v1/rain/{gauge}"
schema:

```json
[
    "timestamp": {
        "type": "string",
        "format": "ISO8601 with timezone",
        "example": "2020-12-09T22:56:47,3446917-05:00",
        "notes": "timestamp the measurement was taken, not when the mqtt message was sent"
    },
    "rain_amount": {
        "type": "string",
        "format": "mm to 4 decimal precision",
        "example": "0.2794",
        "notes": "technically a 32-bit float"
    }
]
```

sample topic: "v1/rain/bluehouse"
sample payload: "['2020-12-09T22:56:47,3446917-05:00','0.2794']"

---

# daily check-in

Sent on a regular basis, possibly 2x per day? Message timestamp will be recorded by the broker.

topic: "v1/daily/{gauge}"
schema:

```json
[
    "timestamp": {
        "type": "string",
        "format": "ISO8601 with timezone",
        "example": "2020-12-09T22:56:47,3446917-05:00",
        "notes": "timestamp the measurement was taken, not when the mqtt message was sent"
    },
    "system_uptime" {
        "type": "string",
        "format": "32-bit float",
        "example": "92563.04",
        "notes": "number of seconds system has been running, taken from `/proc/uptime`"
    }
]
```

sample topic: "v1/checkin/bluehouse"
payload: "['2020-12-20T22:56:47,3446917-05:00', '92563.04']"

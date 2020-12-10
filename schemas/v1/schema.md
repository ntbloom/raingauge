# Schema v1 worksheet

A work in progress to get all of the MQTT topics sorted out. For now this is only the topics that need to be addressed on the client side.

### Headers

Sent with every MQTT message

**implemented?: NO**

_example_

```json
"header":
    {
        "schema": "v1.json",
        "msg_timestamp": "2020-12-09T22:56:47,3446917-05:00",
        "client": "ntbloom",
    }
```

### Add a Gauge

Sent to add a new gauge to the cloud

**implemented?: NO**

_example_

topic: v1/add/{SERIAL}

```
"topic": "v1/add/000001",
"payload":
    {
        "serial": "000001",
        "name": "blue-house-garden",
        "description": "0.2794mm per click, in the garden on the south side"
    }
```

### Rain Event

Sent on every rain event

**implemented?: NO**

_example_

topic: v1/rain/{SERIAL}

```json
"topic": "v1/rain/000001",
"payload":
    {
        "serial": "000001",
        "event_timestamp": "2020-12-09T22:47:32,6421110-05:00",
        "amount": "0.2794mm"
    }
```

### Status Message

Sent on regular basis as check-in (2x/day?)

**implemented?: NO**

_example_

topic: v1/status/{SERIAL}

```json
"topic": "v1/status/000001",
"payload":
    {
        "serial": "000001",
        "last_reboot": "2020-10-04T03:32:16,1283901-05:00",
        "uptime": "up 1 day, 14 hours, 7 minutes",
        "status":
            {
                "active": "True",
                "active_since": "2020-10-04T03:32:16,1283901-05:00"
            }
    }
```

### Delete a Gauge

Remove a gauge from the cloud

**implemented?: NO**

_example_

topic: v1/delete/{SERIAL}

```json
"topic": "v1/delete/000001",
"payload":
    {
        "serial": "000001",
        "name": "blue-house-gaardden",
        "reason": "accidental spelling error"
    }
```

### Update A Gauge

Update a gauge's info in the cloud

**implemented?: NO**

_example_

topic: v1/update/{SERIAL}

```json
"topic": "v1/update/000001",
"payload":
    {
        "serial": "000001",
        "updated_properties":
            [
                "name":
                    {
                        "old": "blue-house-garden",
                        "new": "bhg"
                    },
                "description":
                    {
                        "old": "0.2794mm per click, in the garden on the south side",
                        "new": "0.2794mm/click, north side garden"
                    }
            ]
    }
```

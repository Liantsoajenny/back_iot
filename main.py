from fastapi import FastAPI, Request
from pydantic import BaseModel
from typing import Optional

app = FastAPI()


latest_distance: Optional[float] = None

class DistanceData(BaseModel):
    distance: float

@app.post("/send-distance")
async def receive_distance(data: DistanceData):
    global latest_distance
    latest_distance = data.distance
    return {"message": "Distance received successfully", "distance": latest_distance}


@app.get("/get-distance")
async def get_distance():
    if latest_distance is None:
        return {"message": "No distance received yet"}
    return {"distance": latest_distance}


@app.put("/update-distance")
async def update_distance(data: DistanceData):
    global latest_distance
    latest_distance = data.distance
    return {"message": "Distance updated successfully", "distance": latest_distance}
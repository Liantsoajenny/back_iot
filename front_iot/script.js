const distanceDisplay = document.getElementById("distance");
const updateForm = document.getElementById("updateForm");

async function fetchDistance() {
  try {
    const res = await fetch("http://192.168.137.154:8080/get-distance");
    const data = await res.json();
    distanceDisplay.textContent = `${data.distance.toFixed(1)} cm`;
    console.log(data)
  } catch (err) {
    distanceDisplay.textContent = "Erreur";
  }
}

setInterval(fetchDistance, 3000);
fetchDistance();

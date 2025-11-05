async function apiCall(endpoint, method = "GET", data = null) {
    try {
        const options = {
            method: method,
            headers: {
                "Content-Type": "application/json",
            },
        };

        if (data) {
            options.body = JSON.stringify(data);
        }

        const response = await fetch(`/api/${endpoint}`, options);
        return await response.json();
    } catch (error) {
        console.error("API call failed:", error);
        return { success: false, message: "Network error" };
    }
}

async function getStatus() {
    const result = await apiCall("status", "GET");
    if (result.ledState !== undefined) {
        document.getElementById("status").innerHTML = `
            <strong>Catflap:</strong> ${result.ledState ? "OPEN" : "CLOSED"}<br>
            <strong>Time:</strong> ${result.currentTime}<br>
            <strong>Last Event:</strong> ${
                result.lastEvent
                    ? `${result.lastEvent.eventType} by ${result.lastEvent.user} at ${result.lastEvent.eventTime}`
                    : "None"
            }
        `;
    } else {
        document.getElementById("status").innerHTML = "Failed to get status";
    }
}

async function turnLedOn() {
    const data = { state: true };
    const result = await apiCall("led", "POST", data);
    if (result.success) {
        console.log("Catflap opened");
        getStatus();
    } else {
        alert("Failed to open catflap: " + result.message);
    }
}

async function turnLedOff() {
    const data = { state: false };
    const result = await apiCall("led", "POST", data);
    if (result.success) {
        console.log("Catflap closed");
        getStatus();
    } else {
        alert("Failed to close catflap: " + result.message);
    }
}

// Load initial status when page loads
window.onload = function () {
    getStatus();
};

// Auto-refresh status every 10 seconds
setInterval(getStatus, 10000);

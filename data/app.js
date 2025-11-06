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

async function getCatlog() {
    const result = await apiCall("catlog", "GET");

    if (result.log && result.cats) {
        displayCatlog(result.log, result.cats);
    } else {
        document.getElementById("catlog").innerHTML = "Failed to load catlog";
    }
}

function displayCatlog(log, cats) {
    // Create a map of tagId to cat name for easy lookup
    const catMap = {};
    cats.forEach((cat) => {
        catMap[cat.tagId] = cat.name;
    });

    // Sort log entries by timestamp (most recent first)
    const sortedLog = log.sort((a, b) => b.timestamp - a.timestamp);

    let html = "";

    if (sortedLog.length === 0) {
        html = "<p>No activity logged yet.</p>";
    } else {
        html = '<table class="log-table">';
        html +=
            "<thead><tr><th>Time</th><th>Cat</th><th>Tag ID</th></tr></thead>";
        html += "<tbody>";

        sortedLog.forEach((entry) => {
            const catName = catMap[entry.tagId] || "Unknown Cat";
            const formattedTime = new Date(
                entry.timestamp * 1000
            ).toLocaleString();

            html += `<tr>
                <td>${formattedTime}</td>
                <td>${catName}</td>
                <td>${entry.tagId}</td>
            </tr>`;
        });

        html += "</tbody></table>";
    }

    document.getElementById("catlog").innerHTML = html;
}

// Load initial catlog when page loads
window.onload = function () {
    getCatlog();
};

// Auto-refresh catlog every 30 seconds
setInterval(getCatlog, 30000);

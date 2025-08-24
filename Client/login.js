

const ws = new WebSocket("ws://localhost:9002");

const loginForm = document.getElementById("loginForm");
const errorMsg = document.getElementById("errorMsg");

// LOGIN
loginForm.addEventListener("submit", (e) => {
  e.preventDefault();

  const username = document.getElementById("username").value.trim();
  const password = document.getElementById("password").value.trim();

  // Send login request
  const msg = {
    type: "login",
    username,
    password
  };

  ws.send(JSON.stringify(msg));
});

// LOGIN ACK
ws.onmessage = (event) => {
  try {
    const msg = JSON.parse(event.data);

    if (msg.type === "login_success") {
        // Save token or user ID for later
      localStorage.setItem("authToken", msg.token);

      // Redirect to main app page
      window.location.href = "index.html";
    }
    else if (msg.type === "login_failed") {
      errorMsg.textContent = "Invalid username or password.";
    }
  } catch (err) {
    console.error("Error parsing message", err);
  }
};

const ws = new WebSocket("ws://localhost:9002"); // Change to your server port
ws.binaryType = "arraybuffer";

ws.onopen = () => {
    document.getElementById("status").innerText = "Connected to WebSocket server.";
};

ws.onclose = () => {
    document.getElementById("status").innerText = "Disconnected from server.";
};

ws.onerror = (err) => {
    document.getElementById("status").innerText = "Error: " + err.message;
};

document.getElementById("orderForm").addEventListener("submit", (e) => {
    e.preventDefault();

    const messageType = 1; // Should be an option later.
    const symbol = parseInt(document.getElementById("symbol").value);
    const price = parseFloat(document.getElementById("price").value);
    const quantity = parseInt(document.getElementById("quantity").value);
    const orderID = parseInt(document.getElementById("orderID").value);
    const userID = parseInt(document.getElementById("userID").value);
    const isBuy = parseInt(document.getElementById("isBuy").value);
    const orderType = parseInt(document.getElementById("orderType").value);

    // Binary layout matches your struct:
    // orderType (4), symbol (4), price (4), quantity (4), orderID (4),
    // userID (4), isBuy (4), orderType (4) = 32 bytes
    const buffer = new ArrayBuffer(32);
    const view = new DataView(buffer);

    let offset = 0;
    view.setUint32(offset, messageType, true); offset += 4;
    view.setUint32(offset, symbol, true); offset += 4;
    view.setFloat32(offset, price, true); offset += 4;
    view.setUint32(offset, quantity, true); offset += 4;
    view.setUint32(offset, orderID, true); offset += 4;
    view.setUint32(offset, userID, true); offset += 4;
    view.setUint32(offset, isBuy, true); offset += 4;
    view.setUint32(offset, orderType, true);

    ws.send(buffer);
    document.getElementById("status").innerText = "Order sent!";
});


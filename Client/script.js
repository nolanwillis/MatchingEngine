const WS_URL = "ws://localhost:9002"; 

// NAVBAR
const tabs = document.querySelectorAll(".tab");
const navButtons = document.querySelectorAll(".nav-btn");
navButtons.forEach(btn => {
  btn.addEventListener("click", () => {
    const target = btn.getAttribute("data-tab");
    // toggle active button
    navButtons.forEach(b => b.classList.toggle("active", b === btn));
    // toggle tabs
    tabs.forEach(tab => tab.classList.toggle("active", tab.id === target));
  });
});

// CONNECTION STATUS 
const wsDot = document.getElementById("wsStatus");
const wsText = document.getElementById("wsText");
function setStatus(state) 
{
    if (state === "connected") 
    {
        wsDot.className = "dot dot-green";
        wsText.textContent = "Connected";
    } 
    else if (state === "connecting") 
    {
        wsDot.className = "dot dot-yellow";
        wsText.textContent = "Connecting…";
    } 
    else 
    {
        wsDot.className = "dot dot-red";
        wsText.textContent = "Disconnected";
    }
}

// HELPERS
function GetStockSymbol(value) 
{
    switch (value) 
    {
        case 1: return "AAA";
        case 2: return "BBB";
        case 3: return "CCC";
        case 4: return "DDD";
        case 5: return "EEE";
        default: return "NA";
    }
}
function GetOrderType(value) 
{
    switch (value) 
    {
        case 1: return "Market";
        case 2: return "Limit";
        default: return "NA";
    }
}

// ESTABLISHING WEBSOCKET CONNECTION
let ws;
connect();

function connect() 
{
    try 
    {
        setStatus("connecting");
        ws = new WebSocket(WS_URL);
        ws.binaryType = "arraybuffer";

        ws.onopen = () => setStatus("connected");
        ws.onclose = () => setStatus("disconnected");

        ws.onerror = (e) => {
        console.error("WebSocket error:", e);
        setStatus("disconnected");
        };

        ws.onmessage = onTradeMessage; // handle broadcasts (trades)
    } 
    catch (e) 
    {
        console.error("Failed to create WebSocket:", e);
        setStatus("disconnected");
    }
}

// SENDING ORDERS

// Order Format:
// 0:  messageType (u32)
// 4:  symbol      (u32)
// 8:  price       (f32)
// 12: quantity    (u32)
// 16: orderID     (u32)
// 20: userID      (u32)
// 24: isBuy       (u32)
// 28: orderType   (u32)

document.getElementById("orderForm").addEventListener("submit", (e) => {
    e.preventDefault();

    if (!ws || ws.readyState !== WebSocket.OPEN) 
    {
        setFormStatus("WebSocket not connected.");
        return;
    }

    const messageType = parseInt(document.getElementById("messageType").value, 10); // e.g., 1
    const symbol = parseInt(document.getElementById("symbol").value, 10);
    const price = parseFloat(document.getElementById("price").value);
    const quantity = parseInt(document.getElementById("quantity").value, 10);
    const orderID = parseInt(document.getElementById("orderID").value, 10);
    const userID = parseInt(document.getElementById("userID").value, 10);
    const isBuy = parseInt(document.getElementById("isBuy").value, 10);
    const orderType = parseInt(document.getElementById("orderType").value, 10);


    const buffer = new ArrayBuffer(32);
    const view = new DataView(buffer);

    let off = 0;
    view.setUint32(off, messageType, true); off += 4;
    view.setUint32(off, symbol, true);      off += 4;
    view.setFloat32(off, price, true);      off += 4;
    view.setUint32(off, quantity, true);    off += 4;
    view.setUint32(off, orderID, true);     off += 4;
    view.setUint32(off, userID, true);      off += 4;
    view.setUint32(off, isBuy, true);       off += 4;
    view.setUint32(off, orderType, true);

    ws.send(buffer);
    setFormStatus("Order sent!");
});

function setFormStatus(message) 
{
    document.getElementById("status").textContent = message;
}

// RECEIVING TRADES 

// Trade Format:
// 0:  messageType (u32) 
// 4:  symbol      (u32)
// 8:  price       (f32)
// 12: quantity    (u32)
// 16: buyOrderID  (u32)
// 20: sellOrderID (u32)
// 24: userID      (u32)
// 28: orderType   (u32)

const tradeContainer = document.getElementById("tradeContainer");

async function onTradeMessage(event) 
{
    try 
    {
        const buffer = event.data instanceof ArrayBuffer ? event.data : await event.data.arrayBuffer();
        const data = new DataView(buffer);
        
        const messageType = data.getUint32(0, true);

        const trade = {
        symbol: GetStockSymbol(data.getUint32(4, true)),
        price: data.getFloat32(8, true),
        quantity: data.getUint32(12, true),
        buyOrderID: data.getUint32(16, true),
        sellOrderID: data.getUint32(20, true),
        userID: data.getUint32(24, true),
        orderType: GetOrderType(data.getUint32(28, true))
        };

        addTradeCard(trade);
    } 
    catch (err) 
    {
        console.error("Failed to parse trade message:", err);
    }
}

function addTradeCard(trade) 
{
    const card = document.createElement("div");
    card.className = "trade-card";

    const info = document.createElement("div");
    info.className = "trade-info";
    info.innerHTML = `
    <span><strong>${trade.symbol}</strong></span>
    <span>Price: $${Number(trade.price).toFixed(2)}</span>
    <span>Qty: ${trade.quantity}</span>
    <span>Buy Order ID: ${trade.buyOrderID}</span>
    <span>Sell Order ID: ${trade.sellOrderID}</span>
    <span>Type: ${trade.orderType}</span>
    `;

    card.appendChild(info);
    tradeContainer.prepend(card);
}
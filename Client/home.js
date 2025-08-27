// FORMATS
// Login:
// 0:  messageType (u32)
// 4:  username    (char[50])
// 54: userID      (u32)
// 58: loginType   (u32)

// Order:
// 0:  messageType (u32)
// 4:  symbol      (u32)
// 8:  price       (f32)
// 12: quantity    (u32)
// 16: orderID     (u32)
// 20: userID      (u32)
// 24: isBuy       (u32)
// 28: orderType   (u32)

// Trade:
// 0:  messageType (u32) 
// 4:  symbol      (u32)
// 8:  price       (f32)
// 12: quantity    (u32)
// 16: buyOrderID  (u32)
// 20: sellOrderID (u32)
// 24: userID      (u32)
// 28: orderType   (u32)

// HELPERS
function getMessageType(value)
{
  switch(value)
  {
    case 0: return "Null";
    case 1: return "Order";
    case 2: return "Trade";
    case 3: return "Login";
  }
}
function getLoginType(value)
{
  switch(value)
  {
    case 0: return "Null";
    case 1: return "Acknowledge";
    case 2: return "Reject";
  }
}
function getStockSymbol(value) 
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
function getOrderType(value) 
{
    switch (value) 
    {
        case 1: return "Market";
        case 2: return "Limit";
        default: return "NA";
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
function setFormStatus(message) 
{
    document.getElementById("status").textContent = message;
}

// UI VARIABLES
const preLoginDiv = document.getElementById("pre-login")
const postLoginDiv = document.getElementById("post-login");
const loginForm = document.getElementById("loginForm");
const errorMsg = document.getElementById("errorMsg");
const tradeContainer = document.getElementById("tradeContainer");

// WEBSOCKET CONNECTION
const ws = new WebSocket("ws://localhost:9002");
ws.binaryType = "arraybuffer"
ws.onmessage = handleMessages;

// MESSAGE HANDLER
async function handleMessages(event) 
{
    try 
    {
        const buffer = event.data instanceof ArrayBuffer ? event.data : await event.data.arrayBuffer();
        const data = new DataView(buffer);
        
        const messageType = getMessageType(data.getUint32(0, true));
        
        if (messageType === "Login")
        {
            const userID = data.getUint32(54, true);
            const loginType = getLoginType(data.getUint32(58, true));
            if (loginType === "Acknowledge")
            {

                localStorage.setItem("userID", userID);
                preLoginDiv.style.display = "none";
                postLoginDiv.style.display = "flex";
                console.log("Login authenticated");
            }
        }
        else if (messageType == "Trade")
        {
            const trade = 
            {
                symbol: getStockSymbol(data.getUint32(4, true)),
                price: data.getFloat32(8, true),
                quantity: data.getUint32(12, true),
                buyOrderID: data.getUint32(16, true),
                sellOrderID: data.getUint32(20, true),
                userID: data.getUint32(24, true),
                orderType: getOrderType(data.getUint32(28, true))
            };
            addTradeCard(trade);
        }

    } 
    catch (err) 
    {
        console.error("Failed to parse trade message:", err);
    }
}


// FORM LISTENERS
// Login
loginForm.addEventListener("submit", (e) => {
  e.preventDefault();

  const username = document.getElementById("username").value.trim();
  console.log(username);

  const buffer = new ArrayBuffer(54);
  const view = new DataView(buffer);

  let off = 0;
  view.setUint32(off, 3, true); off += 4; // 3 is the messageType enum value of Login.

  const encoder = new TextEncoder();
  const encoded = encoder.encode(username);
  const maxLen = 50;
  for (let i = 0; i < maxLen; i++) 
  {
    view.setUint8(off + i, i < encoded.length ? encoded[i] : 0, true);
  }

  ws.send(buffer);
});
// Navbar
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
// Order
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
  const userID = localStorage.getItem("userID");
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






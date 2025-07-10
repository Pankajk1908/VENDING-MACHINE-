
let cart = [];
let issuedItems = [];
let uniqueCode = '';

// Function to switch between sections
function showSection(sectionId) {
    const sections = [
        'choose-action-section', 
        'get-items-section', 
        'submit-items-section', 
        'cart-section', 
        'order-history-section',
        'submission-info-section'
    ];
    
    sections.forEach(section => {
        document.getElementById(section).style.display = 'none';
    });
    
    document.getElementById(sectionId).style.display = 'block';
}

// Function to add items to the cart
function addToCart() {
    const items = [
        { item: 'Arduino Uno', quantity: document.getElementById('Arduino-Uno-quantity').value },
        { item: 'NodeMCU- esp32', quantity: document.getElementById('NodeMCU-esp32-quantity').value },
        { item: 'Arduino nano', quantity: document.getElementById('Arduino-nano-quantity').value },
        { item: 'Servo Motor', quantity: document.getElementById('servo-motor-quantity').value },
        { item: 'DC motor', quantity: document.getElementById('DC-motor-quantity').value },
        { item: 'Bluetooth module', quantity: document.getElementById('Bluetooth-module-quantity').value },
        { item: 'Motor driver(L293D)', quantity: document.getElementById('Motor-driver(L293D)-quantity').value },
        { item: 'Mini breadboard', quantity: document.getElementById('Mini-breadboard-quantity').value },
        { item: 'Ultrasonic sensors', quantity: document.getElementById('Ultrasonic-sensors-quantity').value },
        { item: 'LCD screen', quantity: document.getElementById('LCD-screen-quantity').value },
        { item: 'Raspberry pi', quantity: document.getElementById('Raspberry-pi-quantity').value }
    ];

    items.forEach(({ item, quantity }) => {
        if (quantity > 0) {
            const existingItemIndex = cart.findIndex(cartItem => cartItem.item === item);
            if (existingItemIndex !== -1) {
                cart[existingItemIndex].quantity += parseInt(quantity);
            } else {
                cart.push({ item, quantity: parseInt(quantity) });
            }
        }
    });

    alert('Items added to cart');
}

// Function to display the cart items in the cart section
function showCart() {
    showSection('cart-section');
    const cartItemsDiv = document.getElementById('cart-items');
    cartItemsDiv.innerHTML = ''; // Clear previous content
    
    // Iterate through each item in the cart
    cart.forEach((cartItem, index) => {
        // Create a new div element for each cart item
        const cartItemElement = document.createElement('div');
        cartItemElement.classList.add('cart-item');
        
        // Construct the HTML for the cart item
        cartItemElement.innerHTML = `
            <span>${cartItem.item} - ${cartItem.quantity}</span>
            <button onclick="decreaseQuantity(${index})">-</button>
            <button onclick="increaseQuantity(${index})">+</button>
            <button onclick="removeFromCart(${index})">Remove</button>
        `;
        
        // Append the cart item element to the cart items container
        cartItemsDiv.appendChild(cartItemElement);
    });
}

// Function to remove an item from the cart
function removeFromCart(index) {
    cart.splice(index, 1);
    showCart(); // Update cart display after removal
}

// Function to increase quantity of an item in the cart
function increaseQuantity(index) {
    if (cart[index].quantity < 2) {
        cart[index].quantity++;
    } else {
        alert('Quantity cannot be more than 2.');
    }
    
    showCart(); // Update cart display after increase
}

// Function to decrease quantity of an item in the cart
function decreaseQuantity(index) {
    if (cart[index].quantity > 1) {
        cart[index].quantity--;
    } else {
        alert('Quantity cannot be less than 1.');
    }
    showCart(); // Update cart display after decrease
}

// Function to confirm selection (placeholder)
function confirmSelection() {
    alert('Selection confirmed');
}

// Function to place an order for items in the cart
function orderItems() {
    uniqueCode = `ORD-${Math.random().toString(36).substr(2, 9).toUpperCase()}`;
    issuedItems = [...cart];
    cart = [];
    alert(`Order placed. Your unique code is ${uniqueCode}`);
    showOrderHistory(); // Show order history after placing the order
}

// Function to show order history
function showOrderHistory() {
    showSection('order-history-section');
    const orderHistoryDiv = document.getElementById('order-history-info');
    orderHistoryDiv.innerHTML = `
        <p><strong>Order History:</strong></p>
        ${issuedItems.map(item => `<p>${item.item} - ${item.quantity}</p>`).join('')}
    `;
}

// Function to handle unique code submission
function handleUniqueCode() {
    const uniqueCodeInput = document.getElementById('unique-code-input').value.trim();
    if (uniqueCodeInput === uniqueCode) {
        showSection('submission-info-section');
        const issuedItemsDiv = document.getElementById('issued-items');
        issuedItemsDiv.innerHTML = '';
        issuedItems.forEach((item, index) => {
            issuedItemsDiv.innerHTML += `
                <div class="submission-item">
                    <span>${item.item} - ${item.quantity}</span>
                </div>
            `;
        });
        issuedItemsDiv.innerHTML += `
            <button onclick="confirmSubmission()">Confirm Submission</button>
            <button onclick="redirectToMainMenu()">Start</button>
        `;
    } else {
        alert('Invalid unique code. Please try again.');
    }
}

// Function to confirm submission
function confirmSubmission() {
    alert('All items submitted successfully');
    issuedItems = [];
    uniqueCode = '';
    redirectToMainMenu();
}

// Function to redirect to main menu
function redirectToMainMenu() {
    showSection('choose-action-section');
}



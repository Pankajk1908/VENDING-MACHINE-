# 🔧 ESP32-Based IoT Vending Machine System

This project implements a smart **IoT-based vending machine** for the ECE Lab using **two ESP32 boards**:

- 📦 **ESP1**: Web interface, data sync with Google Sheets & ESP2
- 📸 **ESP2 (ESP32-CAM)**: Captures images and uploads them to Google Drive for logging

---

## 📋 Features

### 🧠 ESP1 – Main Controller
- Hosts a web interface:
  - 📥 *Get Items* with cart functionality
  - 📤 *Submit Items* with login verification
  - 🛒 View Cart, Confirm Selection
  - 📜 Order History (per user)
- Sends POST data (`gmail`, `cart`, `status`) to:
  - 📄 Google Sheets using Apps Script
  - 🔄 ESP2 to trigger image capture

### 📷 ESP2 – Camera System (ESP32-CAM)
- Receives POST `/submit` requests from ESP1
- Captures images every 5 seconds for 1 minute
- Uploads images to **Google Drive** using an Apps Script endpoint
- Flash LED for visual feedback during capture

---

## 🧰 Hardware Requirements

### ESP1:
- ESP32 Dev Module
- Wi-Fi connection

### ESP2:
- ESP32-CAM (AI Thinker)
- Flash LED on GPIO 4
- MicroSD card (optional for local image logging)

---

## 📦 File Structure

ESP-Vending-Machine/
├── ESP1/
│ ├── main.ino # Web interface + API logic
├── ESP2-CAM/
│ ├── camera_upload.ino # ESP32-CAM image capture
├── GoogleAppsScript/
│ ├── Code.gs # Drive + Sheets API handler
└── README.md








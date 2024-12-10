# Bluetooth Low Energy (BLE) Peripheral with Nordic nRF5340DK

This repository contains the code and documentation for a Bluetooth Low Energy (BLE) peripheral application implemented using Nordic's nRF5340DK. The application demonstrates the use of both standard and custom BLE services and characteristics, with a focus on implementing advanced security features and enhancing connectivity options.

## Features

### 1. **Comprehensive BLE Profile**
- Implementation of standard and custom BLE services and characteristics.
- Bidirectional communication between the Nordic device and a smartphone.

### 2. **Security Features**
- Legacy security and LE Secure Connections.
- Secure pairing processes for both methods.
- Handling security concerns in BLE with:
  - Various security levels.
  - Use of a Filter Accept List for secure and encrypted connections.

### 3. **Connection Management**
- Reading and modifying connection parameters.
- Requesting different PHY modes during connection establishment.

## Functional Highlights

### Security Implementation
- **Pairing Support**: Step-by-step addition of pairing support to the BLE peripheral.
- **Bonding**: Utilizing bonding information to create a Filter Accept List and enhance connection security.
- **Filter Accept List**: Advertising using a Filter Accept List for secure communication.

### Connection Optimization
- Establishing bi-directional communication with a smartphone.
- Practicing connection parameter updates to optimize BLE performance.
- Requesting different PHY modes for enhanced data rates and reliability.

## Getting Started

### Prerequisites
- Nordic nRF5340 Development Kit.
- nRF Connect SDK installed on your development environment.
- Smartphone with a BLE-compatible app (e.g., nRF Connect for Mobile).

### Setup
1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/ble-peripheral.git
   cd ble-peripheral

### Testing
1. Pair your smartphone with the nRF5340DK.
2. Test bi-directional communication using the smartphone app.
3. Verify connection parameter updates and PHY mode requests.

## Code Structure
- **/src**: Source code for the BLE peripheral.
- **/config**: Configuration files for security levels and Filter Accept List.
- **/docs**: Documentation for setting up and testing the application.

## Contribution
Contributions are welcome! Feel free to submit issues or pull requests for enhancements or bug fixes.

## Acknowledgments
- Nordic Semiconductor for providing robust SDKs and tools for BLE development.
- Community contributors for their valuable feedback and support.

# Project_Uber 
## Introduction
This is a simplified system of a taxi company. The application is able to support 2 types of users – customers and drivers. They are be able to register and log in to the system using a username and password, and exit the application without it terminating.
## Client's functions
* ORDER

Orders a taxi by specifying current address, destination and number of passengers.
Each address contains a name, coordinates (point with x and y) and additional specifying information (optional for each address).
When sending an order to the application, the system must trace the notification to all available drivers, first sending it to the driver closest to the address from which it was ordered. When a driver accepts the order, the system notifies the user. The system generates a unique id and prints it to the user.
* CHECK_ORDER

Checks the status of the order by its ID - whether it has been accepted, which driver will fulfill it, what the driver's details are(name and surname, car number, phone number, rating) and how long it will take to arrive.
* CANCEL_ORDER

Cancel order by its ID. If a driver has already accepted the order, the system releases him and notifies him about it.

* PAY

Pays for an order by its ID after it has been marked by the driver as completed. The money paid by the user goes into the driver's account.

* RATE

To rate (from 1 to 5) an otder's driver. The order's driver he is rating must have been accepted by him and already completed.

* ADD_MONEY

Adds money to the user's account. For convenience, we assume that a valid credit or debit card is entered and no additional checks are made for it.

## Driver's functions
* CHANGE_ADDRESS

Driver changes his current address (name and coordinates).

* CHECK_MESSAGES

Checks messages sent by the system. There are the orders that the system sends to him.

* ACCEPT_ORDER

Accepts an order by its ID and sends to the system information on how many minutes it will be at the address.

* DECLINE_ORDER

Declines an order by its ID. If a driver declines an order, the system should offer it to the next closest driver to the order address.

* FINISH_ORDER

Marks the order as completed (when it has reached the address). This automatically changes driver's address to the destination address.

* ACCEPT_PAYMENT

Accept payment. Sends information to the system about how much money he received from it.
## How it works
When you start the programme information about drivers, clients and orders is read from file. You are asked to make registration by pressing 1 or log in by pressing 2.
After you log in you can do some of the actions, mentioned above, depending on your role. There is a letter which represents every function, you can see them on the console screen. All the users can log out by pressing "q". After you log out, you can make registration, log in or just close the app by pressing "c". As you press "c", all the information about drivers, clients, orders is saved in different files. You can see the company's profit at the bottom of drivers' file.
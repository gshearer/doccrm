# doccrm -- Sales Engineer CRM-like Tool
# Introduction
DOCCRM -- Sales Engineer CRM-like Tool

# DESCRIPTION
This is a CRM-like tool to manage Customers, Contacts, Technologies, Manufacturers, and Distributors. Though there are many CRM tools that can perform these functions, this tool has one unique feature.

Each customer can be tagged with various technologies as you'll see in the screenshots.

A background process searches the Internet for items related to each technology such as the CVE database. From this data, the tool generates a list of "talking points" for each customer.

I have plans to expand this search for things like End-of-life bulletins, Manufacturer & Distributor promotions, and so on.

The goal is to enhance my value to both the sales reps that I assist and the customers that we serve.

## DISCLAIMER ##

This should have been written in PHP. It's written in C because that's what I know, but it's certainly not ideal for generating HTML :) However, it's fast!

Technologies used:

Backend: ArchLinux, Postgre SQL, NGINX Web Server, FastCGI gateway
Frontend: HTML5, CSS (bulma)

# TODO LISTS
This screen shows the list of TODO items. These items can be generic or assigned to a specific customer. A todo item can be assigned a priority of HIGH MEDIUM LOW. Note that if a TODO list item is assigned to a customer, you can click on that customer's name to be taken directly to the Customer edit screen.

TODO list items assigned to specific customers also show up on the customer edit screen. (see customer edit screen)

The location bar at the very top allows the user to quickly navigate to various sections of this application.

![TODO List](https://user-images.githubusercontent.com/7363828/114941636-67521f80-9e11-11eb-93b6-549a8370416c.jpg)

# CUSTOMERS
This screen shows a simple list of all customers. There's a simple single form entry at the top and bottom of this list for convenience.
![Customers](https://user-images.githubusercontent.com/7363828/114941627-66b98900-9e11-11eb-8074-77654dff9922.jpg)

# CUSTOMER EDIT
This is the most important screen in the application. Here you can manage your contacts and notes for each customer. Note that the text areas you see for data entry are of unlimited size, so you can add as much data as you wish.

TODO items for this specific customer can also be managed here, which will be displayed on the primary TODO list screen (above).

Most importantly -- this is where you tag what technologies are associated with a customer.
![Customer Edit](https://user-images.githubusercontent.com/7363828/114941624-6620f280-9e11-11eb-94c9-8613f0a74b23.jpg)

# CUSTOMER JOURNAL
This is actually part of the same customer edit screen which is too big for one screenshot. A journal is associated with each customer. Journal entries are timestamped and can be unlimited. I tend to make a journal entry every time I interact with a customer in some way.
![Customer Journal](https://user-images.githubusercontent.com/7363828/114941626-6620f280-9e11-11eb-9a3d-abd0ccc29ec6.jpg)

# TECHNOLOGIES
This is a simple screen where you can define technologies which can be associated with customers. Each technology can be clicked on to manage further details (see below)

## This is one of the most important screens ##
At the bottom this is where you will see a list of *TALKING POINTS* that the background process has found while searching the web. This is the biggest reason I wrote this application. I wanted an automated system that gives me good reason to inform both my rep and my customer about important items related to the products & services they use. Not only does this help keep your relationships fresh and active --- but also aids in winning additional business!
![Technologies](https://user-images.githubusercontent.com/7363828/114941633-67521f80-9e11-11eb-9123-d804024de7b2.jpg)

# TECHNOLOGY EDIT
Here you can manage the technologies and assign a distributor to each. You can also manage notes for this technology.
![Technology Edit](https://user-images.githubusercontent.com/7363828/114941635-67521f80-9e11-11eb-9980-777a6badd4c0.jpg)

# MANUFACTURERS
This screen shows a list of defined OEM / Manufactureres. Each one can be clicked on to be taken to the edit screen where further details can be managed (see below)
![Manufacturers](https://user-images.githubusercontent.com/7363828/114941632-66b98900-9e11-11eb-8421-93830569a641.jpg)

# MANUFACTURER EDIT
This screen allows you manage details about each Manufacturer
![Manufacturer Edit](https://user-images.githubusercontent.com/7363828/114941630-66b98900-9e11-11eb-81fa-b742a2ee4a24.jpg)
 
# DISTRIBUTORS
This screen allows the user to manage a list of Distributors that are used to fulfil a given technology. Each distributor can be clicked on to be taken to the edit screen where further details can be managed (see below)
![Disty](https://user-images.githubusercontent.com/7363828/114941628-66b98900-9e11-11eb-928f-ebf5ce810581.jpg)

# DISTRIBUTOR EDIT
![Distributor Edit](https://user-images.githubusercontent.com/7363828/114941629-66b98900-9e11-11eb-80a6-6d3a85ac6a1b.jpg)

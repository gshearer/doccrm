# doccrm -- Sales Engineer CRM-like Tool
# Introduction
DOCCRM -- Sales Engineer CRM-like Tool

# Description
This is a CRM-like tool to manage Customers, Contacts, Technologies, Manufacturers, and Distributors. Though there are many CRM tools that can perform these functions, this tool has one unique feature.

Each customer can be tagged with various technologies as you'll see in the screenshots.

A background process searches the Internet for items related to each technology such as the CVE database. From this data, the tool generates a list of "talking points" for each customer.

I have plans to expand this search for things like End-of-life bulletins, Manufacturer & Distributor promotions, and so on.

The goal is to enhance my value to both the sales reps that I assist and the customers that we serve.

Disclaimer :)

This should have been written in PHP. It's written in C because that's what I know, but it's certainly not ideal for generating HTML :) However, it's fast!

Technologies used:

Backend: ArchLinux, Postgre SQL, NGINX Web Server, FastCGI gateway
Frontend: HTML5, CSS (bulma)

# TODO LISTS
This screen shows the list of TODO items. These items can be generic or assigned to a specific customer. A todo item can be assigned a priority of HIGH MEDIUM LOW.
TODO items will also be shown on the customer specific screen.
![TODO List](https://user-images.githubusercontent.com/7363828/114941636-67521f80-9e11-11eb-93b6-549a8370416c.jpg)


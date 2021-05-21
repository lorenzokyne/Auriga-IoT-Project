# Auriga.WWSToaster

## Description
A simple arduino project for a prototype of IoT security device for ATMs. Let's see some examples of ATM attacks that this project aims to avoid. 

### ATM Jackpotting
It is a sophisticated crime in which thieves install malicious software and/or hardware at ATMs that forces the machines to dispense huge volumes of cash on demand.
1. Gain physical internal access to an ATM through the top-hat of the terminal.
2. Use an endscope instrument to locate internal portion of the cash machine.
3. Attach a cord that allows them to sync their device to the ATM’s computer.
4. Use a keyboard or device to access the ATM’s computer.
5. Install the ATM Malware.
6. Collect cash with money mule.

This is a summarized attack process and is no way an absolute methodology to ATM attacking. 

### Physical Attack
Another simple and frequent attack, especially in Puglia, is removing of ATM from the site. This is a Physical Attack. Physical attacks on ATMs are considered risky, as it not only leads to financial losses but also involves the risk to property and life. The physical attack involves solid and gas explosives attacks, along with physical removal of ATMs from the site and later using other techniques to gain access to the cash dispenser.

### Other types of Attacks
There are other types of attacks like Man-in Middle attack, Data Sniffing Attacks, Skimming with Spoofing. Those attacks target customers instead of banks. 

## Devices
- [Modulo GSM GSM GPRS SIM800L](https://www.amazon.it/gp/product/B07X2634ZQ/ref=ox_sc_act_title_1?smid=A2BQVM41SWSLKR&psc=1)
- [Aideepen 2PCS GY-GPS6MV2 NEO-6M Modulo di Posizione Modulo GPS](https://www.amazon.it/gp/product/B08CZSL193/ref=ox_sc_act_title_2?smid=AUN6EYX254ETV&psc=1)
- [AZDelivery Jumper Wire Cavetti](https://www.amazon.it/gp/product/B074P726ZR/ref=ox_sc_act_title_3?smid=A1X7QLRQH87QA3&psc=1)
- [Elegoo Progetto Starter Kit Basic](https://www.amazon.it/gp/product/B06XSFF7MG/ref=ox_sc_act_title_4?smid=AZF7WYXU5ZANW&psc=1)
- [Elegoo 37-in-1 Kit Modulo Sensore Elettronici](https://www.amazon.it/gp/product/B01N79PG4G/ref=ox_sc_act_title_5?smid=AZF7WYXU5ZANW&psc=1)
- [Caricabatterie USB Amazon da 5](https://www.amazon.it/gp/product/B01J2G52O6/ref=crt_ewc_title_dp_1?ie=UTF8&psc=1&smid=A11IL2PNWYJU7H)
- [POSUGEAR Power Bank 10000mAh](https://www.amazon.it/gp/product/B07WVVTK86/ref=crt_ewc_title_dp_2?ie=UTF8&psc=1&smid=A1F8R6XWWYQ81U)

## Architecture
The following diagram shows the architecture that must be implemented in order to satisfy the project's requirements. Basically, it is composed of three parts.
- The IoT devices located on the ATMs (Arduino).
- A message broker used to communicate with a backend that implements the business logic (RabbitMQ).
- A module for system monitoring (Elastic Stack).

![Architecture Diagram](docs/diagrams/architecture-diagram.png)

### Arduino

### RabbitMQ

After you installed RabbitMQ you must create a new exchange with the following attributes.
- **Name**: amq.topic
- **Type**: topic
- **Durability**: true

Queue Name | Type | Durability | Args
------------ | ------------- | ------------- | -------------
q_brightness | classic| true | 
q_electromagnetic-field | classic| true | 
q_gps | classic| true | 
q_gyroscope | classic| true | 
q_microphone | classic| true | 
q_motion | classic| true | 
q_sensors | classic| true | 
q_temp-humidity | classic| true | 

### Elastic Stack

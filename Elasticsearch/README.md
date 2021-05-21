# Elasticsearch - Windows Installation steps

 [Official Documentation](https://www.elastic.co/guide/en/elasticsearch/reference/current/index.html)

## Requirements 

- Windows
- Internet connection

## Steps

1. Download Elasticsearch from the [official website](https://www.elastic.co/downloads/elasticsearch).
2. Unzip the file in your favourite folder. For example **C:**
3. Open the **config/elasticsearch.yml** file and set the address of the node using **network.host: 127.0.0.1**
>By default Elasticsearch binds only to localhost which means it cannot be accessed remotely.

Than run Elasticsearch from the command line or install it as a service.
After you can navigate to **127.0.0.1:9200** and verify that Elasticsearch is running.

### Run from the command line:
Open the cmd or the PowerShell, move to the installation folder and run
> **.\bin\elasticsearch.bat**

Elasticsearch will start in foreground and can be stopped by pressing **Ctrl+C**.

### Install as a service:
Open the cmd or the PowerShell, move to the installation folder and run
> **.\bin\elasticsearch-service.bat install**

Than the service can be started in background or stopped using 
> **.\bin\elasticsearch-service.bat start**
> **.\bin\elasticsearch-service.bat stop**





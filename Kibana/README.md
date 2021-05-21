# Kibana - Windows installation steps

[Official Documentation](https://www.elastic.co/guide/en/kibana/current/index.html)

## Requirements 

- Windows
- Internet connection

## Steps

1. Download Kibana from the [official website](https://www.elastic.co/downloads/kibana).
2. Unzip the file in your favourite folder. For example **C:**
3. Open the **config/kibana.yml** file and set the address of the node using **server.host: 127.0.0.1**
>By default Kibana binds only to localhost which means it cannot be accessed remotely.
4. Open the **config/kibana.yml** file and set the address of the Elasticsearch node using **elasticsearch.hosts: [ "127.0.0.1:9200" ]**.
5. From the command line move to the installation folder and run
> **.\bin\kibana.bat**

Kibana will start in foreground and can be stopped by pressing **Ctrl+C**.

You can navigate to **127.0.0.1:5601** and verify that Kibana is running.


# Logstash- Windows installation steps

[Official Documentation](https://www.elastic.co/guide/en/logstash/current/index.html)

## Requirements 

- Windows
- Internet connection

## Steps

1. Download Logstash from the [official website](https://www.elastic.co/downloads/logstash).
2. Unzip the file in your favourite folder. For example **C:\\**
3. Create a **sensors-pipeline.conf** in the **config/** folder.
4. Open the **config/pipelines.yml** file and set the pipeline id and the pipeline configuration:
> \- **pipeline.id: sensors-pipeline**
>    **path.config: "./config/sensors-pipeline.conf"**
5. Configure the pipeline using the **config/sensors-pipeline.conf** file. The pipeline must consume the messages from the RabbitMQ queue, filter them and send to Elasticsearch.

Than you can run Logstash or check the pipeline configuration from the command line.

### Check pipeline configuration:
Open the cmd or the PowerShell, move to the installation folder and run
> **.\bin\logstash --config.test_and_exit**

Logstash will check the configuration file.

### Run from the command line:
Open the cmd or the PowerShell, move to the installation folder and run
> **.\bin\logstash --config.reload.automatic**

Logstash will start in foreground and can be stopped by pressing **Ctrl+C**.
Using the **config.reload.automatic** Logstash restart itself if any configuration file was modified.

